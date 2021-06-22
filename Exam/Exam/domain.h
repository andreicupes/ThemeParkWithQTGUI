#pragma once
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Ethnologist {
private:
	string name;
	string area;
public:
	Ethnologist(){}
	Ethnologist(string a, string b);
	string getName();
	string getArea();

	friend istream& operator>> (istream& stream, Ethnologist& e) {
		string line;
		getline(stream, line);
		vector<string> result;
		stringstream ss(line);
		string token;
		while (getline(ss, token, ';'))
			result.push_back(token);
		if (result.size() != 2) return stream;
		e.name = result[0];
		e.area = result[1];
		return stream;
	}

	friend ostream& operator<<(ostream& stream, Ethnologist& e) {
		stream << e.name << ";" << e.area << "\n"; return stream;
	}
};


class Building {
private:
	string id;
	string desc;
	string area;
	vector<string> loc;
public:
	Building(){}
	Building(string a, string b, string c, vector<string> d) { this->id = a; this->desc = b; this->area = c; this->loc = d; }
	
	string getID() { return this->id; }
	string getArea() { return this->area; }
	string getDesc() { return this->desc; }
	vector<string> getLoc() { return this->loc; }
	string getCoord() {
		string s = ""; for (auto i : this->loc) { s += i; s += " "; } return s;
	}

	friend istream& operator>> (istream& stream, Building& b) {
		string line;
		getline(stream, line);
		vector<string> result;
		stringstream ss(line);
		string token;
		while (getline(ss, token, ';'))
			result.push_back(token);
		if (result.size() <=  3) return stream;
		b.id = result[0];
		b.desc = result[1];
		b.area = result[2];
		for (int i = 3; i < result.size(); i++)b.loc.push_back(result[i]);
		return stream;
	}

	friend ostream& operator<<(ostream& stream, Building& b) {
		stream << b.id << ";" << b.desc<<";"<<b.area;
		for (auto i : b.loc)stream << ";" << i;
		stream << "\n"; return stream;
	}
};