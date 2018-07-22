#ifndef CELL_H
#define CELL_H
#include <cstdlib>
#include <vector>

class Object;

enum Terrain {
	Stairs, WallV, WallH, Door, Empty, Passage, Chamber
};

class Cell {
    Terrain terrain;
    Object * obj = nullptr;
    int r, c;
    int chamberNumber; // 0-4 for chamber, 5 for non-chamber
    // will never use this if non chamber
		std::vector<Cell*> neighbours;
public:
    Cell(Terrain terrain, int r, int c, int chamberNumber = 5);
    ~Cell();
    Terrain getTerrain() const;
    std::pair<int, int> getPos() const;
    bool canMoveTo() const;
    bool enemyCanMoveTo() const;
		void setObject(Object* obj);
		void clearObject();
    Object* getObject() const;
    int getChamberNumber() const;
		void addNeighbour(Cell* cell);
		std::vector<Cell*> getNeighbours() const;
		void setStairs();
};

#endif
