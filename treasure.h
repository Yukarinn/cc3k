#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"
#include <string>

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
    // get the value of the treasure (in string)
    // to display to the player
    // so the player knows how much gold it is
		std::string getName();	
};

#endif
