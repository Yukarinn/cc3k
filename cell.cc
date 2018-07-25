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

// a player can move to this cell if it is stairs, a chamber tile, or a passage tile that is empty or has gold on it
bool Cell::canMoveTo() const {
    if (terrain != Terrain::Stairs && terrain != Terrain::Door && terrain != Terrain::Chamber && terrain != Terrain::Passage)
        return false;
    if (!obj) 
        return true;
    if (obj->getType() == ObjectType::Potion)
        return false;
    if (obj->getType() == ObjectType::Enemy)
        return false;
    return true;
}


// enemies can only move to cells in their chamber, or block the door as long as these are non-empty
bool Cell::enemyCanMoveTo() const {
    if (terrain != Terrain::Door && terrain != Terrain::Chamber)
        return false;
    if (!obj)
        return true;
    return false;
}
void Cell::setObject(Object* obj) {
    this->obj = obj;
}

void Cell::clearObject() {
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

vector<Cell*> Cell::getNeighbours() const {
    return neighbours;
}
void Cell::setStairs() {
    this->terrain = Terrain::Stairs;
}
