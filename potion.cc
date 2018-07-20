#include "potion.h";
#include "player.h";
#include <vector>

using namespace std;

Potion::Potion(PotionType potionType): Item(ObjectType::Potion), potionType{potionType} {}

Potion::~Potion() {}

PotionType Potion::getPotionType() const {
	return potionType;
}

string Potion::getEffect() const {
	switch(PotionType) {
		case PotionType::RH:
			return "Plus HP";
		case PotionType::BA:
			return "Buff ATK";
		case PotionType::BD:
			return "Buff DEF";
		case PotionType::PH:
			return "Minus HP";
		case PotionType::WA:
			return "Debuff ATK";
		case PotionType::WD:
			return "Debuff DEF";
	}
}

