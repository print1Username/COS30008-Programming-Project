#pragma once
#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Player {
private:
	string name;
	int hp;

	int damage;

	struct position {
		float x;
		float y;
	} pos;

	const int maxhp;
	const int maxequip = 10;

	const double speed = 2.0;

public:
	Player(string n, int h, int d);

	// Getter
	string getName();
	int getHp();
	int getMaxHp();
	float getPositionX();
	float getPositionY();
	double getSpeed();
	int getDamage();

	// Setter
	int setHp(int h);
	int setPosition(int x, int y);
	void healing(int h);
	void damaging(int h);

	string printPlayer();

	friend ostream & operator<<(ostream & s, Player & p);

	void ResetPlayer();
};