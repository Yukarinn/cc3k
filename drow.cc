#include "drow.h"
#include "elf.h"
#include "potion.h"
#include <algorithm>

using namespace std;

Drow::Drow(): Player("Drow", 150, 25, 15, 150, 25, 15) {}

Drow::~Drow() {}

void Drow::drink(Potion* potion) {
	switch(potion->getPotionType()) {
		case PotionType::RH:
			setHp(min(getMaxHp(), getHp() + 15));
			break;
		case PotionType::BA:
			setAtk(getAtk() + 15);
			break;
		case PotionType::BD:
			setDef(getDef() + 15);
			break;
		case PotionType::PH:
			setHp(max(0, getHp() - 15));
			break;
		case PotionType::WA:
			setAtk(max(getAtk() - 15, 0));
			break;
		case PotionType::WD:
			setDef(max(getDef() - 15, 0));
			break;
	}
	delete potion;
}

