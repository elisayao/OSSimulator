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

#include <string>
#include <vector>

struct OSParameters
{
	int mem_model;		   /* 0=None, 1=Fixed, 2=Variable   */
	int mem_fix_blksize;   /* F: Number of bytes per block  */
	int mem_fix_blksaval;  /* F: Number of available blocks */
	int mem_var_maxsize;   /* V: Maximum block size         */
	int mem_var_totsize;   /* V: Total available memory     */
	int pro_max_tasks;	 /* Maximum Processes allowed     */
	int init_quantum;	  /* Default quantum size          */
	int disk_units;		   /* Number of disk units avail.   */
	int tape_units;		   /* Number of tape units avail.   */
	int cdrom_units;	   /* Number of CDROM units avail.  */
	int every_n_units;	 /* If not zero, print #3 detail  */
						   /*   output every n units        */
	char pro_algorithm[8]; /* FIFO : first-in, first-out    */
						   /* IPRI : initial priority       */
						   /* MLFQ : multi-level fb queue   */
};

struct ProgramRecord
{
	int process_priority;	  /* User assigned priority        */
	int process_memsize;	   /* Load module memory requirement*/
	int run_info[10][3] = {0}; /* 10 groups of 3 integers:      */
							   /*    0 = CPU units              */
							   /*    1 = I/O units              */
							   /*    2 = I/O device types:      */
							   /*        1 = DEV_DISK           */
							   /*        2 = DEV_TAPE           */
							   /*        3 = DEV_CD             */
							   /*  0 thru 9 is the 10 cycles    */
	char process_name[8];	  /* User name of process 7 chars  */
};

struct PCB
{
	int id;					   /* Unique process id             */
	std::string name;		   /* User name of process          */
	int initial_priority;	  /* User assigned priority        */
	int memsize;			   /* Load module memory requirement*/
	int run_info[10][3] = {0}; /* 10 groups of 3 integers:      */
							   /*    0 = CPU units              */
							   /*    1 = I/O units              */
							   /*    2 = I/O device type        */
							   /*        1 = DEV_DISK           */
							   /*        2 = DEV_TAPE           */
							   /*        3 = DEV_CD             */
							   /*  0 thru 9 is the 10 cycles    */
	int cur_ctr;			   /* Current CPU count for a cycle */
	std::string state;		   /* E=Exec,B=Blocked,R=Ready,     */
							   /* D=Done, H=Held                */
	int total_cpu;			   /* Total CPU currently used      */
	int total_ios;			   /* Total I/Os currently used     */
	int start_time;			   /* First Time Process Started    */
	int end_time;			   /* Time Process Ended.           */
	int sim_ri_idx;			   /* Current run_info index: 0-9   */
};

struct EventEntry
{
	int time;		  /* Time Event should be invoked  */
	int pid;		  /* Process Id of event           */
	std::string type; /* Type of event:                */
					  /*  T = Time Out                 */
					  /*  I = I/O Completion           */

	bool operator<(const EventEntry &rhs) const
	{
		return time < rhs.time;
	}
};

struct DeviceEntry
{
	int did;		   /* device ID. Unique within type */
	int pid;		   /* current PID using this device */
	std::string state; /* State of device: Aval/Busy    */
};

struct ReadyListEntry
{
	int pid;			  /* PID of process                */
	int current_priority; /* System assigned priority      */

	bool operator<(const ReadyListEntry &rhs) const
	{
		return current_priority > rhs.current_priority;
	}
};

struct BlockListEntry
{
	int pid;			  /* PID of process                */
	int current_priority; /* System assigned priority      */
	std::string state;	/* State of service request:     */
						  /* IO_WORKING or IO_PENDING Dev  */
						  /* or IO_DONE but not yet removed*/
	int dtype;			  /* Device Type: DEV_DISK, etc.   */
	int did;			  /* Device ID if IO_WORKING       */

	bool operator<(const BlockListEntry &rhs) const
	{
		return current_priority > rhs.current_priority;
	}
};

struct MemoryBlockEntry
{
	int state; /* MEM_FREE=0, MEM_USED=1        */
	int pid;   /* PID of process, or if OS's 0. */
};