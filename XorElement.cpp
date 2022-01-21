﻿#include "LogicalElement.h"

XorElement::XorElement(int new_id, int* new_ins_id, int new_ins_num) {
	//ñóùåñòâîâàíèå id áóäåò ïðîâåðÿòüñÿ â ìåòîäå ñõåìû
	if (new_ins_num > 3) {
		throw ManyInsException();
	}
	id = new_id;
	ins_num = new_ins_num;
	for (int i = 0; i < ins_num; i++) {
		ins_id[i] = new_ins_id[i];
	}
	out_val = false;
}
void XorElement::calcValue(LogicalElement** scheme) {
	getInsValues(scheme);
	out_val = ins_val[0] ^ ins_val[1];
	for (int i = 2; i < ins_num; i++) { // äëÿ óíèâåðñàëüíîñòè, ïðè ðàñøèðåíèè âîçìîæíîñòåé ïðîãðàììû
		out_val ^= ins_val[i + 1];
	}
}