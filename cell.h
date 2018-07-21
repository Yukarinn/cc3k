#ifndef CELL_H
#define CELL_H

Class Object;

enum Terrain {
	Wall, Door, Floor, Passage, Chamber
};

class Cell {
	Terrain terrain;
	Object * obj = nullptr;
    int r, c;
    int whichChamber = 5; // 0-4 for chamber, 5 for non-chamber
                            // will never use this if non chamber
	public:
		Cell(Terrain terrain, Object * obj, int r, int c, int whichChamber);
		~Cell();	
		Terrain getTerrain() const;
		pair<int, int> getPos() const;
		bool canMoveTo() const;
}

#endif
