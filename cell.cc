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
	return terrain == Terrain::Door || terrain == Terrain::Floor || terrain == Terrain::Passage;
}
