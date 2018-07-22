#include "cell.h"
#include "object.h"

using namespace std;

Cell::Cell(Terrain terrain, int r, int c, int chamberNumber):
	terrain{terrain}, r{r}, c{c}, chamberNumber{chamberNumber} {}

Cell::~Cell() {
	delete this->obj;
}

pair<int, int> Cell::getPos() const {
	return make_pair(r, c);
}

Terrain Cell::getTerrain() const {
	return terrain;
}

bool Cell::canMoveTo() const {
	return (terrain == Terrain::Stairs || terrain == Terrain::Door || terrain == Terrain::Chamber || terrain == Terrain::Passage) && (obj->getType() != ObjectType::Potion) && (obj->getType() != ObjectType::Enemy);
}

void Cell::setObject(Object* obj) {
	this->obj = obj;
}

void Cell::clearObject() {
	delete this->obj;
	this->obj = nullptr;
}

Object* Cell::getObject() const {
	return obj;
}

int Cell::getChamberNumber() const {
	return chamberNumber;
}

void Cell::addNeighbour(Cell* cell) {
	neighbours.emplace_back(cell);
}

void Cell::setStairs() {
	this->terrain = Terrain::Stairs;
}
