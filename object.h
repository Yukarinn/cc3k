#ifndef OBJECT_H
#define OBJECT_H

class Cell;

enum class ObjectType {
	Potion, Enemy, Player, Treasure, Empty
};

class Object {
		char display; // character to display on map
	protected:
		ObjectType type;
		Cell* cell; // cell this object is on
	public:
		Object(ObjectType type, char display);
		virtual ~Object();		
		ObjectType getType();
		Cell* getCell() const;
		void setCell(Cell * cell);
		char getDisplay() const;
};
#endif
