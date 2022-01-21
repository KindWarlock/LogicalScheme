#include "LogicalElement.h"

void LogicalElement::getInsValues(LogicalElement** scheme) {
	for (int i = 0; i < ins_num; i++) {
		int in_id = ins_id[i];
		ins_val[i] = (*scheme[in_id]).getValue();
	}
}

void LogicalElement::setId(int new_id)
{
	id = new_id;
}

void LogicalElement::changeInsForward(int new_id)
{
	for (int i = 0; i < ins_num; i++) {
		if (ins_id[i] > new_id) {
			ins_id[i]++;
		}
	}
}

void LogicalElement::changeInsBackward(int new_id)
{
	for (int i = 0; i < ins_num; i++) {
		if (ins_id[i] >= new_id) {
			ins_id[i]--;
		}
	}
}

void LogicalElement::appendIn(int new_id)
{
	if (ins_num == 3) {
		throw ManyInsException();
		return;
	}
	ins_id[ins_num++] = new_id;
}

bool LogicalElement::getValue() {
	return out_val;
}

bool LogicalElement::checkIns(int vals_num) {
	for (int i = 0; i < ins_num; i++) {
		// åñëè ññûëàåòñÿ íà íà÷àëüíûé ýëåìåíò, íî â íåì íåò ââåäåííûõ äàííûõ
		if (ins_id[i] < 3 && ins_id[i] > vals_num) {
			return false;
		}
	}
	return true;
}

int LogicalElement::getInsNum()
{
	return ins_num;
}