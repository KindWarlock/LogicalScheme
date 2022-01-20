#pragma once
#include <iostream>
#include <exception>

struct ManyInsException : public std::exception {
	const char* what() const throw ()
	{
		return "Too many inputs to the element.";
	}
};

class LogicalElement
{
protected:
	int id;
	int ins_num;
	int ins_id[3];
	bool ins_val[3];
	bool out_val;

	virtual void getInsValues(LogicalElement** scheme);
public:
	virtual void calcValue(LogicalElement** scheme) = 0;
	virtual bool getValue();
	virtual bool checkIns(int vals_num); // для кол-ва начальных значений
};

class OrElement : public LogicalElement {
public:
	OrElement(int new_id, int* ins_id, int new_ins_num);
	virtual void calcValue(LogicalElement** scheme);
};

class XorElement : public LogicalElement {
public:
	XorElement(int new_id, int* ins_id, int new_ins_num);
	virtual void calcValue(LogicalElement** scheme);
};

class AndElement : public LogicalElement {
public:
	AndElement(int new_id, int* ins_id, int new_ins_num);
	virtual void calcValue(LogicalElement** scheme);
};

class NotElement : public LogicalElement {
protected:
	virtual void getInsValues(LogicalElement** scheme);
public:
	NotElement(int new_id, int ins_id);
	virtual void calcValue(LogicalElement** scheme);
};

class InElement : public LogicalElement {
protected:
	virtual void getInsValues(LogicalElement** scheme);
public:
	InElement(int new_id, bool val);
	virtual void calcValue(LogicalElement** scheme);
};