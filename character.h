#ifndef CHARACTER_H
#define CHARACTER_H
#include "object.h";

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
		void strike(Character &other) virtual;
		void beStruckBy(Character &other) virtual;
}

#endif
