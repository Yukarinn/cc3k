#include "potion.h"
#include "player.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<PotionType> Potion::seen = {};
Potion::Potion(PotionType potionType): Item(ObjectType::Potion, 'P'), potionType{potionType} {}

Potion::~Potion() {}

PotionType Potion::getPotionType() const {
    return potionType;
}

string Potion::getEffect() const {
    // check if the player has seen this potion before
    // if not, tell the player it's unknown potion
    if (find(Potion::seen.begin(), Potion::seen.end(), potionType) == Potion::seen.end())
        return "Unknown Potion";
    // otherwise, return the type of the potion
    switch(potionType) {
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

void Potion::see(PotionType potionType) {
    // add the new potion that player used too the seen list
    Potion::seen.emplace_back(potionType);
}
