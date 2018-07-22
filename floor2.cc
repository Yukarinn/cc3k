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
	int chamber = 0;
	
	for (int i = 0; i < 25; i ++) {
		vector<int> row(79);
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
			if (layout[i][j] == -1) layout[i][j] = 5;
			//cout << layout[i][j];
		}
		//cout << endl;
	}
    for (int i = 0; i< 25; i++)
    {
        for (int j = 0; j<79; j++)
        {
            if (layout[i][j] != 5) // is a chamber
            {
                chambers[layout[i][j]].push_back(theFloor[i][j]);
            }
        }
    }
}

void Floor::spawnPlayer(Object * thePlayer, int chamberNum)
{
    
    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    // if its the next floor then we should use the original player
    
    // reset atk and def
    thePlayer->setAtk(thePlayer->getBaseAtk());
    thePlayer->setDef(thePlayer->getBaseDef());
    chambers[chamberNum][whichCell]->setObject(thePlayer); // put player in cell
    thePlayer.setCell(chambers[chamberNum][whichCell]);
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
            PotionType::WD}
        if (! chambers[whichChamber][whichCell]->getObject) // nothings on the floor
        {
            Potion* potion = new Potion(potionTypes[whichPotion]);
            chambers[whichChamber][whichCell]->setObject(potion);
            potion.setCell(chambers[whichChamber][whichCell]);
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
        if (!(chambers[whichChamber][whichCell]->getObject()))
        {
            if (whichTreasure % 2 == 0 || whichTreasure == 1) // 5/8 chance
                treasure = new Treasure(TreasureType::NO);
            else if (whichTreasure == 3) // 1/8 chance
                treasure = new Treasure(TreasureType::HD);
            else // 1/4 chance
                treasure = new Treasure(TreasureType::SM);
            chambers[whichChamber][whichCell]->setObject(treasure);
            treasure.setCell(chambers[whichChamber][whichCell]);
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
        if (!(chambers[whichChamber][whichCell]->getObject()))
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
            chambers[whichChamber][whichCell]->setObject(enemy);
            enemy.setCell(chambers[whichChamber][whichCell]);
            mobs.emplace_back(enemy);
        }
        else
        {
            i--; // occupied, try again
        }
    }
}

void Floor::mobAct()
{
    for (int i=0; i<mobs.size(); i++)
    {
        mobs[i]->act();
    }
}


