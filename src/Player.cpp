#include "Player.h"

Player::Player(string n, int h, int d) : 
	name(n), hp(h), maxhp(h), pos{ 0, 0 }, damage(d) {}

// Getter
string Player::getName() {
	return name;
}

int Player::getHp() {
	return hp;
}

int Player::getMaxHp() {
	return maxhp;
}

float Player::getPositionX() {
	return pos.x;
}

float Player::getPositionY() {
	return pos.y;
}

double Player::getSpeed() {
	return speed;
}

int Player::getDamage() {
	return damage;
}

// Setter
int Player::setHp(int h) {
	if ( h < 0 ) {
		hp = 0;
	} else if ( h > maxhp ) {
		hp = maxhp;
	} else {
		hp = h;
	}
	return hp;
}

int Player::setPosition(int x, int y) {
	pos.x = static_cast<float>(x);
	pos.y = static_cast<float>(y);
	return 0;
}

void Player::healing(int h) {
	setHp(hp + h);
}

void Player::damaging(int h) {
	setHp(hp - h);
}

string Player::printPlayer() {
	string p;
	p += "Player Name: " + name + "\n";
	p += "HP: " + to_string(hp) + "/" + to_string(maxhp) + "\n";
	p += "Position: (" + to_string(pos.x) + ", " + to_string(pos.y) + ")\n";
	return p;
}

ostream & operator<<(ostream & s, Player & p) {
	s << p.printPlayer();
	return s;
}

void Player::ResetPlayer() {
	hp = maxhp;
	pos.x = 0;
	pos.y = 0;
}