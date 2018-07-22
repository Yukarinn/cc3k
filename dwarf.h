#ifndef DWARF_H
#define DWARF_H
#include "enemy.h"

class Vampire;

class Dwarf: public Enemy {
	public: 
		Dwarf();
		~Dwarf();
		void beStruckBy(Vampire &other);
};
#endif
