#pragma once

#include "Human.h"

class Pirate : public Human
{
public:
	Pirate();
	~Pirate();
	void attack(int x, int y, Ship &s);

	void action(Ship& statek);
	void positiveAnswer(Ship& statek);
	void negativeAnswer(Ship& statek);
	static bool busy;
private:

	static unsigned int chance;
};

