#pragma once
#pragma once
#include<vector>
using std::vector;
class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
private:
	vector<Observer*> obs;
public:
	void addObs(Observer* ob) {
		obs.push_back(ob);
	}
	void notify() {
		for (auto ob : obs)
			ob->update();
	}
	void removeObs(Observer* ob)
	{
		obs.erase(std::remove(obs.begin(), obs.end(), ob), obs.end());
	}
};

