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

	void addServ(string id, string desc, string loc, string area) {
		if (this->r.addRepo(id,desc,loc,area) == false) throw exception("Failed!");
		notify();
	}

	vector<Building> sortare(string area)
	{
		vector<Building> all{ this->r.getVB() };
		vector<Building> rez;
		Building office;
		int i = 0;
		while (i < all.size()) {
			if (all.at(i).getArea() == area)
			{
				rez.push_back(all.at(i));
				all.erase(all.begin() + i);
			}
			else if (all.at(i).getArea() == "office")
			{
				office = all.at(i);
				all.erase(all.begin() + i);
			}
			else i++;
		}
		std::sort(all.begin(), all.end(), [](Building b1, Building b2) {

			return b1.getArea() < b2.getArea();
			});
		for (auto el : all)
			rez.push_back(el);
		rez.push_back(office);
		return rez;
	}

	vector<Ethnologist> getSVE() { return this->r.getVE(); }
	vector<Building> getSVB() { return this->r.getVB(); }
};