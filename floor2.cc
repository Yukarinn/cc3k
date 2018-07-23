#include "floor2.h"
#include "cell.h"
#include "player.h"
#include "potion.h"
#include "treasure.h"
#include "enemy.h"

#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"

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
				case '\\':
					cell = new Cell(Terrain::Stairs, i, j);
					break;
				default:
					custom = true;
					cell = new Cell(Terrain::Chamber, i, j);
					Object* obj = nullptr;
					switch (plan[i][j]) {
						case '0':
							obj = new Potion(PotionType::RH);
							break;
						case '1':
							obj = new Potion(PotionType::BA);
							break;
						case '2':
							obj = new Potion(PotionType::BD);
							break;
						case '3':
							obj = new Potion(PotionType::PH);
							break;
						case '4':
							obj = new Potion(PotionType::WA);
							break;
						case '5':
							obj = new Potion(PotionType::WD);
							break;	
						case '6':
							obj = new Treasure(TreasureType::NO);
							break;
						case '7':
							obj = new Treasure(TreasureType::SM);
							break;
						case '8':
							obj = new Treasure(TreasureType::ME);
							break;
						case '9':
							obj = new Treasure(TreasureType::HD);
							break;
						case '@':
							customPlayerCell = cell;
							break;
						case 'H':
							obj = new Human();
							break;
						case 'W':
							obj = new Dwarf();
							break;
						case 'E':
							obj = new Elf();
							break;
						case 'O':
							obj = new Orc();
							break;
						case 'M':
							obj = new Merchant();
							break;
						case 'D':
							obj = new Dragon();
							break;
						case 'L':
							obj = new Halfling();
							break;
					}
					if (obj) {
						cell->setObject(obj);
						obj->setCell(cell);
					}
					break;
			}
			row.push_back(cell);
		}
		theFloor.push_back(row);
	}
	cout << "*** done reading in from layout ***" << endl;
}

Floor::~Floor() {
	for (auto row: theFloor) {
		for (auto cell: row) {
			if (cell->getObject() && (cell->getObject()->getType() == ObjectType::Enemy || cell->getObject()->getType() == ObjectType::Player)) 
				cell->clearObject();
			delete cell;
		}
	}
	for (auto each: mobs) {
		delete each;
	}
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
			else if (cell->getObject()) {
				ret += cell->getObject()->getDisplay();
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
			else if (cell->getTerrain() == Terrain::Stairs) {
				ret += "\\";
			}
		}
		ret += "\n";
	}
	return ret;
}

void Floor::setPlayer(Player* player) {
	this->player = player;
	if (custom) {
		customPlayerCell->setObject(player);
		player->setCell(customPlayerCell);	
	}
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
            //cout << layout[i][j];
        }
        //cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        vector<Cell*> row;
        chambers.push_back(row);
    }
    // vector chambers
    for (int i = 0; i < 25; i ++) {
        for (int j = 0; j < 79; j ++)  {
            if (layout[i][j] > 0) // chambers are 1-5, 0 is empty
            {
                chambers[layout[i][j]-1].push_back(theFloor[i][j]);
            }
        }
    }
    
    for (int i = 0; i < 25; i ++) {
        for (int j = 0; j < 79; j ++) {
            for (int di = -1; di <= 1; di ++) {
                for (int dj = -1; dj <= 1; dj ++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni < 0 || nj < 0 || ni >= 25 || nj >= 79)
                        continue;
                    if (theFloor[ni][nj]->getTerrain() == Terrain::WallV
                        || theFloor[ni][nj]->getTerrain() == Terrain::WallH)
                        continue;
                    if (theFloor[ni][nj]->getTerrain() == Terrain::Empty)
                        continue;
                    theFloor[i][j]->addNeighbour(theFloor[ni][nj]);
                }
            }
        }
    }
		if (custom) {
			for (int i = 0; i < 25; i ++) {
				for (int j = 0; j < 79; j++) {
					if (theFloor[i][j]->getObject() && theFloor[i][j]->getObject()->getDisplay() == 'D') {
						Dragon* dragon = dynamic_cast<Dragon*>(theFloor[i][j]->getObject());
						mobs.emplace_back(dragon);
						vector<Cell*> neighbours = theFloor[i][j]->getNeighbours();
						for (auto neighbour: neighbours) {
							if (neighbour->getObject() && neighbour->getObject()->getType() == ObjectType::Treasure) {
								Treasure* treasure = dynamic_cast<Treasure*>(neighbour->getObject());
								if (treasure->getTreasureType() == TreasureType::HD) {
									dragon->setHoard(treasure);
								}
							}
						}
					}
				}
			}
		}
	cout << "*** done setup ***" << endl;
}

