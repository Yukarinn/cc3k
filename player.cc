#include "player.h"
#include "treasure.h"
#include "potion.h"
#include "cell.h"

using namespace std;

Player::Player(string name, int hp, int atk, int def, int maxHp, int baseAtk, int baseDef):
	Character(name, '@', hp, atk, def, ObjectType::Player), maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef} {}

Player::~Player() {}

int Player::getMaxHp() const {
	return maxHp;
}

int Player::getBaseAtk() const {
	return baseAtk;
}

int Player::getBaseDef() const {
	return baseDef;
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
	this->setAtk(baseAtk);
	this->setDef(baseDef);
}

void Player::drink(Potion* potion) {
	switch(potion->getPotionType()) {
		case PotionType::RH:
			setHp(getHp() + 10);
			return;
		case PotionType::BA:
			setAtk(getAtk() + 10);
			return;
		case PotionType::BD:
			setDef(getDef() + 10);
			return;
		case PotionType::PH:
			setHp(getHp() - 10);
			return;
		case PotionType::WA:
			setAtk(getAtk() - 10);
			return;
		case PotionType::WD:
			setDef(getDef() - 10);
			return;
	}
}

void Player::pick(Treasure* treasure) {
	switch (treasure->getTreasureType()) {
		case TreasureType::SM:
			gold ++;
			delete treasure;
			return;
		case TreasureType::NO:
			gold += 2;
			delete treasure;
			return;
		case TreasureType::ME:
			gold += 4;
			delete treasure;
			return;
		case TreasureType::HD:
			gold += 6;
			delete treasure;
			return;
		case TreasureType::HN:
			return;
	}
}

void Player::move(Cell* cell) {
	Cell* prev = this->cell;
	if (cell->getObject()->getType() == ObjectType::Treasure) {
		pick(dynamic_cast<Treasure*>(cell->getObject()));
	}
	cell->setObject(this);
	prev->clearObject();
	this->setCell(cell);
}
