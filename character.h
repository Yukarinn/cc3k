#ifndef CHARACTER_H
#define CHARACTER_H
#include "object.h";

class Vampire;
class Elf;

class Character: public Object {
	std::string name;
	int hp;
	int atk;
	int def;
	public: 
		Character(std::string name, int hp, int atk, int def, ObjectType objectType);
		~Character();	
		std::string getName() const;
		void setHp(int hp);
		void setAtk(int atk);
		void setDef(int def);
		int getHp() const;
		int getAtk() const;
		int getDef() const;
		bool strike(Character& other) virtual;
		bool strike(Goblin& goblin) virtual;
		bool strike(Halfling& other);
		void beStruckBy(Character& other) virtual;
		void beStruckBy(Vampire& other) virtual;
		void beStruckBy(Elf& other) virtual;
}

#endif
