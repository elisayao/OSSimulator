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

#include "OSSimTypes.h"
#include <fstream>

namespace OSSimUtils
{
using namespace std;

bool ReadOSOSParameters(string filename, vector<OSParameters> &os_prarms)
{
	os_prarms.clear();
	ifstream fs(filename, ifstream::binary);

	if (!fs.is_open())
	{
		return false;
	}

	do
	{
		OSParameters new_entry;
		fs.read((char *)&new_entry, sizeof(OSParameters));
		os_prarms.push_back(new_entry);

	} while (!fs.eof());

	return true;
}

bool ReadProgramRecord(string filename, vector<ProgramRecord> &prog_records)
{
	prog_records.clear();
	ifstream fs(filename, ifstream::binary);

	if (!fs.is_open())
	{
		return false;
	}

	do
	{
		ProgramRecord new_entry;
		fs.read((char *)&new_entry, sizeof(ProgramRecord));
		prog_records.push_back(new_entry);

	} while (!fs.eof());

	return true;
}
} // namespace OSSimUtils
