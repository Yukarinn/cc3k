#include "treasure.h"
#include "player.h"

using namespace std;

Treasure::Treasure(TreasureType treasureType): Item(ObjectType::Treasure, 'G'), treasureType{treasureType} {}

Treasure::~Treasure() {}

TreasureType Treasure::getTreasureType() const {
    return treasureType;
}

void Treasure::setTreasureType(TreasureType treasureType) {
    this->treasureType = treasureType;
}

string Treasure::getName() {
    switch(treasureType) {
        case TreasureType::NO:  // normal
            return "2 gold";
        case TreasureType::SM:  // small
            return "1 gold";
        case TreasureType::HN:  // dragon hoard
            return "6 gold";
        case TreasureType::ME:  // merchant
            return "4 gold";
    }
    return "";
}
