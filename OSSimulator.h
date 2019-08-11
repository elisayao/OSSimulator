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

#pragma once

#include <vector>
#include <queue>

#include "OSSimTypes.h"

/* Define O/S process ids (also equivalent to their priorities) */
#define IDLE 0	/* CPU has nothing to execute    */
#define MASTER -1 /* Lowest priority               */
#define DONES -2
#define IOS -3
#define DISPATCH -4
#define TI_INT -5
#define SC_INT -6
#define IO_INT -7 /* Highest priority              */

#define CPU_MASTER 4
#define CPU_DONES 3
#define CPU_IOS 3

#define IO_WORKING "W"
#define IO_PENDING "P"
#define IO_DONE "D"

#define DEV_AVAL "A"
#define DEV_BUSY "B"
#define DEV_DISK 0
#define DEV_TAPE 1
#define DEV_CD 2

#define READY "R"
#define EXEC "E"
#define BLOCKED "B"
#define DONE "D"
#define HELD "H"
#define NONE " "

#define EVENT_TI "T"
#define EVENT_IO "I"

#define MEM_FREE 0
#define MEM_USED 1

using namespace std;

class OSSimulator
{
public:
	OSSimulator(OSParameters in_os_prarms);
	~OSSimulator();

	int Simulate(const vector<ProgramRecord> &program_records);

private:
	void OSSimTick();

	void PrintOSParams();

	void InitOS();
	// Process input program and add entry to pcb list.
	void RunMasterScheduler();
	int Allocate(int program_ind, vector<int> &allocated_block);

	void SetReadyList(PCB &pcb);

	bool RunOSProcess();

	void RunDispatcher();
	void RunIOService();
	void RunTimeoutHandler();
	void RunIOCompleteHandler();
	void RunIOServiceHandler();
	void RunProcessDoneService();

	void RunIORoutine();

	void ScheduleOSProcess(int os_pid);

	void RequestIOService(PCB &pcb, int run_ind);
	void SetBlockList(const PCB &pcb, int device_id);

	void RunUserProcess();
	PCB &FindPCBById(int pid);
	void AddToEventList(EventEntry new_event);
	void CheckEvents();

	void PrintSystemInfo();
	void PrintMemoryInfo(int pid);

private:
	OSParameters os_prarms;
	vector<ProgramRecord> program_list;
	vector<PCB> pcb_list;
	vector<EventEntry> event_list;
	vector<DeviceEntry> device_list[3];

	priority_queue<ReadyListEntry> ready_queue;
	vector<BlockListEntry> block_list;

	vector<MemoryBlockEntry> fixed_block_memory_list;

	int ios_request_pid;
	int ios_request_devices;
	int ios_request_unit;

	int master_clock; /* Master system clock           */
	int curr_pid;	 /* Contains pid of process exec. */
	int curr_os_pid;  /* Contains pid of teh current os process. */
	int os_counter;   /* Counts down for MASTER,DONES, */

	priority_queue<int, vector<int>, greater<int>> os_pid_queue;

	queue<EventEntry> pending_ti_events;
	queue<EventEntry> pending_io_events;
};
