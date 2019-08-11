// Copyright 03/2019 Elisa(Lan) Yao

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "OSSimulator.h"
#include <algorithm>
#include <iostream>

OSSimulator::OSSimulator(OSParameters in_os_prarms)
	: os_prarms(in_os_prarms)
{
}

OSSimulator::~OSSimulator()
{
}

int OSSimulator::Simulate(const vector<ProgramRecord> &program_records)
{
	PrintOSParams();

	InitOS();

	program_list = program_records;
	ScheduleOSProcess(MASTER);

	while (true)
	{
		OSSimTick();
		master_clock++;

		if (master_clock % os_prarms.every_n_units == 0)
		{
			PrintSystemInfo();
		}

		if (pcb_list.empty() && program_list.empty())
		{
			return master_clock;
		}
	}
}

void OSSimulator::OSSimTick()
{
	CheckEvents();

	// Finish the tick if there is OS process to run.
	if (RunOSProcess())
	{
		return;
	}

	if (curr_pid != IDLE)
	{
		RunUserProcess();
	}

	RunIORoutine();
}

void OSSimulator::PrintOSParams()
{
	cout << "O/S Parameters:" << endl;
	cout << endl;

	cout << "\tMemory Model Used :\t\t\t" << (os_prarms.mem_model == 1 ? "F" : "V") << endl;
	cout << "\tFixed Mem Blk Size :\t\t\t" << os_prarms.mem_fix_blksize << endl;
	cout << "\tFixed Mem Blks Aval :\t\t\t" << os_prarms.mem_fix_blksaval << endl;
	cout << "\tVariable Mem Max Size :\t\t\t" << os_prarms.mem_var_maxsize << endl;
	cout << "\tVariable Mem Tot Size :\t\t\t" << os_prarms.mem_var_totsize << endl;
	cout << "\tMax.Tasks Allowed :\t\t\t" << os_prarms.pro_max_tasks << endl;
	cout << "\tProcess Mgmt Algthm :\t\t\t" << os_prarms.pro_algorithm << endl;
	cout << "\tInitial Quantum Size :\t\t\t" << os_prarms.init_quantum << endl;
	cout << "\tNumber Disk Units :\t\t\t" << os_prarms.disk_units << endl;
	cout << "\tNumber Tape Units :\t\t\t" << os_prarms.tape_units << endl;
	cout << "\tNumber CD   Units :\t\t\t" << os_prarms.cdrom_units << endl;
	cout << "\tPrint Every N Units :\t\t\t" << os_prarms.every_n_units << endl;

	cout << endl;
}

void OSSimulator::InitOS()
{
	// initialize memory block list.
	fixed_block_memory_list.clear();
	for (int i = 0; i < os_prarms.mem_fix_blksaval; i++)
	{
		MemoryBlockEntry new_block_entry = {0, 0};
		fixed_block_memory_list.push_back(new_block_entry);
	}

	// initialize device list.
	for (int i = 0; i < 3; i++)
	{
		device_list[i].clear();
		int device_num = i == DEV_DISK ? os_prarms.disk_units : (i == DEV_TAPE ? os_prarms.tape_units : os_prarms.cdrom_units);
		for (int j = 0; j < device_num; j++)
		{
			device_list[i].push_back({j, 0, DEV_AVAL});
		}
	}

	// initialize ready and block list.
	event_list.clear();

	string pro_algo(os_prarms.pro_algorithm);
	ready_queue = priority_queue<ReadyListEntry>();
	block_list = vector<BlockListEntry>();

	// restart master clock;
	master_clock = 0;
}

void OSSimulator::ScheduleOSProcess(int os_pid)
{
	os_pid_queue.push(os_pid);
}

