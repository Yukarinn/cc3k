#include "treasure.h"
#include "player.h"

Treasure::Treasure(TreasureType treasureType): Item(ObjectType::Treasure, 'G'), treasureType{treasureType} {}

Treasure::~Treasure() {}

TreasureType Treasure::getTreasureType() const {
	return treasureType;
}

void Treasure::setTreasureType(TreasureType treasureType) {
	this->treasureType = treasureType;
}
