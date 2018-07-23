#include "human.h"
#include "treasure.h"
#include "player.h"
#include "cell.h"
#include <cstdlib>

using namespace std;

Human::Human(): Enemy("Human",'H', 140, 20, 20) {}

Human::~Human() {}

void Human::drop() {
	Cell* cell = this->cell;
	cell->clearObject();
	Treasure* treasure1 = new Treasure(TreasureType::NO);
	Treasure* treasure2 = new Treasure(TreasureType::NO);
	
	cell->setObject(treasure1);
	treasure1->setCell(cell);
	
	vector<Cell*> neighbours = cell->getNeighbours();
	int r = rand() % neighbours.size();
	while (neighbours[r]->getObject() != nullptr && neighbours[r]->getObject()->getType() != ObjectType::Player) {
		r = rand() % neighbours.size();
	}
	Cell* cell2 = neighbours[r];
	if (cell2->getObject() == nullptr) {
		cell2->setObject(treasure2);
		treasure2->setCell(cell2);
	} else {
		Player* player = dynamic_cast<Player*>(cell2->getObject());
		player->setGold(player->getGold() + 4);
		delete treasure2;
	}
	this->cell = nullptr;
}

