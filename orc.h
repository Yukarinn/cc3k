#ifndef ORC_H
#define ORC_H
#include "enemy.h"
#include <utility>
#include <string>

class Goblin;
class Orc: public Enemy {
public: 
    Orc();
    ~Orc();
    std::pair<bool, std::string> strike(Goblin& other);
};
#endif