void OSSimulator::RunMasterScheduler()
{
	if (os_counter != 1)
	{
		return;
	}
	string pro_algo(os_prarms.pro_algorithm);

	// sort the program_list if IPRI algo is used in this OS.
	if (pro_algo == "IPRI")
	{
		sort(program_list.begin(), program_list.end(),
			 [](const ProgramRecord &a, const ProgramRecord &b) -> bool {
				 return a.process_priority > b.process_priority;
			 });
	}

	vector<int> program_to_remove;

	for (int i = 0; i < program_list.size(); i++)
	{
		ProgramRecord &program = program_list[i];
		vector<int> allocated;
		int pid = Allocate(i, allocated);

		if (pid == -2)
		{
			cout << "Flushed: " << program.process_name << " from input queue - not enough memory!" << endl;
			cout << endl;
			program_to_remove.push_back(i);
			continue;
		}

		if (pid == -1)
		{
			continue;
		}

		program_to_remove.push_back(i);

		PCB pcb_entry;
		pcb_entry.id = pid;
		pcb_entry.name = string(program.process_name);
		pcb_entry.initial_priority = program.process_priority;
		memcpy(pcb_entry.run_info, program.run_info, 10 * 3 * sizeof(int));
		pcb_entry.cur_ctr = 0;
		pcb_entry.state = READY;
		pcb_entry.total_cpu = 0;
		pcb_entry.total_ios = 0;
		pcb_entry.start_time = 0;
		pcb_entry.end_time = 0;
		pcb_entry.sim_ri_idx = 0;

		pcb_list.push_back(pcb_entry);
		SetReadyList(pcb_entry);

		cout << "Allocated: " << program.process_name << " at MC time: " << master_clock << " (PID#: " << pid << ")" << endl;
		cout << "Memory Block(s): ";
		for (auto ind : allocated)
		{
			cout << ind + 1 << " ";
		}
		cout << endl;
		cout << endl;
	}

	for (int i = program_to_remove.size() - 1; i >= 0; i--)
	{
		program_list.erase(program_list.begin() + i);
	}

	ScheduleOSProcess(DISPATCH);
}

int OSSimulator::Allocate(int program_ind, vector<int> &allocated_block)
{
	int static next_pid = 1;

	ProgramRecord &program = program_list[program_ind];
	int max_memory = os_prarms.mem_model == 1 ? os_prarms.mem_fix_blksize * os_prarms.mem_fix_blksaval / 1000
											  : os_prarms.mem_var_totsize;

	if (program.process_memsize > max_memory)
	{
		return -2;
	}

	int blocks_required = program.process_memsize * 1000 / os_prarms.mem_fix_blksize;

	vector<int> free_block_indices;

	for (int i = 0; i < fixed_block_memory_list.size(); i++)
	{
		if (fixed_block_memory_list[i].state == MEM_FREE)
		{
			free_block_indices.push_back(i);
		}
	}

	if (free_block_indices.size() < blocks_required)
	{
		return -1;
	}

	int allocated_pid = next_pid;
	next_pid++;
	allocated_block.clear();
	for (int i = 0; i < blocks_required; i++)
	{
		int ind = free_block_indices[i];
		fixed_block_memory_list[ind].state = MEM_USED;
		fixed_block_memory_list[ind].pid = allocated_pid;
		allocated_block.push_back(ind);
	}

	return allocated_pid;
}

void OSSimulator::SetReadyList(PCB &pcb)
{
	static int ready_fifo_priority = INT_MAX;

	string pro_algo(os_prarms.pro_algorithm);
	ReadyListEntry ready_entry;
	ready_entry.pid = pcb.id;
	if (pro_algo == "FIFO")
	{
		ready_entry.current_priority = ready_fifo_priority--;
	}
	else if (pro_algo == "IPRI")
	{
		ready_entry.current_priority = pcb.initial_priority;
	}

	ready_queue.push(ready_entry);
}

bool OSSimulator::RunOSProcess()
{
	if (os_counter == 0)
	{
		// check if we have os process scheduled to run in this tick, if not, return false so
		// it can run user process.
		if (os_pid_queue.empty())
		{
			return false;
		}

		int os_pid = os_pid_queue.top();
		os_pid_queue.pop();
		curr_os_pid = os_pid;

		if (curr_os_pid == IOS)
		{
			os_counter = 3;
		}
		else if (curr_os_pid == DONES)
		{
			os_counter = 3;
		}
		else if (curr_os_pid == MASTER)
		{
			os_counter = 4;
		}
		else
		{
			os_counter = 1;
		}
	}

	if (curr_os_pid == IO_INT)
	{
		RunIOCompleteHandler();
	}
	else if (curr_os_pid == SC_INT)
	{
		RunIOServiceHandler();
	}
	else if (curr_os_pid == TI_INT)
	{
		RunTimeoutHandler();
	}
	else if (curr_os_pid == DISPATCH)
	{
		RunDispatcher();
	}
	else if (curr_os_pid == IOS)
	{
		RunIOService();
	}
	else if (curr_os_pid == DONES)
	{
		RunProcessDoneService();
	}
	else if (curr_os_pid == MASTER)
	{
		RunMasterScheduler();
	}

	os_counter--;
	return true;
}

