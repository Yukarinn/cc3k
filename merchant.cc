#include "merchant.h"

using namespace std;

bool Merchant::aggro = false;

Merchant::Merchant(): Enemy("Merchant", 30, 70, 5) {}

Merchant::~Merchant() {

}

void Merchant::drop() {

}

void Merchant::beStruckBy(Character& other) {

}

void Merchant::setAggro(bool aggro)
{
    Merchant::aggro = aggro;
}
