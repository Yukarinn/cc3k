#include "human.h"
#include "treasure.h"
#include <cstdlib>

using namespace std;

Human::Human(): Enemy("Human", 140, 20, 20) {}

Human::~Human() {}

void Human::drop() {
	Cell* cell = this->cell;
	cell->clearObject();
	Treasure* treasure1 = new Treasure(TreasureType::NO);
	Treasure* treasure2 = new Treasure(TreasureType::NO);
	cell->setObject(treasure1);
	
	int r = rand() % neighbours.size();
	while (neighbours[r]->getObject() != nullptr && neighbours[r]->getObject() != ObjectType::Player) {
		r = rand() % neighbours.size();
	}
	Cell* cell2 = neighbours[r];
	if (cell2->getObject() == nullptr) {
		cell2->setObject(treasure2);
	} else {
		Player* player = cell2->getObject();
		player->setGold(player->getGold() + 4);
		delete treasure2;
	}
}
