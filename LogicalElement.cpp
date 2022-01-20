#include "LogicalElement.h"

void LogicalElement::getInsValues(LogicalElement** scheme) {
	for (int i = 0; i < ins_num; i++) {
		int in_id = ins_id[i];
		ins_val[i] = (*scheme[in_id]).getValue();
	}
}

bool LogicalElement::getValue() {
	return out_val;
}

bool LogicalElement::checkIns(int vals_num) {
	for (int i = 0; i < ins_num; i++) {
		// если ссылается на начальный элемент, но в нем нет введенных данных
		if (ins_id[i] < 3 && ins_id[i] > vals_num) {
			return false;
		}
	}
	return true;
}