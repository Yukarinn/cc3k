#ifndef DROW_H
#define DROW_H
#include "player.h"

class Elf;
class Drow: public Player {
	public: 
		Drow();
		~Drow();
		void beStruckBy(Elf& other) override;
};
#endif
