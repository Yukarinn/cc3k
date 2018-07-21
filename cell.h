#ifndef CELL_H
#define CELL_H

enum Terrain {
	Wall, Door, Floor, Passage, Chamber;
};

class Cell {
    Object * obj = nullptr;
	Terrain terrain;
    int r, c;
    int whichChamber = 5; // 0-4 for chamber, 5 for non-chamber
                            // will never use this if non chamber
	public:
		Cell(Terrain terrain);
		~Cell();	
		Terrain getTerrain();
		pair<int, int> getPos();
		bool canMoveTo();
}

#endif