void OSSimulator::RunDispatcher()
{
	if (ready_queue.empty())
	{
		curr_pid = IDLE;
		return;
	}

	ReadyListEntry nextEntry = ready_queue.top();
	ready_queue.pop();

	for (int i = 0; i < pcb_list.size(); i++)
	{
		if (pcb_list[i].id != nextEntry.pid)
		{
			continue;
		}

		pcb_list[i].state = EXEC;
		if (pcb_list[i].start_time == 0)
		{
			pcb_list[i].start_time = master_clock;
			pcb_list[i].cur_ctr = pcb_list[i].run_info[pcb_list[i].sim_ri_idx][0];

			cout << "Started " << pcb_list[i].name << " at MC time: " << master_clock << " (PID#: " << pcb_list[i].id << ")" << endl;
			cout << endl;
		}
		else
		{
			// We should always need additional circle if resumed from block.
			if (pcb_list[i].cur_ctr == 0)
			{
				pcb_list[i].cur_ctr = pcb_list[i].run_info[pcb_list[i].sim_ri_idx][0];
			}
			else
			{
				// we are resuming from timeout. No need to reset cur_ctr value;
			}
		}

		curr_pid = pcb_list[i].id;
		EventEntry timeout_event;
		timeout_event.time = master_clock + os_prarms.init_quantum + 1;
		timeout_event.pid = pcb_list[i].id;
		timeout_event.type = EVENT_TI;

		AddToEventList(timeout_event);
	}
}

void OSSimulator::RunIOService()
{
	if (os_counter != 1)
	{
		return;
	}

	int pending_entry_ind;
	for (int i = 0; i < block_list.size(); i++)
	{
		if (block_list[i].state == IO_PENDING)
		{
			pending_entry_ind = i;
		}
	}

	ios_request_devices = block_list[pending_entry_ind].dtype;
	ios_request_pid = block_list[pending_entry_ind].pid;

	// Request device
	int available_deivce_ind = -1;
	for (int i = 0; i < device_list[ios_request_devices].size(); i++)
	{
		string device_state = device_list[ios_request_devices][i].state;
		if (device_state == DEV_AVAL)
		{
			available_deivce_ind = i;
			device_list[ios_request_devices][i].state = DEV_BUSY;
			break;
		}
	}

	PCB &pcb = FindPCBById(ios_request_pid);

	if (available_deivce_ind == -1)
	{
		// No device availabe, put the process to Held and remove it from the block list.
		pcb.state = HELD;
		block_list.erase(block_list.begin() + pending_entry_ind);
	}
	else
	{
		pcb.state = BLOCKED;
		block_list[pending_entry_ind].did = device_list[ios_request_devices][available_deivce_ind].did;
		block_list[pending_entry_ind].state = IO_WORKING;

		EventEntry io_complete_event;
		io_complete_event.time = pcb.run_info[pcb.sim_ri_idx][1] + master_clock + 1;
		io_complete_event.pid = pcb.id;
		io_complete_event.type = EVENT_IO;

		AddToEventList(io_complete_event);
	}

	ScheduleOSProcess(DISPATCH);
}

void OSSimulator::RunTimeoutHandler()
{
	PCB &pcb = FindPCBById(pending_ti_events.front().pid);
	pending_ti_events.pop();

	if (pcb.state == EXEC)
	{
		pcb.state = READY;
		curr_pid = IDLE;

		SetReadyList(pcb);

		ScheduleOSProcess(DISPATCH);
	}
}

void OSSimulator::RunIOCompleteHandler()
{
	PCB &pcb = FindPCBById(pending_io_events.front().pid);

	if (pcb.state == BLOCKED)
	{
		pcb.sim_ri_idx++;
		pcb.state = READY;
		SetReadyList(pcb);
	}
	else
	{
		cerr << "Something wrong happend!" << endl;
	}

	int block_entry_ind = -1;
	for (int i = 0; i < block_list.size(); i++)
	{
		if (block_list[i].pid == pending_io_events.front().pid)
		{
			block_entry_ind = i;
		}
	}

	BlockListEntry &entry = block_list[block_entry_ind];

	// set device state back to available.
	for (int i = 0; i < device_list[entry.dtype].size(); i++)
	{
		if (device_list[entry.dtype][i].did == entry.did)
		{
			device_list[entry.dtype][i].state = DEV_AVAL;
		}
	}

	for (int i = 0; i < pcb_list.size(); i++)
	{
		if (pcb_list[i].state == HELD)
		{
			if (pcb_list[i].run_info[pcb_list[i].sim_ri_idx][2] == entry.dtype)
			{
				pcb_list[i].state = READY;
				SetReadyList(pcb_list[i]);
			}
		}
	}

	// remove block list entry.
	block_list.erase(block_list.begin() + block_entry_ind);

	// Invode dispatcher if no process is running.
	if (curr_pid == IDLE)
	{
		ScheduleOSProcess(DISPATCH);
	}

	pending_io_events.pop();
}

