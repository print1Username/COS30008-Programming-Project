#include "Dungeon.h"

Dungeon::Dungeon() {
    // Allocate rooms on heap so references stay valid
    Room * rootRoom = new Room("Root Room");
    Room * room1 = new Room("Room 1");
    Room * room2 = new Room("Room 2");
    Room * room3 = new Room("Room 3");

    Room * room11 = new Room("Room 1.1");
    Room * room12 = new Room("Room 1.2");

    Room * room21 = new Room("Room 2.1");

    Room * room31 = new Room("Room 3.1");
    Room * room32 = new Room("Room 3.2");
    Room * room33 = new Room("Room 3.3");

    Room * room111 = new Room("Room 1.1.1");

    Room * room211 = new Room("Room 2.1.1");

    Room * room321 = new Room("Room 3.2.1");

    Room * room2111 = new Room("Room 2.1.1.1");



    // Build tree (Tree requires T&, so dereference pointers)
    root = new Tree<Room, CHILD>(*rootRoom);
    Tree<Room, CHILD> * t1 = new Tree<Room, CHILD>(*room1);
    Tree<Room, CHILD> * t2 = new Tree<Room, CHILD>(*room2);
    Tree<Room, CHILD> * t3 = new Tree<Room, CHILD>(*room3);

    Tree<Room, CHILD> * t11 = new Tree<Room, CHILD>(*room11);
    Tree<Room, CHILD> * t12 = new Tree<Room, CHILD>(*room12);

    Tree<Room, CHILD> * t21 = new Tree<Room, CHILD>(*room21);

    Tree<Room, CHILD> * t31 = new Tree<Room, CHILD>(*room31);
    Tree<Room, CHILD> * t32 = new Tree<Room, CHILD>(*room32);
    Tree<Room, CHILD> * t33 = new Tree<Room, CHILD>(*room33);

    Tree<Room, CHILD> * t111 = new Tree<Room, CHILD>(*room111);

    Tree<Room, CHILD> * t211 = new Tree<Room, CHILD>(*room211);

    Tree<Room, CHILD> * t321 = new Tree<Room, CHILD>(*room321);

    Tree<Room, CHILD> * t2111 = new Tree<Room, CHILD>(*room2111);



    // Add Dead Room to the vector
    deadRooms.push_back(t111);
    deadRooms.push_back(t33);

    winRoom = t321;

    // Attach to structure
    // Root Room
    root->attachTree(0, t1);
    root->attachTree(1, t2);
	root->attachTree(2, t3);

    // Room 1
    t1->attachTree(0, t11);
    t1->attachTree(1, t12);

    // Room 1.1
    t11->attachTree(0, t111);

    // Room 2
    t2->attachTree(0, t21);

    // Room 2.1
    t21->attachTree(0, t211);

    // Room 2.1.1
    t211->attachTree(0, t2111);

    // Room 3
    t3->attachTree(0, t31);
    t3->attachTree(1, t32);
    t3->attachTree(2, t33);

    // Room 3.2
    t32->attachTree(0, t321);

    // Spawn monster
    // Root Room Monster
    Monster m("M", 10, 2);
    m.setPosition(600.f, 600.f);

    root->getKey().addMonster(m);  // Safe & correct

    // Room 1 Monster
    Monster m1a("M1A", 20, 4);
	m1a.setPosition(400.f, 400.f);
	root->getChild(0)->getKey().addMonster(m1a);

	Monster m1b("M1B", 15, 3);
	m1b.setPosition(700.f, 200.f);
	root->getChild(0)->getKey().addMonster(m1b);

	// Room 2 Monster
	Monster m2a("M2A", 50, 1);
	m2a.setPosition(300.f, 500.f);
	root->getChild(1)->getKey().addMonster(m2a);

    // Room 2.1 Monster
    Monster m21a("M21A", 100, 100);
    m21a.setPosition(100.f, 100.f);
    root->getChild(1)->getChild(0)->getKey().addMonster(m21a);

    // Room 3 Monster
	Monster m3a("M3A", 1, 20);
	m3a.setPosition(800.f, 300.f);
	root->getChild(2)->getKey().addMonster(m3a);

    // Room 3.3 Monster
    Monster m33a("M33A", 20, 10);
    m33a.setPosition(500.f, 100.f);
    root->getChild(2)->getChild(2)->getKey().addMonster(m33a);

    Monster m33b("M33B", 20, 10);
    m33b.setPosition(500.f, 200.f);
    root->getChild(2)->getChild(2)->getKey().addMonster(m33b);

    Monster m33c("M33C", 20, 10);
    m33c.setPosition(500.f, 300.f);
    root->getChild(2)->getChild(2)->getKey().addMonster(m33c);

    Monster m33d("M33D", 20, 10);
    m33d.setPosition(500.f, 400.f);
    root->getChild(2)->getChild(2)->getKey().addMonster(m33d);

    // Start at root
    current = root;

    cout << endl << endl;
}

Room & Dungeon::GetCurrentRoom() {
    return current->getKey();
}

bool Dungeon::IsAtRoot() {
    return current == root;
}

int Dungeon::SubRoomSize() {
    return current->getSize();
}

int Dungeon::CurrentMonsterSize() {
    return current->getKey().getMonsterCount();
}

string Dungeon::MonsterName(int index) {
    if ( index < 0 || index >= current->getKey().getMonsterCount() )
        throw out_of_range("Invalid monster index.");

    Monster & m = current->getKey().getMonsterRef(index);
    return m.getName();
}

bool Dungeon::CheckPlayerDead() {
    for ( auto * dead : deadRooms ) {
        if ( current == dead )
            return true;
    }
    return false;
}

bool Dungeon::CheckPlayerWin() {
    return current == winRoom;
}

void Dungeon::MoveRoom(int index) {
    if ( index < 0 || index >= SubRoomSize() )
        throw out_of_range("Invalid room index.");

    Tree<Room, CHILD> * next = current->getChild(index);
    if ( next == Tree<Room, CHILD>::NIL )
        return;

    current = next;
}

void Dungeon::MoveParentRoom() {
    if ( current->getParent() != nullptr )
        current = current->getParent();
    else 
        return;
}

void Dungeon::ResetDungeon() {
    current = root;
}