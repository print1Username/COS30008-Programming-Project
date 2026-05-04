#include "Monster.h"

Monster::Monster() :
	name(""), hp(0), maxhp(0), pos({ 0, 0 }), damage(0) {}

Monster::Monster(string n, int h, int d) :
	name(n), hp(h), maxhp(h), damage(d) {
	cout << "Monster " << name << " created." << endl;
}

// Getter
string Monster::getName() {
	return name;
}

int Monster::getHp() {
	return hp;
}

int Monster::getMaxHp() {
	return maxhp;
}

float Monster::getPositionX() {
	return pos.x;
}

float Monster::getPositionY() {
	return pos.y;
}

double Monster::getSpeed() {
	return speed;
}

int Monster::getDamage() {
	return damage;
}

// Setter
void Monster::setHp(int h) {
	hp = h;
	if ( hp < 0 )
		hp = 0;
	if ( hp > maxhp )
		hp = maxhp;
}

void Monster::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Monster::healing(int h) {
	setHp(hp + h);
}

void Monster::damaging(int h) {
	setHp(hp - h);
}

string Monster::printMonster() {
	string m;
	m += "Monster:\n";
	m += "Name: " + name + "\n";
	m += "HP: " + to_string(hp) + "/" + to_string(maxhp) + "\n";
	return m;
}

ostream & operator<<(ostream & s, Monster & m) {
	s << m.printMonster();
	return s;
}