#include <cstdlib>
#include "floor.h"
#include "cell.h"
#include "player.h"
#include "potion.h"

void Floor::spawnPlayer(Object * thePlayer, int chamberNum)
{

    int whichCell = rand() % chambers[chamberNum].size(); // choose cell
    
    // need to change this since
    // 1. object: player doesnt have a type, need to modyfy player.h
    // (i.e player should inherit objectType from object.h)
    // 2. if its the next floor then we should use the original player
    
    // reset atk and def
    thePlayer->setAtk(thePlayer->getBaseAtk());
    thePlayer->setDef(thePlayer->getBaseDef());
    chambers[chamberNum][whichCell]->obj = thePlayer; // put player in cell
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
            chambers[whichChamber][whichCell]->obj = new Potion(potionTypes[whichPotion]);
        }
        else
        {
            i--; // occupied, do it again
        }
    }
}

void Floor::spawnGold();
void Floor::spawnEnemies();

Floor::Floor(Cell * cleanFloor[30][79], Object * thePlayer) {
    isFrozen = false;
    // copy the floor
    for (int i=0; i<30; i++)
    {
        for (int j=0; j<79; j++)
        {
            theFloor[i][j] = new Cell();
            theFloor[i][j]->terrian = cleanFloor[i][j]->terrrian;
            theFloor[i][j]->r = cleanFloor[i][j]->r;
            theFloor[i][j]->c = cleanFloor[i][j]->c;
            if (theFloor[i][j]->terrian == Terrian::Chamber)
            {
                theFloor[i][j]->whichChamber = cleanFloor[i][j]->whichChamber;
                chambers[theFloor[i][j]->whichChamber].emplace_back(theFloor[i][j]);
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

