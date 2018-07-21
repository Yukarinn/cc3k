#include <cmath>
#include "character.h";

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

void Character::strike(Character &other) {
	int dmg = ceil((100/(100+other.getDef()))*this->atk);
}

void Character::beStruckBy(Character &other) {
	other.strike(*this);
}

