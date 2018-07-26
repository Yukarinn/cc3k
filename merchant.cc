#include "merchant.h"
#include "cell.h"
#include "player.h"
#include "treasure.h"
using namespace std;

bool Merchant::aggro = false; //static flag for merchant aggro behaviour

Merchant::Merchant(): Enemy("Merchant", 'M', 30, 70, 5) {}

Merchant::~Merchant() {
}

// merchants move randomly all the time
// unles they have been attacked by the player before
// in which case they will attack if the player is nearby
string Merchant::act() {
    if (Merchant::aggro && findPlayer() != nullptr) {
        Player* player = dynamic_cast<Player*>(findPlayer()->getObject());
        return strike(player);
    }
    move();
    return "";
}

// drops a special merchant hoard
void Merchant::drop() {
    Cell* cell = this->cell;
    cell->clearObject();
    Treasure* treasure = new Treasure(TreasureType::ME);
    cell->setObject(treasure);
    treasure->setCell(cell);
    this->cell = nullptr;
}

void Merchant::setAggro(bool aggro)
{
    Merchant::aggro = aggro;
}
