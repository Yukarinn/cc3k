#include "player.h"

using namespace std;

Player::Player(string name, int hp, int atk, int def, int max_hp, int base_hp, int base_def):
	Character(name, hp, atk, def, ObjectType::Player), max_hp{max_hp}, base_hp{base_hp}, base_def{base_def} {}

Player::~Player() {}

int Player::getMaxHp() const {
	return maxHp;
}

int Player::getBaseAtk() const {
	return baseAtk;
}

int Player::getBaseDef() const {
	return baesDef;
}

int getGold() const {
	return gold;
}

void setgold(int gold) {
	this->gold = gold;
}

void die() {

}
