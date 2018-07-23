#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "game2.h"

using namespace std; 

int main() {
	srand(time(NULL));
	cout << rand() % 100 << endl;
	string buf;
	Game* game = new Game();
	cout << "Please select your race:" <<endl;
	for (int i = 0; i < game->getRaces().size(); i ++) {
		cout << i + 1 << ": " << game->getRaces()[i] << endl;
	}
	int selection;
	cin >> selection;
	game->newPlayer(selection);
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
					game = new Game();
					cout << "Please select your race:" <<endl;
					for (int i = 0; i < game->getRaces().size(); i ++) {
						cout << i + 1 << ": " << game->getRaces()[i] << endl;
					}
					cin >> selection;
					game->newPlayer(selection);
					game->startLevel();	
					game->draw();
					continue;	
				}
				else if (buf == "q") {
					
				} else {
					throw InvalidAction();
				}
				game->mobAct();
				game->draw();
				game->displayMenu();
			} catch (exception& e) {
				cout << e.what() << endl;
				game->draw();
				game->displayMenu();
			}
		}
	} catch (exception& e) {
		cout << e.what() << endl;
	}
}
