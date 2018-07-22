#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <string>

class Cell;
class Player;

class Floor {
    std::vector<std::vector<Cell*>> theFloor;
    Player * player;
    std::vector<std::vector<int>> layout;
public:
    Floor(std::vector<std::vector<char>> plan);
    ~Floor();
    std::string draw();
    void setPlayer(Player* player);
    Player* getPlayer();
    void setup();
private:
    void floodfill(int i, int j, int chamber);
};

#endif
