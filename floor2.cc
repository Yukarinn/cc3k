#include "floor2.h"
#include "cell.h"
#include "player.h"

#include <vector>
#include <iostream>

using namespace std;

Floor::Floor(vector<vector<char>> plan) {
	for (int i = 0; i < 25; i ++) {
		vector<Cell*> row;
		for (int j = 0; j < 79; j ++) {
			Cell* cell;
			switch(plan[i][j]) {
				case '|':
					cell = new Cell(Terrain::WallV, i, j);
					break;
				case '-':
					cell = new Cell(Terrain::WallH, i, j);
					break;
				case ' ':
					cell = new Cell(Terrain::Empty, i, j);
					break;
				case '#':
					cell = new Cell(Terrain::Passage, i, j);
					break;
				case '+':
					cell = new Cell(Terrain::Door, i, j);
					break;
				case '.':
					cell = new Cell(Terrain::Chamber, i, j);
					break;
				default:
					cell = new Cell(Terrain::Chamber, i, j);
					break;
			}
			row.push_back(cell);
		}
		theFloor.push_back(row);
	}
}

Floor::~Floor() {
	for (auto row: theFloor) {
		for (auto cell: row) {
			delete cell;
		}
	}
	delete player;
}

string Floor::draw() {
	string ret = "";
	for (int i = 0; i < 25; i ++) {
		for (int j = 0; j < 79; j ++) {
			Cell* cell = theFloor[i][j];
			if (cell->getTerrain() == Terrain::WallV) {
				ret += "|";
			}
			else if (cell->getTerrain() == Terrain::WallH) {
				ret += "-";
			}
			else if (cell->getTerrain() == Terrain::Empty) {
				ret += " ";
			}
			else if (cell->getObject() && cell->getObject()->getType() == ObjectType::Player) {
				ret += "@";
			}
			else if (cell->getTerrain() == Terrain::Chamber) {
				ret += ".";
			}
			else if (cell->getTerrain() == Terrain::Passage) {
				ret += "#";
			}
			else if (cell->getTerrain() == Terrain::Door) {
				ret += "+";
			}
		}
		ret += "\n";
	}
	return ret;
}

void Floor::setPlayer(Player* player) {
	this->player = player;
}

Player* Floor::getPlayer() {
	return player;
}
	

void Floor::floodfill(int i, int j, int chamber) {
	if (i < 0 || j < 0 || i >= 25 || j >= 79)
		return;
	if (theFloor[i][j]->getTerrain() != Terrain::Chamber)
		return;
	if (layout[i][j] != 0) 
		return;
	layout[i][j] = chamber;
	floodfill(i + 1, j, chamber);
	floodfill(i - 1, j, chamber);
	floodfill(i, j - 1, chamber);
	floodfill(i, j + 1, chamber);
}

void Floor::setup() {
	int chamber = 1;
	
	for (int i = 0; i < 25; i ++) {
		vector<int> row(79);
		for (int j = 0; j < 79; j ++)
				row[j] = 0;
		layout.push_back(row);
	}
	for (int i = 0; i < 25; i ++) {
		for (int j = 0; j < 79; j ++) {
			if (layout[i][j] != 0)
				 continue;
			if (theFloor[i][j]->getTerrain() != Terrain::Chamber) 
				layout[i][j] = -1;
			if (theFloor[i][j]->getTerrain() == Terrain::Chamber) {
				floodfill(i, j, chamber ++);
			}
		}
	}
	for (int i = 0; i < 25; i ++) {
		for (int j = 0; j < 79; j ++)  {
			if (layout[i][j] == -1)
				 layout[i][j] = 0;
			cout << layout[i][j];
		}
		cout << endl;
	}
}

