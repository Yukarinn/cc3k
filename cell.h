#ifndef CELL_H
#define CELL_H

enum Terrain {
	Wall, Door, Floor, Passage;
};

class Cell {
	Terrain terrain;
	int r, c;
	public:
		Cell(Terrain terrain);
		~Cell();	
		Terrain getTerrain();
		pair<int, int> getPos();
		bool canMoveTo();
}

#endif
