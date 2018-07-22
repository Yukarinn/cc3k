#include "cell.h"
#include "object.h"

using namespace std;

Cell::Cell(Terrain terrain, int r, int c, int whichChamber):
	terrain{terrain}, r{r}, c{c}, whichChamber{whichChamber} {}

Cell::~Cell() {
	delete this->obj;
}

Cell::getPos() const {
	return make_pair(r, c);
}

Cell::getTerrain() const {
	return terrain;
}

bool canMoveTo() const {
	return (terrain == Terrain::Stairs || terrain == Terrain::Door || terrain == Terrain::Chamber || terrain == Terrain::Passage) && (obj->objectType != ObjectType::Potion) && (obj->objectType != ObjectType::Enemy);
}

void setObject(Object* obj) {
	this->obj = obj;
}

Object* getObject() const {
	return obj;
}

int getChamberNumber() const {
	return chamberNumber;
}

void addNeighbour(Cell* cell) {
	neighbours.emplace_back(cell);
}
