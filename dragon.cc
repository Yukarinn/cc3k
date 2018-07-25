#include "dragon.h"
#include "treasure.h"
#include "cell.h"
#include "player.h"
#include <iostream>

using namespace std;

Dragon::Dragon(): Enemy("Dragon", 'D',  150, 20, 20) {}

Dragon::~Dragon() {}

string Dragon::act() {
    Cell* cell = dragonFindPlayer();
    if (!cell)
        return "";
    Player* player = dynamic_cast<Player*>(cell->getObject());
    return strike(player);
}

Cell* Dragon::dragonFindPlayer() {
    Cell* cell1 = this->getCell();
    vector<Cell*> neighbours1 = cell1->getNeighbours();
    Cell* cell2 = hoard->getCell();
    vector<Cell*> neighbours2 = cell2->getNeighbours();
    for (auto neighbour: neighbours1) {
        if (neighbour->getObject() && neighbour->getObject()->getType() == ObjectType::Player) {
            return neighbour;
        }
    }
    for (auto neighbour: neighbours2) {
        if (neighbour->getObject() && neighbour->getObject()->getType() == ObjectType::Player) {
            return neighbour;
        }
    }
    return nullptr;
}

void Dragon::drop() {
    this->hoard->setTreasureType(TreasureType::HN);	
    this->hoard = nullptr;
    cell->clearObject();
    this->cell = nullptr;	
}

Treasure* Dragon::getHoard() const {
    return hoard;
}

void Dragon::setHoard(Treasure* hoard) {
    this->hoard = hoard;
}
