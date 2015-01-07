#pragma once
class Planet;
class Ship
{
public:
	Ship();
	~Ship();
	int getX() { return this->x; }
	int getY() { return this->y; }

	void display();

	void fly(float& dt, wstring rozkaz,  int counterLimit = 70);
	void flyTo(float& dt, Planet& p);
	void focus(Planet& p);
	
	int getMoney(){ return money; }
	void setMoney(int m){ money = m; }

	void SetStuff(int stuff);
	int GetStuff();

	void comeBack();
	void setPosition(float x = 460, float y = 460);
	bool isStuck;
	int movementCounter = 0;
	// movmentCounter jako public poniewaz funkcja wydajaca rozkaz np."prawo" bedzie musiala go zerowac
private:
	void setTexture();
	

	
	int vx, vy;
	int x, y;

	int money;
	int stuff;

	sf::Texture statekTekstura;
	sf::Sprite statek;
};

