#include "item.h"
#include "cell.h"

using namespace std;

Item::Item(ObjectType type, char display): Object(type, display) {}
Item::~Item() {
	cell->clearObject();
}
