#include "LogicalElement.h"

NotElement::NotElement(int new_id, int new_in_id) {
	//ñóùåñòâîâàíèå id áóäåò ïðîâåðÿòüñÿ â ìåòîäå ñõåìû
	id = new_id;
	ins_num = 1;
	ins_id[0] = new_in_id;
	out_val = false;
}
void NotElement::calcValue(LogicalElement** scheme) {
	getInsValues(scheme);
	out_val = !ins_val[0];
}
void NotElement::changeInsForward(int new_id)
{
	if (ins_id[0] > new_id) {
		ins_id[0]++;
	}
}
void NotElement::changeInsBackward(int new_id)
{
	if (ins_id[0] > new_id) {
		ins_id[0]--;
	}
}
void NotElement::appendIn(int new_id)
{
	ins_id[0] = new_id;
}
void NotElement::getInsValues(LogicalElement** scheme) {
	int in_id = ins_id[0];
	ins_val[0] = (*scheme[in_id]).getValue();
}
