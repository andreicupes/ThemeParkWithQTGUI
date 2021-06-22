#pragma once
#include "observer.h"
#include "repo.h"
#include <qdebug.h>

class Service : public Observable {
private:
	Repo r;
public:
	Service() { Repo newRepo; this->r = newRepo; readFiles(); }

	void readFiles() { this->r.readFile1(); this->r.readFile2(); }

	vector<Ethnologist> getSVE() { return this->r.getVE(); }
	vector<Building> getSVB() { return this->r.getVB(); }
};