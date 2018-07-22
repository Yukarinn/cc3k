#include "orc.h"
#include "goblin.h"

using namespace std;

Orc::Orc(): Enemy("Orc", 180, 30, 25) {}

Orc::~Orc() {}

bool Orc::strike(Goblin &other) {
	int dmg = ceil(1.5 * (100/(100+other.getDef()))*this->atk);
	other.setHp(other.getHp() - dmg);
	return true;
}
