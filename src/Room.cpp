#include "Room.h"

Room::Room() : 
	name("[Default]"), monsters() {
	cout << "Room " << name << " created." << endl;
}

Room::Room(string n) :
	name(n), monsters() {
	cout << "Room " << name << " created." << endl;
}

string Room::getName() {
	return name;
}

void Room::addMonster(const Monster & m) {
	if (monsters.size() >= maxMonster) {
		cout << "Cannot add more monsters. Max limit reached." << endl;
		return;
	}
	monsters.add(m);
}

void Room::removeMonster(int index) {
	monsters.remove(index);
}

string Room::listMonster(int index) {
	return monsters[index].printMonster();
}

string Room::printMonster() {
	string m;
	m += "Monsters in Room " + name + ":\n";
	for ( NodeIter<Monster> it = monsters.getIter(); it != it.end(); it++ ) {
		m += (*it).printMonster() + "\n";
	}
	return m;
}

string Room::printRoom() {
	string r;
	r += "Room:\n";
	r += "Name: " + name + "\n";
	return r;
}

ostream & operator<<(ostream & s, Room & r) {
	s << r.printRoom();
	return s;
}

int Room::getMonsterCount() {
	return monsters.size();
}

Monster & Room::getMonsterRef(int index) {
	if ( index < 0 || index >= monsters.size() )
		throw out_of_range("Monster index out of range");

	Monster & m = monsters[index];

	// NIL check
	if ( &m == &Node<Monster>::NIL.getData() )
		throw runtime_error("Attempted to access NIL monster node");

	return m;
}

