#include <cstdlib>
#include "floor.h"
#include "cell.h"
#include "player.h"
#include "potion.h"
#include "treasure.h"

void Floor::spawnPlayer(Object * thePlayer, int chamberNum)
{

    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    // 2. if its the next floor then we should use the original player
    
    // reset atk and def
    thePlayer->setAtk(thePlayer->getBaseAtk());
    thePlayer->setDef(thePlayer->getBaseDef());
    chambers[chamberNum][whichCell]->setObject(thePlayer); // put player in cell
}

void Floor::spawnStairs(int chamberNum)
{
    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    // WHAT IS STAIRS???
    //chambers[chamberNum][whichCell]->
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
        if (! chambers[whichChamber][whichCell]->obj) // nothings on the floor
        {
            chambers[whichChamber][whichCell]->setObject(new Potion(potionTypes[whichPotion]));
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

        if (!(chambers[whichChamber][whichCell]->obj))
        {
            if (whichTreasure % 2 == 0 || whichTreasure == 1) // 5/8 chance
            {
                chambers[whichChamber][whichCell]->setObject(new Treasure(TreasureType::NO));
            }
            else if (whichTreasure == 3) // 1/8 chance
            {
                chambers[whichChamber][whichCell]->setObject(new Treasure(TreasureType::DR));
            }
            else // 1/4 chance
            {
                chambers[whichChamber][whichCell]->setObject(new Treasure(TreasureType::SM));
            }
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
        
        if (!(chambers[whichChamber][whichCell]->obj))
        {
            if (whichEnemy < 4) // 2/9 human
            {
                chambers[whichChamber][whichCell]->setObject(new Human());
            }
            else if (whichEnemy < 7) // 3/18 dwarf
            {
                chambers[whichChamber][whichCell]->setObject(new Dwarf());
            }
            else if (whichEnemy < 12) // 5/18 halfling
            {
                chambers[whichChamber][whichCell]->setObject(new Halfling());
            }
            else if (whichEnemy < 14) // 1/9 elf
            {
                chambers[whichChamber][whichCell]->setObject(new Elf());
            }
            else if (whichEnemy < 16) // 1/9 orc
            {
                chambers[whichChamber][whichCell]->setObject(new Orc());
            }
            else // 1/9 merchant
            {
                chambers[whichChamber][whichCell]->setObject(new Merchant());
            }
            mobs.emplace_back(chambers[whichChamber][whichCell]);
        }
        else
        {
            i--; // occupied, try again
        }
}

Floor::Floor(Cell * cleanFloor[30][79], Object * thePlayer) {
    isFrozen = false;
    // copy the floor
    for (int i=0; i<30; i++)
    {
        for (int j=0; j<79; j++)
        {
            theFloor[i][j] = new Cell(cleanFloor[i][j]->getTerrrian(),
                                      cleanFloor[i][j]->getr(),
                                      cleanFloor[i][j]->getc());

            if (cleanFloor[i][j]->getTerrian == Terrian::Chamber)
            {
                theFloor[i][j]->chamberNumber = cleanFloor[i][j]->getChamberNumber;
                chambers[theFloor[i][j]->getChamberNumber].emplace_back(theFloor[i][j]);
                // put cell pointers in chambers
            }
        }
    }
    
    // choose chamber for player
    int chamberNumPlayer = rand() % 5;
    spawnPlayer(thePlayer, chamberNumPlayer);
    
    // choose chamber for stairs
    int chamberNumStairs = chamberNumPlayer;
    while (chamberNumStairs == chamberNumPlayer)
    {
        chamberNumStaris = rand() % 5;
    }
    spawnStairs(chamberNumStairs);
    
    spawnPotions();
    spawnGold();
    spawnEnemies(); // append to mob vector
}

// display
void Floor::draw()
{
    
}

void Floor::mobAct()
{
    for (int i=0; i<mobs.size(); i++)
    {
        mobs[i]->act();
    }
}

