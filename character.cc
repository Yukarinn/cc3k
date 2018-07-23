#include <cmath>
#include <iostream>
#include "character.h"
#include "vampire.h"
#include "goblin.h"
#include "halfling.h"
#include "elf.h"

using namespace std;

Character::Character(string name, char display, int hp, int atk, int def, ObjectType objectType): Object(objectType, display), name{name},  hp{hp}, atk{atk}, def{def} {}

Character::~Character() {}

void Character::setHp(int hp) {
	this->hp = hp;
}

void Character::setAtk(int atk) {
	this->atk = atk;
}

void Character::setDef(int def) {
	this->def = def;
}

string Character::getName() const {
	return name;
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

