#include "dragon.h"

using namespace std;

Dragon::Dragon() Enemy("Dragon", 150, 20, 20) {}

Dragon::~Dragon() {}

void Dragon::defeat() {

}

Treasure* Dragon::getHoard() const {
	return hoard;
}

void Dragon::setHoard(Treasure* hoard) {
	this->hoard = hoard;
}
