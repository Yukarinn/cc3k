#ifndef ITEM_H
#define ITEM_H
#include "object.h"

class Item: public Object {
	public:
		Item(ObjectType type);
		~Item();
};

#endif
