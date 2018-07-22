#include "enemy.h"
#include "treasure.h"
#include <cstdlib>

using namespace std;

Enemy::Enemy(string name, int hp, int atk, int def) Character(name, hp, atk, def) {}

Enemy::~Enemy() {}

void Enemy::act() {
	if (findPlayer() != nullptr) {
		Player* player = findPlayer();
		player.beStruckBy(this);
		return;
	}
	Cell* cell = this->getCell();
	int r = rand() % cell->neighbours.size();
	while (cell->neighbours[r]->canMove()) {
		r = rand() % cell->neighbours.size();
	}
	cell->neighbours[r].
}

Cell* Enemy::findPlayer() {
	Cell* cell = this->getCell();
	for (Cell* each: cell->neighbours) {
		if (each->obj->objectType == ObjectType::Player) {
			return each;
		}
	}
	return nullptr;
}

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
}
