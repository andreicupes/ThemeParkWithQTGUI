#pragma once
#include "domain.h"
#include <fstream>

class Repo {
private:
	vector<Ethnologist> ve;
	vector<Building> vb;
public:
	Repo() { vector<Ethnologist> a; this->ve = a; vector<Building> b; this->vb = b; }
	void readFile1() {
		ifstream file("ethnologists.txt");
		if (!file.is_open()) return;
		Ethnologist p;
		while (file >> p) {
			this->ve.push_back(p);
		}
		file.close();
	}
	void readFile2() {
		ifstream file2("buildings.txt");
		if (!file2.is_open()) return;
		Building s;
		while (file2 >> s) {
			this->vb.push_back(s);
		}
		file2.close();
	}

	vector<Ethnologist> getVE() { return this->ve; }
	vector<Building> getVB() {return this->vb; }
};