void OSSimulator::RunIOServiceHandler()
{
	ScheduleOSProcess(IOS);
}

void OSSimulator::RunProcessDoneService()
{
	if (os_counter != 1)
	{
		return;
	}

	int done_pcb_ind = -1;
	for (int i = 0; i < pcb_list.size(); i++)
	{
		if (pcb_list[i].state == DONE)
		{
			done_pcb_ind = i;
			break;
		}
	}

	PCB &done_pcb = pcb_list[done_pcb_ind];

	cout << "De-Allocated: " << done_pcb.name << " at MC time " << master_clock << endl;
	cout << "\t Total Service Units: " << done_pcb.total_ios << endl;
	cout << "\t Total CPU Units: " << done_pcb.total_cpu << endl;
	cout << "\t  MC Start Time: " << done_pcb.start_time << endl;
	cout << "\t  MC End Time: " << done_pcb.end_time << endl;
	cout << "\t Total Elapsed Units: " << done_pcb.end_time - done_pcb.start_time << endl;
	cout << "\t  Memory Blks Used: ";
	for (int i = 0; i < fixed_block_memory_list.size(); i++)
	{
		if (fixed_block_memory_list[i].pid == done_pcb.id)
		{
			fixed_block_memory_list[i].state = MEM_FREE;
			cout << " " << i + 1;
		}
	}
	cout << endl;
	cout << endl;

	pcb_list.erase(pcb_list.begin() + done_pcb_ind);

	ScheduleOSProcess(MASTER);
}

void OSSimulator::RunIORoutine()
{
	for (int i = 0; i < block_list.size(); i++)
	{
		if (block_list[i].state != IO_WORKING)
		{
			continue;
		}

		int pid = block_list[i].pid;
		PCB &pcb = FindPCBById(pid);
		pcb.total_ios++;
	}
}

void OSSimulator::RequestIOService(PCB &pcb, int run_ind)
{
	pcb.state = BLOCKED;
	SetBlockList(pcb, -1);

	ScheduleOSProcess(SC_INT);
}

void OSSimulator::SetBlockList(const PCB &pcb, int device_id)
{
	static int block_fifo_priority = INT_MAX;
	BlockListEntry block_entry;

	block_entry.pid = pcb.id;

	string pro_algo(os_prarms.pro_algorithm);
	if (pro_algo == "FIFO")
	{
		block_entry.current_priority = block_fifo_priority--;
	}
	else if (pro_algo == "IPRI")
	{
		block_entry.current_priority = pcb.initial_priority;
	}

	block_entry.state = IO_PENDING;
	block_entry.dtype = pcb.run_info[pcb.sim_ri_idx][2];
	block_entry.did = device_id;

	block_list.push_back(block_entry);
	sort(block_list.begin(), block_list.end());
}

void OSSimulator::RunUserProcess()
{
	for (int i = 0; i < pcb_list.size(); i++)
	{
		if (pcb_list[i].id == curr_pid)
		{
			if (pcb_list[i].cur_ctr > 0)
			{
				pcb_list[i].total_cpu++;
				pcb_list[i].cur_ctr--;
			}

			if (pcb_list[i].cur_ctr <= 0)
			{
				int cur_ri_ind = pcb_list[i].sim_ri_idx;

				if (pcb_list[i].run_info[cur_ri_ind][1] != 0)
				{
					RequestIOService(pcb_list[i], cur_ri_ind);
				}
				else if (cur_ri_ind < 10 && pcb_list[i].run_info[cur_ri_ind][0] != 0)
				{
					// have more cycle to execute.
					pcb_list[i].sim_ri_idx++;
					pcb_list[i].cur_ctr = pcb_list[i].run_info[cur_ri_ind + 1][0];
				}
				else
				{
					// Invoke done service.
					pcb_list[i].state = DONE;
					pcb_list[i].end_time = master_clock;

					cout << "Completed: " << pcb_list[i].name << " at MC time: " << master_clock << endl;
					cout << endl;

					ScheduleOSProcess(DONES);
				}
			}
		}
	}
}

