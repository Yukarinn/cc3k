#include "enemy.h"
#include "treasure.h"
#include "player.h"
#include "cell.h"

#include <cstdlib>

using namespace std;

Enemy::Enemy(string name, int hp, int atk, int def): Character(name, hp, atk, def, ObjectType::Enemy) {}

Enemy::~Enemy() {}

void Enemy::act() {
	if (findPlayer() != nullptr) {
		Player* player = dynamic_cast<Player*>(findPlayer()->getObject());
		player->beStruckBy(*this);
		return;
	}
	Cell* cell = this->getCell();
	vector<Cell*> neighbours = cell->getNeighbours();
	int r = rand() % neighbours.size();
	while (!neighbours[r]->enemyCanMoveTo()) {
		r = rand() % neighbours.size();
	}
	neighbours[r]->setObject(this);
	cell->clearObject();
	this->setCell(neighbours[r]);
}

Cell* Enemy::findPlayer() {
	Cell* cell = this->getCell();
	for (Cell* each: cell->getNeighbours()) {
		if (each->getObject()->getType() == ObjectType::Player) {
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
