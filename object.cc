#include "object.h"
#include "cell.h"

using namespace std;

Object::Object(ObjectType type): type{type} {}

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
