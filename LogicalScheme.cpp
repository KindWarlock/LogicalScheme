#include "LogicalScheme.h"

LogicalScheme::LogicalScheme() {
	id_cnt = 3;
	capacity = 9;
	elems = new LogicalElement * [capacity];
	createMap();
	for (int i = 0; i < 3; i++) {
		LogicalElement* elem = new InElement(i, false);
		elems[i] = elem;
	}
}

LogicalScheme::~LogicalScheme()
{
	// óäàëÿåì âñå âûäåëåííûå óêàçàòåëè íà ýëåìåíòû
	for (int i = 0; i < id_cnt; i++) {
		delete elems[i];
	}
	delete[] elems;
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
			std::cout << "* " << elem_type << " id: " << id_cnt - 1 << std::endl;
		}
		break;
		case 2:
		{
			LogicalElement* elem = new XorElement(id_cnt, new_ins_id, new_ins_num);
			elems[id_cnt++] = elem;
			std::cout << "* " << elem_type << " id: " << id_cnt - 1 << std::endl;
		}
		break;
		case 3:
		{
			LogicalElement* elem = new AndElement(id_cnt, new_ins_id, new_ins_num);
			elems[id_cnt++] = elem;
			std::cout << "* " << elem_type << " id: " << id_cnt - 1 << std::endl;
		}
		break;
		case 4:
		{
			LogicalElement* elem = new NotElement(id_cnt, new_ins_id[0]);
			elems[id_cnt++] = elem;
			std::cout << "* " << elem_type << " id: " << id_cnt - 1 << std::endl;
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

bool LogicalScheme::append(std::string elem_type, int* new_ins_id, int new_ins_num, int* new_outs_id, int new_outs_num)
{
	int min_out = checkIds(new_ins_id, new_ins_num, new_outs_id, new_outs_num);
	if (min_out == -1) {
		return false;
	}
	try {
		switch (names_mapping[elem_type]) {
		case 1:
		{
			LogicalElement* elem = new OrElement(min_out, new_ins_id, new_ins_num);
			moveIdsForward(min_out);
			for (int i = 0; i < new_outs_num; i++) {
				elems[new_outs_id[i]]->appendIn(min_out);
			}
			elems[min_out] = elem;
			id_cnt++;
			std::cout << "* " << elem_type << " id: " << min_out << std::endl;
		}
		break;
		case 2:
		{
			LogicalElement* elem = new XorElement(min_out, new_ins_id, new_ins_num);
			moveIdsForward(min_out);
			for (int i = 0; i < new_outs_num; i++) {
				elems[new_outs_id[i]]->appendIn(min_out);
			}
			elems[min_out] = elem;
			id_cnt++;
			std::cout << "* " << elem_type << " id: " << min_out << std::endl;
		}
		break;
		case 3:
		{
			LogicalElement* elem = new AndElement(min_out, new_ins_id, new_ins_num);
			moveIdsForward(min_out);
			for (int i = 0; i < new_outs_num; i++) {
				elems[new_outs_id[i]]->appendIn(min_out);
			}
			elems[min_out] = elem;
			id_cnt++;
			std::cout << "* " << elem_type << " id: " << min_out << std::endl;
		}
		break;
		case 4:
		{
			LogicalElement* elem = new NotElement(min_out, new_ins_id[0]);
			moveIdsForward(min_out);
			for (int i = 0; i < new_outs_num; i++) {
				elems[new_outs_id[i]]->appendIn(min_out);
			}
			elems[min_out] = elem;
			id_cnt++;
			std::cout << "* " << elem_type << " id: " << min_out << std::endl;
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

bool LogicalScheme::remove(int id)
{
	if (id < 3) {
		std::cout << "Can't remove input element.\n";
		return false;
	}
	if (elems[id]->getInsNum() > 1 && id != id_cnt) {
		std::cout << "Can't delete element with 2 entrances.\n";
		return false;
	}
	if (id > id_cnt) {
		std::cout << "No such id.\n";
		return false;
	}
	delete elems[id];
	moveIdsBackward(id);
	id_cnt--;
	return false;
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



void LogicalScheme::extendArray() {
	capacity += 5;
	LogicalElement** old_ptr = elems;
	elems = new LogicalElement * [capacity];
	for (int i = 0; i < id_cnt; i++) {
		elems[i] = old_ptr[i];
	}
	delete[] old_ptr;
}
int LogicalScheme::checkIds(int* ids, int ids_num) {
	for (int i = 0; i < ids_num; i++) {
		if (ids[i] >= id_cnt || ids[i] < 3) {
			return ids[i];
		}
	}
	return -1;
}
int LogicalScheme::checkIds(int* ids_in, int ids_in_num, int* ids_out, int ids_out_num)
{
	int id_none = checkIds(ids_in, ids_in_num);
	if (id_none != -1) {
		std::cout << "No id " << id_none << std::endl;
		return -1;
	}
	id_none = checkIds(ids_out, ids_out_num);
	if (id_none != -1) {
		std::cout << "No id " << id_none << std::endl;
		return -1;
	}
	int min_out = INT_MAX;
	for (int i = 0; i < ids_in_num; i++) {
		for (int k = 0; k < ids_out_num; k++) {
			if (ids_out[k] < ids_in[i]) {
				return -1;
			}
			if (ids_out[k] < min_out) {
				min_out = ids_out[k];
			}
		}
	}
	return min_out;
}
void LogicalScheme::createMap() {
	names_mapping["or"] = 1;
	names_mapping["xor"] = 2;
	names_mapping["and"] = 3;
	names_mapping["not"] = 4;
}
void LogicalScheme::moveIdsForward(int id_new) {
	for (int i = id_cnt; i > id_new; i--) {
		elems[i] = elems[i - 1];
		elems[i]->setId(i);
		elems[i]->changeInsForward(i);
	}
}
void LogicalScheme::moveIdsBackward(int id_new)
{
	for (int i = id_cnt - 2; i >= id_new; i--) {
		elems[i] = elems[i + 1];
		elems[i]->setId(i);
		elems[i]->changeInsBackward(i);
	}
}
