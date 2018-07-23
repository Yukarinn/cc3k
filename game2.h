#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>

class Floor;
class Player;

class Game {
    std::vector<Floor*> floors;
    Player * player;
    int level;
		std::vector<std::string> directions = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
		std::vector<std::string> races = {"shade", "drow", "vampire", "troll", "goblin"};
	public:
    Game(std::string file = "default.txt");
		~Game();
		void newPlayer(int player);
		std::vector<std::string> getDirections() const;
		std::vector<std::string> getRaces() const;
		void startLevel();
		void draw();
		void playerMove(std::string direction);
};

#endif
