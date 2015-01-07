#pragma once

#include "Human.h"
#include "Ship.h"

using namespace std;

class BorderMan : public Human {
public:
	BorderMan();
	~BorderMan();

	void action(Ship& statek);

	void negativeAns(Planet& p);
	void positiveAns(Planet& p, Ship& s);
	static bool busy;
//private:
	static unsigned int chance;
};