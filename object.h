#ifndef OBJECT_H
#define OBJECT_H

class Cell;

enum ObjectType {
	Potion, Enemy, Player, Treasure, Empty
};

class Object {
	ObjectType type;
	Cell *cell;
	public:
		Object(ObjectType type);
		~Object();		
		ObjectType getType();
		Cell* getCell() const;
		void setCell(Cell * cell);
}

#endif
