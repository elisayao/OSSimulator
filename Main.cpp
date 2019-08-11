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

#include "OSSimTypes.h"
#include "OSSimUtils.h"
#include "OSSimulator.h"

#include <iostream>

#define VERSION 5

using namespace std;

int main(int argc, char *argv[])
{
	vector<OSParameters> os_instances;
	if (!OSSimUtils::ReadOSOSParameters("OS_OSP.DAT", os_instances))
	{
		cout << "Invalid OS parameters files" << endl;
	}

	vector<ProgramRecord> program_records;
	if (!OSSimUtils::ReadProgramRecord("OS_INP.DAT", program_records))
	{
		cout << "Invalid Program record files" << endl;
	}

	for (size_t i = 1; i < os_instances.size(); i++)
	{
		cout << "Starting O/S Simulation: " << i + 1 << ". "
			 << "Version " << VERSION << endl;
		cout << endl;

		OSSimulator simulator(os_instances[i]);
		int last_clock = simulator.Simulate(program_records);

		cout << "Ended O/S Simulation: " << i + 1 << ". Last clock: " << last_clock << endl;
		cout << endl;
	}

	return 0;
};