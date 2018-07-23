#include "dragon.h"
#include "treasure.h"

using namespace std;

Dragon::Dragon(): Enemy("Dragon", 'D',  150, 20, 20) {}

Dragon::~Dragon() {}

void Dragon::drop() {
	this->hoard->setTreasureType(TreasureType::HN);	
}

Treasure* Dragon::getHoard() const {
	return hoard;
}

void Dragon::setHoard(Treasure* hoard) {
	this->hoard = hoard;
}
