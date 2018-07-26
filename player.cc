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
            if (name == "Vampire") // edge case for vampire who has no max hp
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

// gets gold and deletes treasure
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

// when moving, first check if there is
// treasure to be picked up, if so,
// grab it first
string Player::move(Cell* cell) {
    string ret =  "";
    Cell* prev = this->cell;
    prev->clearObject();
    if (onHoard) { // if the player was on hoard spot previous turn, put but hoard into the cell
        prev->setObject(onHoard);
        onHoard = nullptr;
    }
    ret += grab(cell);
    cell->setObject(this);
    this->setCell(cell);
    return ret;
}


// grabs treasure,
// if parameter argument is own cell
// try to grab the dragon hoard
string Player::grab(Cell* cell) {
    string ret = "";
    if (this->cell != cell && cell->getObject() && cell->getObject()->getType() == ObjectType::Treasure) {
        Treasure* treasure = dynamic_cast<Treasure*>(cell->getObject());
        string name = treasure->getName();
        if (pick(treasure))
            ret = "picks up " + name;
    }
		if (this->cell == cell && onHoard && onHoard->getTreasureType() == TreasureType::HN) {
			ret = "picks up " + onHoard->getName();
			delete onHoard;
			onHoard = nullptr;
			gold += 6;	
			cell->setObject(this);
		}
    return ret;
}


// spots nearby potions
string Player::spot() {
    string ret = "";
    Cell* cell = this->cell;
    vector<Cell*> neighbours = cell->getNeighbours();
    for (auto each: neighbours) {
        if (each->getObject() && each->getObject()->getType() == ObjectType::Potion) {
            ret += "a " + dynamic_cast<Potion*>(each->getObject())->getEffect() + ", ";		
        }
    }
    if (ret != "") { //return string shouldn't have ending comma
        ret.pop_back();
        ret.pop_back();
    }
    return ret;
}


// damage calculations
// accounting for different player/enemy interactions
string Player::strike(Enemy* enemy) {
    int damage = ceil((100.0/(100.0 + enemy->getDef())) * atk);
    if (enemy->getName() == "Halfling" && rand() % 2) {
        return "PC's attack on the halfling missed (" + to_string(enemy->getHp()) + " HP). ";
    }
    if (enemy->getDisplay() == 'M') {
        Merchant::setAggro(true);	
    }
    enemy->setHp(max(0, enemy->getHp() - damage));
    
    string ret = "PC deals " + to_string(damage) + " damage to " + enemy->getName() + " (" + to_string(enemy->getHp()) + " HP). ";
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