PCB &OSSimulator::FindPCBById(int pid)
{
	for (int i = 0; i < pcb_list.size(); i++)
	{
		if (pcb_list[i].id == pid)
		{
			return pcb_list[i];
		}
	}

	return pcb_list[0];
}

void OSSimulator::AddToEventList(EventEntry new_event)
{
	event_list.push_back(new_event);
	sort(event_list.begin(), event_list.end());
}

void OSSimulator::CheckEvents()
{
	if (event_list.empty())
	{
		return;
	}

	if (master_clock > event_list[0].time)
	{
		cerr << "Something wrong happened" << endl;
	}

	while (!event_list.empty() && master_clock == event_list[0].time)
	{
		EventEntry event_entry = event_list[0];
		event_list.erase(event_list.begin());

		if (event_entry.type == EVENT_TI && FindPCBById(event_entry.pid).state == EXEC)
		{
			// Only trigger timeout event if the process is currently executing.
			pending_ti_events.push(event_entry);
			ScheduleOSProcess(TI_INT);
		}
		else if (event_entry.type == EVENT_IO)
		{
			pending_io_events.push(event_entry);
			ScheduleOSProcess(IO_INT);
		}
	}
}

void OSSimulator::PrintSystemInfo()
{
	if (pcb_list.empty())
	{
		return;
	}

	cout << "=================================== " << master_clock << " ===================================" << endl;
	cout << endl;
	cout << "Pid  Program                Memory           Current     Rdy   I/O    Event  " << endl;
	cout << "     Name                   Usage            State       List  T-Dv#  Info   " << endl;
	cout << "---  --------  ----------------------------  ----------  ----  -----  -------" << endl;
	for (int i = 0; i < pcb_list.size(); i++)
	{
		PCB &pcb = pcb_list[i];
		cout << pcb.id << "    ";
		cout << pcb.name << "   ";
		PrintMemoryInfo(pcb.id);
		cout << "\t\t\t";
		cout << pcb.state << "\t";
		cout << (pcb.state == READY ? "   1" : "") << "\t";
		if (pcb.state == BLOCKED)
		{
			for (int j = 0; j < block_list.size(); j++)
			{
				if (block_list[j].pid == pcb.id)
				{
					if (block_list[j].state == IO_PENDING)
					{
						cout << "PEND\t";
					}
					else
					{
						cout << block_list[j].dtype + 1 << "-" << block_list[j].did << "\t";
					}
				}
			}
		}
		else
		{
			cout << "\t";
		}

		for (int j = 0; j < event_list.size(); j++)
		{
			if (event_list[j].pid == pcb.id)
			{
				cout << event_list[j].type << ":" << event_list[j].time;
			}
		}
		cout << endl;
	}

	cout << endl;
	cout << "\t\tFreeBlks: ";
	for (int i = 0; i < fixed_block_memory_list.size(); i++)
	{
		if (fixed_block_memory_list[i].state == MEM_FREE)
		{
			cout << " " << i + 1;
		}
	}
	cout << endl;

	if (!os_pid_queue.empty())
	{
		string process = "";
		int os_process = os_pid_queue.top();
		if (os_process == 0)
		{
			process = "IDLE";
		}
		else if (os_process == -1)
		{
			process = "MASTER";
		}
		else if (os_process == -2)
		{
			process = "DONES";
		}
		else if (os_process == -3)
		{
			process = "IOS";
		}
		else if (os_process == -4)
		{
			process = "DISPATCH";
		}
		else if (os_process == -5)
		{
			process = "TI_INT";
		}
		else if (os_process == -6)
		{
			process = "SC_INT";
		}
		else if (os_process == -7)
		{
			process = "IO_INT";
		}

		cout << "\t\t" << process;
		cout << "\t\t\tExecute Next" << endl;
	}

	cout << "=================================== " << master_clock << " ===================================" << endl;
	cout << endl;
}

void OSSimulator::PrintMemoryInfo(int pid)
{
	for (int i = 0; i < fixed_block_memory_list.size(); i++)
	{
		if (fixed_block_memory_list[i].pid == pid)
		{
			cout << " " << i + 1;
		}
	}
}
