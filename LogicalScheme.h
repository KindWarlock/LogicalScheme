#pragma once
#include "LogicalElement.h"
#include <string>
#include <map>

class LogicalScheme
{
	int id_cnt;
	LogicalElement **elems;
	int capacity;
	std::map<std::string, int> names_mapping;

	void extendArray();
	int checkIds(int* ids, int ids_num);
	void createMap();
public:
	LogicalScheme();
	~LogicalScheme();
	bool append(std::string elem_type, int* new_ins_id, int new_ins_num);
	LogicalElement& operator[] (int index);
	bool calcValue(bool* input_vals, int input_num);
};
