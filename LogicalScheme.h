#pragma once
#include "LogicalElement.h"
#include <string>
#include <map>

class LogicalScheme
{
	int id_cnt;
	LogicalElement** elems;
	int capacity;
	std::map<std::string, int> names_mapping;

	void extendArray();
	int checkIds(int* ids, int ids_num);
	int checkIds(int* ids_in, int ids_in_num, int* ids_out, int ids_out_num);
	void createMap();
	void moveIdsForward(int id_new);
	void moveIdsBackward(int id_new);
public:
	LogicalScheme();
	~LogicalScheme();
	bool append(std::string elem_type, int* new_ins_id, int new_ins_num);
	bool append(std::string elem_type, int* new_ins_id, int new_ins_num, int* new_outs_id, int new_outs_num);
	bool remove(int id);
	LogicalElement& operator[] (int index);
	bool calcValue(bool* input_vals, int input_num);
};
