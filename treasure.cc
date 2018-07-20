#include "treasure.h"
#include "player.h"

Treasure::Treasure(TreasureType treasureType): Item(ObjectType::Treasure), treasureType{treasureType} {}

Treasure::~Treasure() {}

TreasureType Treasure::getTreasureType() const {
	return treasureType;
}
