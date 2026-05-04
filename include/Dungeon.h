#pragma once
#include <iostream>
#include <vector>
#include "Room.h"
#include "Tree.h"
using namespace std;

class Dungeon {
private:
	const static int CHILD = 3;

	Tree<Room, CHILD> * root;
	Tree<Room, CHILD> * current;

	// The room will dead when player go
	vector<Tree<Room, CHILD> *> deadRooms;
	Tree<Room, CHILD> * winRoom;

public:
	Dungeon();

	// Getter
	Room & GetCurrentRoom();    // return reference

	bool IsAtRoot(); // Check if current room is root
	int SubRoomSize(); // Return the Number of Sub Rooms

	int CurrentMonsterSize(); // Get the Monster size in this current room
	string MonsterName(int index); // Get the Monster name in this current room

	bool CheckPlayerDead();
	bool CheckPlayerWin();

	void MoveRoom(int index); // Move into the room
	void MoveParentRoom(); // Move back to the previous room

	void ResetDungeon();
};