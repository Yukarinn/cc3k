#include "player.h"
#include "treasure.h"
#include "potion.h"
#include "cell.h"
#include "enemy.h"
#include "merchant.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(string name, int hp, int atk, int def, int maxHp, int baseAtk, int baseDef):
	Character(name, '@', hp, atk, def, ObjectType::Player), maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef} {}

Player::~Player() {
	if (onHoard) delete onHoard;
}

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

void Player::reset() {
	this->setAtk(baseAtk);
	this->setDef(baseDef);
}

void Player::drink(Potion* potion) {
	switch(potion->getPotionType()) {
		case PotionType::RH:
			if (name == "Vampire")
				setHp(getHp() + 10);
			else
				setHp(min(maxHp, getHp() + 10));
			break;
		case PotionType::BA:
			setAtk(getAtk() + 10);
			break;
		case PotionType::BD:
			setDef(getDef() + 10);
			break;
		case PotionType::PH:
			setHp(max(0, getHp() - 10));
			break;
		case PotionType::WA:
			setAtk(max(0, getAtk() - 10));
			break;
		case PotionType::WD:
			setDef(max(0, getDef() - 10));
			break;
	}
	delete potion;
}

bool Player::pick(Treasure* treasure) {
	switch (treasure->getTreasureType()) {
		case TreasureType::SM:
			gold ++;
			delete treasure;
			return true;
		case TreasureType::NO:
			gold += 2;
			delete treasure;
			return true;
		case TreasureType::ME:
			gold += 4;
			delete treasure;
			return true;
		case TreasureType::HN:
			gold += 6;
			delete treasure;
			return true;
		case TreasureType::HD:
			onHoard = treasure;
			return false;
	}
}

string Player::move(Cell* cell) {
	string ret =  "";
	Cell* prev = this->cell;
	prev->clearObject();
	if (onHoard) {
		prev->setObject(onHoard);
		onHoard = nullptr;
	}
	ret += grab(cell);
	cell->setObject(this);
	this->setCell(cell);
	return ret;
}

string Player::grab(Cell* cell) {
	string ret = "";
		if (cell->getObject() && cell->getObject()->getType() == ObjectType::Treasure) {
		Treasure* treasure = dynamic_cast<Treasure*>(cell->getObject());
		string name = treasure->getName();
		if (pick(treasure))
			ret = "picks up " + name;
	}
	return ret;
}
string Player::spot() {
	string ret = "";
	Cell* cell = this->cell;
	vector<Cell*> neighbours = cell->getNeighbours();
	for (auto each: neighbours) {
		if (each->getObject() && each->getObject()->getType() == ObjectType::Potion) {
			ret += "a " + dynamic_cast<Potion*>(each->getObject())->getEffect() + ", ";		
		}
	}
	if (ret != "") {
		ret.pop_back();
		ret.pop_back();
	}
	return ret;
}


string Player::strike(Enemy* enemy) {
	int damage = ceil((100.0/(100.0 + enemy->getDef())) * atk);
	if (enemy->getName() == "Halfling" && rand() % 2) {
		return "PC's attack on the halfling missed (" + to_string(enemy->getHp()) + "HP). ";
	}
	if (enemy->getDisplay() == 'M') {
		Merchant::setAggro(true);	
	}
	enemy->setHp(max(0, enemy->getHp() - damage));
	
	string ret = "PC deals " + to_string(damage) + " damage to " + enemy->getDisplay() + " (" + to_string(enemy->getHp()) + "HP). ";
	if (name == "Vampire") {
		if (enemy->getName() == "Dwarf") {
			ret += "Lost 5 HP. ";
			hp -= 5;
			hp = max(hp, 0);
		} else {
			ret += "Drained 5 HP. ";
			hp += 5;
		}
	}
	
	if (enemy->getHp() == 0) {
		enemy->drop();
		if (name == "Goblin") {
			ret += "Stole 5 gold. ";
			gold += 5;	
		}
	}
	return ret;
}
