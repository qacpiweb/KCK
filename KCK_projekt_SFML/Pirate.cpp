#include "stdafx.h"
#include "Human.h"
#include "Ship.h"
#include "Pirate.h"
#include "Console.h"



unsigned int Pirate::chance;
bool Pirate::busy = false;


void Pirate::attack(int x, int y, Ship &s)
{

	if (((x % 70 == 0 || y % 70 == 0) && chance <=100) && s.isStuck == false)
	{
		s.isStuck = true; // <-- Bez tego dzia³a konsola :(
		s.setPosition(x, y);
		//cout << "YAARrrr! " << s.isStuck << endl;
		//Pirate::action(s);
		wstring text, temp2;
		temp2 = to_wstring(Pirate::GetPrice());
		Pirate::busy = true;
		text = L"Piraci >> Zaplac " + temp2 + L" albo spadaj!";
		Console::putTextLine(text);
	}

}

Pirate::Pirate()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	default_random_engine generator(seed);
	uniform_int_distribution<unsigned> distribution(1, 100);

	chance = distribution(generator);

	SetPrice(220);
}


Pirate::~Pirate()
{
}

/*void Pirate::action(Ship& statek){
	//cout << "Zaplac " << Pirate::GetPrice() << " albo spadaj!\n";
	wstring text, temp2;
	temp2 = to_wstring(Pirate::GetPrice());
	text = L"Zaplac " + temp2 + L" albo spadaj!";
	Console::putTextLine(text);
	int  temp = 1;
	cin >> temp;
	if ((temp == 1) && (Pirate::GetPrice() < statek.getMoney())) {
	cout << "Dobra, lec\n";
	statek.setMoney(statek.getMoney() - Pirate::GetPrice());
	statek.isStuck = false;
	}
	else {
	cout << "Nie pokazuj sie tu wiecej,  frajerze!\n";
	statek.SetStuff(0);
	statek.isStuck = false;
	}
	}
	
}*/
void Pirate::negativeAnswer(Ship& statek) {
	Console::putTextLine(L"Piraci >> Nie pokazuj sie tu wiecej, frajerze!");
	statek.SetStuff(0);
	statek.isStuck = false;
}

void Pirate::positiveAnswer(Ship& statek) {
	if (Pirate::GetPrice() < statek.getMoney()) {
		Console::putTextLine(L"Piraci >> Dobra, lec");
		Pirate::busy = false;
		statek.setMoney(statek.getMoney() - Pirate::GetPrice());
		statek.isStuck = false;
	}
	else {
		negativeAnswer(statek);
	}
}
