#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "game.h"
#include "player.h"

using namespace std; 

int main(int argc, char *argv[]) {
	bool custom = false;
	string file;
	if (argc > 1) {
		if (argc > 2) {
			cerr << "Usage: "<< argv[0] << " FILE.TXT" << endl;
			return 1;
		}
		custom = true;	
		file = argv[1];
	}
	cin.exceptions(ios::eofbit|ios::failbit);
	srand(time(NULL));
	cout << rand() % 100 << endl;
	string buf;
	Game * game;
	if (!custom)
		game = new Game();
	else
		game = new Game(file);
	
	game->selectPlayer();
	game->startLevel();	
	vector<string> directions = game->getDirections();
	game->draw();
	try {
		while (true) {
			try {
				cin >> buf;
				if (find(directions.begin(), directions.end(), buf) != directions.end()) {
					game->playerMove(buf);
				}	
				else if (buf == "u") {
					string dir;
					cin >> dir;
					game->usePotion(dir);
				} 
				else if (buf == "a") {
					string dir;
					cin >> dir;
					game->playerAttack(dir);
				}
				else if (buf == "f") {
					game->toggleFreeze();
				}
				else if (buf == "r") {
					delete game;
					if (!custom)
						game = new Game();
					else
						game = new Game(file);
					game->selectPlayer();
					game->startLevel();	
					game->draw();
					continue;	
				}
				else if (buf == "q") {
					delete game;
					break;
				} else {
					continue;
				}
				
				if (game->isGameOver()) {
					game->draw();
					cout << "THE GAME IS DONE! YOUR SCORE WAS: " + to_string(game->getPlayer()->getGold()) << endl;
					cout << "RESTART(R) or QUIT(Q)?" << endl;
					continue;
				}
				game->mobAct();
				game->endTurn();
				if (game->isGameOver()) {
					game->draw();
					int score = game->getPlayer()->getGold();
					if (game->getPlayer()->getName() == "Shade") {
						if (rand() % 2)
							score = ceil(score * 1.5);
					}
					cout << "THE GAME IS DONE! YOUR SCORE WAS: " + to_string(score) << endl;
					cout << "RESTART(R) or QUIT(Q)?" << endl;
					continue;
				}
				game->draw();
				game->displayMenu();
			} catch (exception& e) {
				if (cin.eof()) {
					delete game;
					break;
				}
				cout << e.what() << endl;
				game->draw();
				game->displayMenu();
			}
		}
	} catch (exception& e) {}
}
