#ifndef OBJECT_H
#define OBJECT_H

enum ObjectType {
	Potion, Enemy, Player, Treasure, Empty
};

class Object {
	ObjectType type;
	public:
		Object(ObjectType type);
		~Object();		
		ObjectType getType();
}

#endif
