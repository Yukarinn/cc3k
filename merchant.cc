#include "merchant.h"
#include "cell.h"
#include "player.h"
#include "treasure.h"
using namespace std;

bool Merchant::aggro = false;

Merchant::Merchant(): Enemy("Merchant", 'M', 30, 70, 5) {}

Merchant::~Merchant() {
}

string Merchant::act() {
	if (Merchant::aggro && findPlayer() != nullptr) {
		Player* player = dynamic_cast<Player*>(findPlayer()->getObject());
		return strike(player);
	}
	Cell* cell = this->getCell();
	vector<Cell*> neighbours = cell->getNeighbours();
	int r = rand() % neighbours.size();
	while (!neighbours[r]->enemyCanMoveTo()) {
		r = rand() % neighbours.size();
	}
	neighbours[r]->setObject(this);
	cell->clearObject();
	this->setCell(neighbours[r]);
	return "";
}

void Merchant::drop() {
	Cell* cell = this->cell;
	cell->clearObject();
	Treasure* treasure = new Treasure(TreasureType::ME);
	cell->setObject(treasure);
	treasure->setCell(cell);
}

void Merchant::setAggro(bool aggro)
{
    Merchant::aggro = aggro;
}
