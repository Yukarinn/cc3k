#ifndef CHARACTER_H
#define CHARACTER_H
#include "object.h"
#include <string>

class Vampire;
class Elf;
class Goblin;
class Halfling;

class Character: public Object {
	protected:
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
		virtual bool strike(Character& other);
		virtual bool strike(Goblin& goblin);
		bool strike(Halfling& other);
		virtual void beStruckBy(Character& other);
		virtual void beStruckBy(Vampire& other);
		virtual void beStruckBy(Elf& other);
};

#endif
