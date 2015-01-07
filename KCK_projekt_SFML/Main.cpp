#pragma once

#include "stdafx.h"

#include "Window.h"
#include "GameScreen.h"
#include "Ship.h"
#include "Planet.h"
#include "Console.h"
#include "Parameter.h"
#include "Pirate.h"
#include "Help.h"
#include "BorderMan.h"

void wykonaj_komende();
Ship s; Pirate p1; BorderMan b;
map<string, Planet*> planets;
float dt;

int main(int argv, char* argc[])
{
	//int hajsLeci = 232;

	Window::Window();
	GameScreen::GameScreen();
	Console::Console();

	sf::Clock clock;
	
	Parameter money(15, 550, 600, "arial.ttf", L"Pieni¹dze: ");


	 planets["Merkury"] = new Planet(140, 140, 1);
	 planets["Uran"] = new Planet(550, 550, 2); //70,440,2
	 planets["Jowisz"] = new Planet(290, 140, 3);
	 planets["Neptun"] = new Planet(420, 290, 4);
	 dt = clock.restart().asSeconds();
	while (Window::isOpen())
	{
		
		//auto dt = clock.restart().asSeconds();
		Help::podaj_statek(&s, &dt, planets);
		if (Help::flaga)
		{
			wykonaj_komende();
		}
		sf::Event event;
		while (Window::pollEvent(event))
		{
			Window::close(event);
			Window::halp();
			Console::doYourJob(event);
		}

	Window::clear();
	GameScreen::display();
	Console::display();

		p1.attack(s.getX(), s.getY(), s);
		money.display(s.getMoney());

		for (auto planet : planets)
		{
			planet.second->display();
		}


		string name = "Merkury";
		//s.fly(dt, L"lewo");
		//s.flyTo(dt, *planets[name]);
		s.setMoney(10000);
		s.display();

		

		
	Window::display();	

	}
	return 0;
}


void wykonaj_komende()
{
	if (Help::komenda == "lec")
	{
		if (Help::argument == "lewo" || Help::argument == "prawo" || Help::argument == "gora" || Help::argument == "dol")
		{
			s.fly(dt, Help::s2ws(Help::argument));
		}
		else
		{
			s.flyTo(dt, *planets[Help::argument]);
		}
	}
	if (Help::komenda == "plac")
	{
		if (Pirate::busy)
		{
			p1.positiveAnswer(s);
		}
		if (BorderMan::busy)
		{
			for each(pair<string, Planet*> a in planets)
			{
				if (a.second->onPlanet(s))
				{
					b.positiveAns(*a.second,s);
				}
			}
		}
	}


	Help::flaga = false;
}