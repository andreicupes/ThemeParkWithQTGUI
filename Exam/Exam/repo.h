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

	bool addRepo(string id, string desc, string loc, string area) {
		if (desc == "" || loc=="") return false;
		vector<string> result;
		string loc1 = loc;
		stringstream ss(loc);
		string token;
		while (getline(ss, token, ' '))
			result.push_back(token);
		for (auto it : this->vb) {
			vector<string> m = it.getLoc();
			for (auto j : result)
				for (auto k : m) if (j == k) return false;
			if (it.getID() == id) return false;
		}
		for (int i = 0; i < result.size() - 1; i++)
			if (abs(result[i][0] - result[i + 1][0] + result[i][1] - result[i + 1][1]) > 1) return false;
		Building b{ id,desc,area,result };
		this->vb.push_back(b);
	}

	bool updRepo(string id, string desc, string loc) {
		if (desc == "" || loc == "") return false;
		vector<string> result;
		string loc1 = loc;
		stringstream ss(loc);
		string token;
		while (getline(ss, token, ' '))
			result.push_back(token);
		for (int i = 0; i < result.size() - 1; i++)
			if (abs(result[i][0] - result[i + 1][0] + result[i][1] - result[i + 1][1]) > 1) return false;
		for (auto &it : this->vb) {
			if (id == it.getID()) { it.setDesc(desc); it.setLoc(result); return true; }
		}
	}

	vector<Ethnologist> getVE() { return this->ve; }
	vector<Building> getVB() {return this->vb; }
};