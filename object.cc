#include "object.h"
#include "cell.h"

using namespace std;

Object::Object(ObjectType type, char display): type{type}, display{display} {}

Object::~Object() {}

ObjectType Object::getType() {
	return type;
}

Cell* Object::getCell() const {
	return cell;
}

void Object::setCell(Cell* cell) {
	this->cell = cell;
}

char Object::getDisplay() const {
	return display;
}
