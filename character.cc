#include <cmath>
#include "character.h";
#include "vampire.h";

using namespace std;

Character::Character(string name, int hp, int atk, int def, ObjectType objectType): Object(objectType), name{name}, hp{hp}, atk{atk}, def{def} {}

Character::~Character() {}

string Character::getName() const {
	return name;
}

void Character::setHp(int hp) {
	this->hp = hp;
}

void Character::setAtk(int atk) {
	this->atk = atk;
}

void Character::setDef(int def) {
	this->def = def;
}

int Character::getHp() const {
	return hp;
}

int Character::getAtk() const {
	return atk;
}

int Character::getDef() const {
	return def;
}

bool Character::strike(Character& other) {
	int dmg = ceil((100/(100+other.getDef()))*this->atk);
	other.setHp(other.getHp() - dmg);
	return true;
}

void Character::strike(Goblin& other) {
	other.strike(*this);
	return true;
}


bool Character::strike(Halfling& other) {
	if (rand() % 2) {
		int dmg = ceil((100/(100+other.getDef()))*this->atk);
		other.setHp(other.getHp() - dmg);
		return true;
	} 
	cout << "attack missed" << endl;
	return false;
	
}

void Character::beStruckBy(Character& other) {
	other.strike(*this);
}

void Character::beStruckBy(Vampire& other) {
	if (other.strike(*this))
		other.setHp(other.getHp() + 5);
}

void Character::beStruckBy(Elf& other) {
	other.strike(*this);
	other.strike(*this);
}

