#pragma once
#include <iostream>
#include <string>
using namespace std;

class Monster {
private:
	string name;
	int hp;
	const int maxhp;

	const int damage;

	struct position {
		float x;
		float y;
	} pos;

	const double speed = 0.7;

public:
	Monster();
	Monster(string n, int h, int d);

	// Getter
	string getName();
	int getHp();
	int getMaxHp();
	float getPositionX();
	float getPositionY();
	double getSpeed();
	int getDamage();

	// Setter
	void setHp(int h);
	void setPosition(float x, float y);
	void healing(int h);
	void damaging(int h);

	string printMonster();

	friend ostream & operator<<(ostream & s, Monster & m);
};