#include "stdafx.h"
#include "Window.h"
#include "Planet.h"
#include "Ship.h"
#include "Pirate.h"

Ship::Ship()
{
	setTexture();
	setPosition();

	money = 10000;
	isStuck = false;
}


Ship::~Ship()
{
}

void Ship::fly(float& dt, wstring rozkaz, int counterLimit)
{
	movementCounter++;

		vx = vy = 0;
		if (rozkaz == L"lewo" && isStuck == false) 
			vx += -10;
	
		if (rozkaz == L"prawo" && isStuck == false) 
			vx += 65;
		
		if (rozkaz == L"gora" && isStuck == false) 
			vy += -10;
		
		if (rozkaz == L"dol" && isStuck == false) 
			vy += 65;
		
		if (movementCounter <= counterLimit)
		{
			comeBack();

			x += vx * dt;
			y += vy * dt;
		}
}

void Ship::flyTo(float& dt, Planet& p)
{
	Pirate pirat;
	while (this->getX() < p.getX() || this->getX() > p.getX() || this->getY() > p.getY() || this->getY() < p.getY() /*|| isStuck==false*/)
	{
		//pirat.attack(this->getX(), this->getY(), *this);
		if (this->getX() < p.getX())
		{
			this->fly(dt, L"prawo", 7000);
			this->focus(p);
		}
		else if (this->getX() > p.getX())
		{
			this->fly(dt, L"lewo", 7000);
			this->focus(p);
		}
		else if (this->getY() > p.getY())
		{
			this->fly(dt, L"gora", 7000);
			this->focus(p);
		}
		else if (this->getY() < p.getY())
		{
			this->fly(dt, L"dol", 7000);
			this->focus(p);
		}
	}
}


void Ship::comeBack()
{
	if (this->getX() > 460)
		this->x = 460;
	if (this->getX() < 30)
		this->x = 30;
	if (this->getY() < 30)
		this->y = 30;
	if (this->getY() > 460)
		this->y = 460;
}

void Ship::display()
{
	statek.setPosition(x, y);
	Window::draw(statek);
}

void Ship::focus(Planet& p)
{
	if (this->getX() > p.getX() &&
		this->getX() < p.getX() + 70 &&
		this->getY() > p.getY() &&
		this->getY() < p.getY() + 70
		)

		isStuck = true;
}


void Ship::setTexture()
{
	statekTekstura.loadFromFile("spaceShip.png");
	statek.setTexture(statekTekstura);
}

void Ship::setPosition(float x, float y)
{
	statek.setPosition(x,y);
	this->x = x; this->y = y;
}

void Ship::SetStuff(int stuff) {
	this->stuff = stuff;
}

int Ship::GetStuff() {
	return stuff;
}