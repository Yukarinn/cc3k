#ifndef ELF_H
#define ELF_H
#include "enemy.h"
class Elf: public Enemy {
	public: 
		Elf();
		~Elf();
		void strike(Character& other) override;
}
#endif
