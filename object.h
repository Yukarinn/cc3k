#ifndef OBJECT_H
#define OBJECT_H

class Cell;

enum class ObjectType {
	Potion, Enemy, Player, Treasure, Empty
};

class Object {
	protected:
		ObjectType type;
		Cell* cell;
	public:
		Object(ObjectType type);
		~Object();		
		ObjectType getType();
		Cell* getCell() const;
		void setCell(Cell * cell);
};
#endif
