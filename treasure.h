#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"

enum class TreasureType {
	SM, NO, ME, HD, HN // small, normal, merchant, hoard dragon, hoard none
};

class Treasure: public Item {
	TreasureType treasureType;
	public:
		Treasure(TreasureType treasureType);
		~Treasure();
		TreasureType getTreasureType() const;
		void setTreasureType(TreasureType treasureType);	
};

#endif
