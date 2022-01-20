#include "LogicalElement.h"

InElement::InElement(int new_id, bool val) {
	id = new_id;
	out_val = val;
}
void InElement::calcValue(LogicalElement** scheme) {
	return;
}
void InElement::getInsValues(LogicalElement** scheme) {
	return;
}