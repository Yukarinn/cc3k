#include "dwarf.h"
#include "vampire.h"


using namespace std;

Dwarf::Dwarf(): Enemy("Dwarf", 'W', 100, 20, 30) {}

Dwarf::~Dwarf() {}

void Dwarf::beStruckBy(Vampire& other) {
	other.strike(*this);
	other.setHp(other.getHp() - 5);	
}
