#include "merchant.h"

using namespace std;

Merchant::Merchant() Enemy("Merchant", 30, 70, 5) {}

Merchant::~Merchant() {

}

Merchant::beStruckBy(Character &other) {

}
void Merchant::defeat() {

}

// initialize static bool
bool Merchant::aggro = false;

static void setAggro()
{
    aggro = true;
}
