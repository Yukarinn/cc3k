#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"

class Player;

enum TreasureType {
	SM, NO, ME, DR
}

class Treasure: public Item {
	TreasureType treasureType;
	public:
		Treasure(TreasureType treasureType);
		~Treasure();
		TreasureType getTreasureType() const;
}

#endif
