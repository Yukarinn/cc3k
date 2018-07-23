#ifndef POTION_H
#define POTION_H
#include <vector>
#include <string>
#include "item.h"

enum class PotionType {
	RH, BA, BD, PH, WA, WD
};

class Potion: public Item {
	PotionType potionType;
	static std::vector<PotionType> seen;
	public:
		Potion(PotionType potionType);
		~Potion();
		PotionType getPotionType() const;
		std::string getEffect() const;
		static void see(PotionType potionType);
};

#endif
