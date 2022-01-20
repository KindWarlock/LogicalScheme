#include "LogicalElement.h"

NotElement::NotElement(int new_id, int new_in_id) {
	//существование id будет провер€тьс€ в методе схемы
	id = new_id;
	ins_num = 1;
	ins_id[0] = new_in_id;
	out_val = false;
}
void NotElement::calcValue(LogicalElement** scheme) {
	getInsValues(scheme);
	out_val = !ins_val[0];
}
void NotElement::getInsValues(LogicalElement** scheme) {
	int in_id = ins_id[0];
	ins_val[0] = (*scheme[in_id]).getValue();
}