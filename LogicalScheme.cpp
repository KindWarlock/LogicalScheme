#include "LogicalScheme.h"

LogicalScheme::LogicalScheme() {
	id_cnt = 3;
	capacity = 9;
	elems = new LogicalElement*[capacity];
	createMap();
	for (int i = 0; i < 3; i++) {
		LogicalElement* elem = new InElement(i, false);
		elems[i] = elem;
	}
}

LogicalScheme::~LogicalScheme()
{
	// удаляем все выделенные указатели на элементы
	for (int i = 0; i < id_cnt; i++) {
		delete elems[i];
	}
	delete elems;
}

bool LogicalScheme::append(std::string elem_type, int* new_ins_id, int new_ins_num) {
	int id_none = checkIds(new_ins_id, new_ins_num);
	if (id_none != -1) {
		std::cout << "No id " << id_none << std::endl;
		return false;
	}
	try {
		switch (names_mapping[elem_type]) {
		case 1:
		{
			LogicalElement* elem = new OrElement(id_cnt, new_ins_id, new_ins_num);
			elems[id_cnt++] = elem;
		}
		break;
		case 2:
		{
			LogicalElement* elem = new XorElement(id_cnt, new_ins_id, new_ins_num);
			elems[id_cnt++] = elem;
		}
		break;
		case 3:
		{
			LogicalElement* elem = new AndElement(id_cnt, new_ins_id, new_ins_num);
			elems[id_cnt++] = elem;
		}
		break;
		case 4:
		{
			LogicalElement* elem = new NotElement(id_cnt, new_ins_id[0]);
			elems[id_cnt++] = elem;
		}
		break;
		default:
			std::cout << "No element with such name.\n";
			return false;
		}
	}
	catch (ManyInsException e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	if (id_cnt == capacity) {
		extendArray();
	}
	return true;
}

LogicalElement& LogicalScheme::operator[] (int index) {
	return *elems[index];
}

bool LogicalScheme::calcValue(bool* input_vals, int input_num) {
	if (input_num > 3) {
		throw ManyInsException();
		return false;
	}
	for (int i = 0; i < input_num; i++) {
		delete elems[i];
		elems[i] = new InElement(i, input_vals[i]);
	}
	for (int i = 3; i < id_cnt; i++) {
		if (!elems[i]->checkIns(input_num)) {
			std::cout << "Reference to an unassigned input.\n";
			return false;
		}
		elems[i]->calcValue(elems);
	}
	return elems[id_cnt - 1]->getValue();
}



void LogicalScheme::extendArray(){
	capacity += 5;
	LogicalElement** old_ptr = elems;
	elems = new LogicalElement*[capacity];
	for (int i = 0; i < id_cnt; i++) {
		elems[i] = old_ptr[i];
	}
	delete old_ptr;
}
int LogicalScheme::checkIds(int* ids, int ids_num) {
	for (int i = 0; i < ids_num; i++) {
		if (ids[i] >= id_cnt || ids[i] < 0) {
			return ids[i];
		}
	}
	return -1;
}
void LogicalScheme::createMap() {
	names_mapping["or"] = 1;
	names_mapping["xor"] = 2;
	names_mapping["and"] = 3;
	names_mapping["not"] = 4;
}