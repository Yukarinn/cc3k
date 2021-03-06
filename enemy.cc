#include "enemy.h"
#include "treasure.h"
#include "player.h"
#include "cell.h"

#include <cstdlib>

using namespace std;

Enemy::Enemy(string name, char display, int hp, int atk, int def): Character(name, display, hp, atk, def, ObjectType::Enemy) {}

Enemy::~Enemy() {}

// if player is adjacent, hit the player
// otherwise move rnadomly
string Enemy::act() {
	if (findPlayer() != nullptr) {
		Player* player = dynamic_cast<Player*>(findPlayer()->getObject());
		return strike(player);
	}
	move();
	return "";
}

// moves the enemy mob to a random free neighbour
// if possible
void Enemy::move() {
	Cell* cell = this->getCell();
	vector<Cell*> neighbours = cell->getNeighbours();
	int r = rand() % neighbours.size();
	bool free = false; // any free neighbours?
	for (auto each: neighbours) {
		if (each->enemyCanMoveTo())
			free = true;
	}
	if (!free) // can't move
		return;
	while (!neighbours[r]->enemyCanMoveTo()) {
		r = rand() % neighbours.size();
	}
	neighbours[r]->setObject(this);
	cell->clearObject();
	this->setCell(neighbours[r]);
}

// finds player cell if one of the neighbours
// else returns nullptr
Cell* Enemy::findPlayer() {
	Cell* cell = this->getCell();
	for (Cell* each: cell->getNeighbours()) {
		if (each->getObject() && each->getObject()->getType() == ObjectType::Player) {
			return each;
		}
	}
	return nullptr;
}

// drops treasure, then clears enemy cell to nullptr to
// effectively deactivate the enemy
// until floor deletion to avoid dangling
// pointers
void Enemy::drop() { //call before delete
	Cell* cell = this->cell;
	cell->clearObject();
	Treasure* treasure;
	if (rand() % 2) {
		treasure = new Treasure(TreasureType::SM);	
	} else {
		treasure = new Treasure(TreasureType::NO);
	}
	cell->setObject(treasure);
	treasure->setCell(cell);
	this->cell = nullptr;
}

string Enemy::strike(Player* other) {
	int times = 1;
	string ret = "";
	if (name == "Elf")
		times ++;
	for (int i = 0; i < times; i ++) {
		int damage = ceil((100.0/(100.0 + other->getDef())) * atk);
		if (name == "Orc" && other->getName() == "Goblin") {
			damage = ceil(1.5 * (100.0/(100.0 + other->getDef())) * atk);
		}
		if (rand() % 2) {
			other->setHp(max(0, other->getHp() - damage));
			ret += name + " deals " + to_string(damage) + " damage to PC. ";
		} else {
			ret += name + " missed PC. ";
		}
	}	
	return ret;
}