void Floor::spawnPlayer(int chamberNum)
{
    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    Cell* cell = chambers[chamberNum][whichCell];
    cell->setObject(player);
		player->setCell(cell);
}

void Floor::spawnStairs(int chamberNum)
{
    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    chambers[chamberNum][whichCell]->setStairs();
}

void Floor::spawnPotions()
{
    for (int i=0; i<10; i++)
    {
        int whichChamber = rand() % 5;
        int whichCell = rand() % chambers[whichChamber].size();
        int whichPotion = rand() % 6;
        vector <PotionType> potionTypes = {PotionType::RH,
            PotionType::BA,
            PotionType::BD,
            PotionType::PH,
            PotionType::WA,
            PotionType::WD};
				Cell* cell = chambers[whichChamber][whichCell];
        if (cell->getObject() == nullptr) // nothings on the floor
        {
            Potion* potion = new Potion(potionTypes[whichPotion]);
            cell->setObject(potion);
            potion->setCell(cell);
        }
        else
        {
            i--; // occupied, do it again
        }
    }
}

void Floor::spawnGold()
{
    for (int i=0; i<10; i++)
    {
        int whichChamber = rand() % 5;
        int whichCell = rand() % chambers[whichChamber].size();
        int whichTreasure = rand() % 8;
        Treasure* treasure;
        Cell* cell = chambers[whichChamber][whichCell];
        if (cell->getObject() == nullptr)
        {
            if (whichTreasure % 2 == 0 || whichTreasure == 1) // 5/8 chance
                treasure = new Treasure(TreasureType::NO);
            else if (whichTreasure == 3) { // 1/8 chance
                treasure = new Treasure(TreasureType::HD);
								bool free = false;
								vector<Cell*> neighbours = cell->getNeighbours();
								for (auto neighbour: neighbours) {
									if (neighbour->getObject() == nullptr)
										free = true;
								}
								if (!free) {
									i--;
								} else {
									int whichCell = rand() % neighbours.size();
									while (neighbours[whichCell]->getObject() != nullptr)
										whichCell = rand() % neighbours.size();
									Dragon* dragon = new Dragon();
									mobs.emplace_back(dragon);
									dragon->setHoard(treasure);
									neighbours[whichCell]->setObject(dragon);
									dragon->setCell(neighbours[whichCell]);
								}
						}
            else // 1/4 chance
                treasure = new Treasure(TreasureType::SM);
            cell->setObject(treasure);
            treasure->setCell(cell);
        }
        else
        {
            i--; // occupied, try again
        }
    }
}


void Floor::spawnEnemies()
{
    for (int i=0; i<20; i++)
    {
        int whichChamber = rand() % 5;
        int whichCell = rand() % chambers[whichChamber].size();
        int whichEnemy = rand() % 18;
        Enemy* enemy;
        Cell* cell = chambers[whichChamber][whichCell];
        if (cell->getObject() == nullptr)
        {
            if (whichEnemy < 4) // 2/9 human
                enemy = new Human();
            else if (whichEnemy < 7) // 3/18 dwarf
                enemy = new Dwarf();
            else if (whichEnemy < 12) // 5/18 halfling
                enemy = new Halfling();
            else if (whichEnemy < 14) // 1/9 elf
                enemy = new Elf();
            else if (whichEnemy < 16) // 1/9 orc
                enemy = new Orc();
            else
                enemy = new Merchant();
            cell->setObject(enemy);
            enemy->setCell(cell);
            mobs.emplace_back(enemy);
        }
        else
        {
            i--; // occupied, try again
        }
    }
}

void Floor::spawn()
{
		if (custom)
			return;
    // choose chamber for player
    int chamberNumPlayer = rand() % 5;
    spawnPlayer(chamberNumPlayer);
    
    // choose chamber for stairs
    int chamberNumStairs = chamberNumPlayer;
    while (chamberNumStairs == chamberNumPlayer)
    {
        chamberNumStairs = rand() % 5;
    }
    spawnStairs(chamberNumStairs); 
    spawnPotions();
    spawnGold();
    spawnEnemies();
    
    cout << "*** done spawning ***" << endl;
}

string Floor::mobAct()
{
		string ret = "";
    for (int i=0; i < mobs.size(); i++)
		{	
				if (mobs[i]->getCell()) {
					if (mobs[i]->getName() == "Dragon") {
						ret += dynamic_cast<Dragon*>(mobs[i])->act();
					} else {
						ret += mobs[i]->act();
					}
				}
    }
		return ret;
}
