#include <vector>
#include <iostream>
#include <algorithm>

#include "game2.h"

using namespace std; 

int main() {
	string buf;
	Game game = Game();
	cout << "Please select your race:" <<endl;
	for (int i = 0; i < game.getRaces().size(); i ++) {
		cout << i + 1 << ": " << game.getRaces()[i] << endl;
	}
	int selection;
	cin >> selection;
	game.newPlayer(selection);
	game.startLevel();	
	while (cin >> buf) {
	
	}
}
