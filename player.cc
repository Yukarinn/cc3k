#include "player.h"
#include "treasure.h"
#include "potion.h"
#include "cell.h"

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

int Player::getGold() const {
	return gold;
}

void Player::setGold(int gold) {
	this->gold = gold;
}

void Player::die() {

}

void Player::reset() {
	this->atk = baseAtk;
	this->def = baseDef;
}

void Player::drink(Potion& potion) {
	switch(potion.getPotionType()) {
		case PotionType::RH:
			hp += 10;
			return;
		case PotionType::BA:
			atk += 10;
			return;
		case PotionType::BD:
			def += 10;
			return;
		case PotionType::PH:
			hp -= 10;
			return;
		case PotionType::WA:
			atk -= 10;
			return;
		case PotionType::WD:
			def -= 10;
			return;
	}
}

void Player::pick(Treasure& treasure) {
	switch (treasure.getTreasureType()) {
		case TreasureType::SM:
			gold ++;
			return;
		case TreasureType::NO:
			gold += 2;
			return;
		case TreasureType::ME:
			gold += 4;
			return;
		case TreasureType::HD:
			gold += 6;
			return;
		case TreasureType::HN:
			return;
	}
}

void Player::move(Cell* cell) {
	Cell* prev = this->cell;
	if (cell->obj.ObjectType == ObjectType::Treasure) {
		pick(*(cell->obj));
	}
	delete cell->obj;
	cell->obj = this;
	prev->obj = nullptr;
}
