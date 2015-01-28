﻿#include "stdafx.h"

#include "BorderMan.h"
#include "Planet.h"
#include "Human.h"
#include "Console.h"

unsigned int BorderMan::chance;
bool BorderMan::busy = false;

BorderMan::BorderMan() {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	default_random_engine generator(seed);
	uniform_int_distribution<unsigned> distribution(1, 100);

	chance = distribution(generator);

	SetPrice(100);
}

BorderMan::~BorderMan(){}

void BorderMan::action(Ship& statek, Planet& p) {
	//if (p.visited == false) {
		wstring text, text2;
		text = to_wstring(Human::GetPrice());
		p.SetBoolFalse();
		text2 = L"Skorumpowana Obsługa Graniczna >> Zaplac " + text + L" albo spadaj!";
		Console::putTextLine(text2);
		BorderMan::busy = true;
		//cout << "Zaplac " << Human::GetPrice() << " albo spadaj!\n";
		/*int  temp;
		cin >> temp;
		if ((temp == 1) && (Human::GetPrice() < statek.getMoney())) {
		cout << "Dobra, wlatuj\nWitamy na plnecie\n";
		statek.setMoney(statek.getMoney() - Human::GetPrice());
		statek.isStuck = false;
		}
		else {
		cout << "Spadaj, nie chcê Ciê tu wiêcej widzieæ\n"; //Smuteg
		p.SetBoolFalse();
		statek.isStuck = false;
		}
		}*/
	//}
}

void BorderMan::negativeAns(Planet& p) {
	p.SetBoolFalse();
	Console::putTextLine(L"Skorumpowana Obsługa Graniczna >> Pff, tylko tyle? Nie pokazuj się tu więcej.");
	BorderMan::busy = false;
	p.visited = true;
}

void BorderMan::positiveAns(Planet& p, Ship& s) {
	if (p.CanWeShop() == true && GetPrice() <= s.getMoney()) {
		s.setMoney(s.getMoney() - GetPrice());
		Console::putTextLine(L"Przekupiona Obsługa Graniczna >> Ooo tak, moja kochane pinionżki :3");
		BorderMan::busy = false;
		p.SetBoolTrue();
		p.visited = true;
	}
	else {
		negativeAns(p);
	}
}

//Mo¿e dodamy coœ w main co po up³ywie np 30-60 sekund ustawi planety na dostêpne? 0o
//Planeta matka  ustawia wszystkie na true.