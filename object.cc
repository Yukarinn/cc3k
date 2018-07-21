#include "object.h"
#include "cell.h"

using namespace std;

Object::Object(ObjectType type): type{type} {}

Object::~Object() {}

ObjectType Object::getType() {
	return type;
}

Cell* getCell() {
	return cell;
}

void setCell(Cell* cell) {
	this->cell = cell;
}
