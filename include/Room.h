#pragma once
#include <iostream>
#include <string>
#include "Tree.h"
#include "Monster.h"
#include "List.h"
using namespace std;

class Room {
private:
	string name;

	List<Monster> monsters;
	int maxMonster = 4;

public:
	Room();
	Room(string n);

	string getName();

	// Monster
	void addMonster(const Monster & m);
	void removeMonster(int index);
	string listMonster(int index);
	string printMonster();
	int getMonsterCount();
	Monster & getMonsterRef(int index);

	string printRoom();

	friend ostream & operator<<(ostream & s, Room & r);
};