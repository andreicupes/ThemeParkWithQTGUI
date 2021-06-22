#include "domain.h"

Ethnologist::Ethnologist(string a, string b)
{
	this->name = a;
	this->area = b;
}

string Ethnologist::getName()
{
	return this->name;
}

string Ethnologist::getArea()
{
	return this->area;
}
