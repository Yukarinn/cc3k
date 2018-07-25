#include "orc.h"
#include "goblin.h"
#include <cmath>
using namespace std;

Orc::Orc(): Enemy("Orc", 'O',  180, 30, 25) {}

Orc::~Orc() {}

pair<bool, string> Orc::strike(Goblin& other) {
    string ret = "";
    int dmg = ceil(1.5 * (100.0/(100.0+other.getDef()))*this->atk);
    other.setHp(other.getHp() - dmg);
    ret += name + " deals " + to_string(dmg) + " damage to PC.";
    return make_pair(true, ret);
}

