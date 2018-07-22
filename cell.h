#ifndef CELL_H
#define CELL_H

Class Object;

enum Terrain {
	Stairs, Wall, Door, Empty, Passage, Chamber
};

class Cell {
    Terrain terrain;
    Object * obj = nullptr;
    int r, c;
    int chamberNumber; // 0-4 for chamber, 5 for non-chamber
    // will never use this if non chamber
		vecotr<Cell*> neighbours;
public:
    Cell(Terrain terrain, int r, int c, int chamberNumber = 5);
    ~Cell();
    Terrain getTerrain() const;
    pair<int, int> getPos() const;
    bool canMoveTo() const;
    void setObject(Object* obj);
    Object* getObject() const;
    int getChamberNumber() const;
		void addNeighbour(Cell* cell);
}

#endif
