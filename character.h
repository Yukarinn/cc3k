#ifndef CHARACTER_H
#define CHARACTER_H
#include "object.h"
#include <string>
#include <utility>

class Character: public Object {
	protected:
		std::string name;
		int hp;
		int atk;
		int def;
	public: 
		Character(std::string name, char display, int hp, int atk, int def, ObjectType objectType);
		~Character();
		void setHp(int hp);
		void setAtk(int atk);
		void setDef(int def);
		int getHp() const;
		int getAtk() const;
		int getDef() const;
		std::string getName() const;
};

#endif
