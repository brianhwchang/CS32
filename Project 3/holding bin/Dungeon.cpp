//
//  Dungeon.cpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Dungeon.h"
#include "Actor.h"
#include "globals.h"

#include <string>
#include <vector>
#include <vector>
#include <iostream>

using namespace std;

Dungeon::Dungeon()
{
    drawDungeon();                  //make the box.
    level = 0;                      //start at top level 0
    m_player = new Player(this);    //create player actor.
    spawnPlayer();                  //Randomly spawn in the map.
    genMonsters();
    spawnMonsters();
    genObjects();
    spawnObjects();
}

Dungeon::~Dungeon()
{
    if (m_player != nullptr)
    {
        delete m_player;
        m_player = nullptr;
    }
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++)   //Freeing memory allocated for monsters
    {
        delete (*mon);
    }
    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end(); obj++)      //Free memory allocated for objects
    {
        delete (*obj);
    }
    if (level == 4)
        delete goldenIdol;
    else
        delete m_stairs;
}

void Dungeon::nextLevel()
{
    level++;
    clearMonsters();    //remove all monsters
    clearObjects();     //remove all objects
    drawDungeon();      //draws a new dungeon
    genMonsters();      //creates a whole new vector of monsters.
    genObjects();       //creates a whole new vector of objects.
    spawnPlayer();      //spawns the player in the new dungeon.
    spawnMonsters();    //spwans the monsters.
    spawnObjects();     //spawns the objects.
    printDungeon();     //prints the dungeon onto the terminal.
}


void Dungeon::setChar(int row, int col, char ch)
{
    map[row][col] = ch;
}


// Creates new monster instances to be stored in the MonsterVector, number of monsters is based on the level of the dungeon.
void Dungeon::genMonsters()
{
    // M randomly placed monsters, where M = randInt(2, 5*(L+1)+1) (So, for example, level 3 will have between 2 and 21 monsters.)
    int n_mobs = randInt(2, 5*(level+1)+1 );
    
    if (level < 2) // Only goblins and snakewomen
    {
        for (int i = 0; i < n_mobs; i++)
        {
            int whosThatPokemon = randInt(1, 2);
            if (whosThatPokemon == 1)
                monsterVector.push_back(new Snakewoman(this));
            else if (whosThatPokemon == 2)
                monsterVector.push_back(new Goblin(this));
        }
    }
    
    else if (level == 2) //Goblins, Snakes, and Bogeybois
    {
        for (int i = 0; i < n_mobs; i++)
        {
            int whoDatBoi = randInt(1, 3);
            
            if (whoDatBoi == 1)
                monsterVector.push_back(new Snakewoman(this));
            else if (whoDatBoi == 2)
                monsterVector.push_back(new Goblin(this));
            else if (whoDatBoi == 3)
                monsterVector.push_back(new Bogeyman(this));
        }
    }
    
    else if (level > 2)     //Gibbons, Snekes, Bogeyboards, and Dragoons.
    {
        for (int i = 0; i < n_mobs; i++)
        {
            int whoHimIs = randInt(1, 4);
            
            if (whoHimIs == 1)
                monsterVector.push_back(new Snakewoman(this));
            else if (whoHimIs == 2)
                monsterVector.push_back(new Goblin(this));
            else if (whoHimIs == 3)
                monsterVector.push_back(new Bogeyman(this));
            else if (whoHimIs == 4)
                monsterVector.push_back(new Dragon(this));
        }
    }
}


//genObjects
// Generates new objects to fill the object vector.
void Dungeon::genObjects()
{
    int n_obs = randInt(2, 3);
    for (int i = 0; i < n_obs; i++)
    {
        int whosThatPokemon = randInt(1, 7);
        switch (whosThatPokemon)
        {
            case 1:
                objectVector.push_back(new ShortSword);
                break;
            case 2:
                objectVector.push_back(new LongSword);
                break;
            case 3:
                objectVector.push_back(new Mace);
                break;
            case 4:
                objectVector.push_back(new HPScroll);
                break;
            case 5:
                objectVector.push_back(new ArmorScroll);
                break;
            case 6:
                objectVector.push_back(new StrengthScroll);
                break;
            case 7:
                objectVector.push_back(new DexScroll);
                break;
            default:
                break;
        }
    }
    
}

void Dungeon::spawnPlayer()         //randomly plops the player in the dungeon.
{
    if (m_player->getRowPos() && m_player->getColPos())
    {
        m_player->clearLastPositionOnMap();
    }
    
    int temp_row;
    int temp_col;         //create temp vars to hold coordinates.
    
    do {
        temp_row = randInt(1,17);
        temp_col = randInt(1,69);
    } while (!actorPosValid(temp_row, temp_col));
    
    m_player->setPosition(temp_row, temp_col);
    setChar(temp_row, temp_col, PLAYER_DISPLAY);
}


//spawnmonsters
// iterates through the monster vector, spawning them 1 by 1, randomly.
void Dungeon::spawnMonsters()
{
    int temp_row;
    int temp_col;
    
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++)
    {
        do {
            temp_row = randInt(1,17);
            temp_col = randInt(1,69);
        } while (!actorPosValid(temp_row, temp_col));
        (*mon)->setPosition(temp_row, temp_col);
    }
}

//spawnobjects
//goes through vector and puts them on the map
void Dungeon::spawnObjects()
{
    //Spawn the drops.
    
    int temp_row;
    int temp_col;
    
    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end(); obj++)
    {
        do {
            temp_row = randInt(1,17);
            temp_col = randInt(1,69);
        } while (!objectPosValid(temp_row, temp_col));
        
        (*obj)->setPos(temp_row, temp_col);
    }
    
    //  Spawn Idol or Stairs.
    
    do {
        temp_row = randInt(1,17);
        temp_col = randInt(1,69);
    } while (!objectPosValid(temp_row, temp_col));
    
    if (level == 4)
    {
        goldenIdol = new Object(temp_row, temp_col, "Golden Idol");       //constructed with Random Position generated when spawned.
    }
    else if (level < 4)
    {
        m_stairs = new Object(temp_row, temp_col, "Stairs");              //constructed with Random position generated when spawned.
    }
}


void Dungeon::playMove()
{
    m_player->takeTurn();
    // Iterate through monsters to have them take turn
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++)
    {
        (*mon)->takeTurn();
    }
}

void Dungeon::drawDungeon()
{
    for (int r = 0; r < MAXROWS; r++)
    {
        for (int c = 0; c < MAXCOLS; c++)
        {
            if (r == 0 || r == 17)              //top row and bottom row are walls
                map[r][c] = '#';
            else if (c == 0 || c == 69)              //leftmost and rightmost cols are walls.
                map[r][c] = '#';
            else
                map[r][c] = ' ';
        }
    }
}

bool Dungeon::isPlayer(int row, int col)
{
    if (row == m_player->getRowPos() && col ==m_player->getColPos())
        return true;
    else
        return false;
}

bool Dungeon::isMob(int row, int col)
{
    if (getSymbol(row, col) == BOGEYMAN_DISPLAY
        || getSymbol(row, col) == GOBLIN_DISPLAY
        || getSymbol(row, col) == SNAKEWOMAN_DISPLAY
        || getSymbol(row, col) == DRAGON_DISPLAY )
        return true;
    else
        return false;
}

bool Dungeon::isObj(int row, int col)
{
    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end(); obj++)
    {
        if (row == (*obj)->getRow() && col == (*obj)->getCol())
            return true;
    }
    
    if (getSymbol(row, col) == SCROLL_DISPLAY
        || getSymbol(row, col) == WEAPON_DISPLAY
        || getSymbol(row, col) == STAIR_DISPLAY
        || getSymbol(row, col) == GOLDEN_IDOL_DISPLAY)
        return true;
    else
        return false;
}

bool Dungeon::isStairs(int row, int col)
{
    if (row == m_stairs->getRow() && col == m_stairs->getCol())
        return true;
    else
        return false;
}

bool Dungeon::isIdol(int row, int col)
{
    if (row == goldenIdol->getRow() && col == goldenIdol->getCol())
        return true;
    else
        return false;
}

void Dungeon::eraseObject(Object* object)
{
    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end(); obj++)
    {
        if ((*obj)->getRow() == object->getRow() && (*obj)->getCol() == object->getCol())
        {
            map[object->getRow()][object->getCol()] = ' ';
            setChar(object->getRow(), object->getCol(), ' ');
            objectVector.erase(obj);
            return;
        }
    }
}

void Dungeon::printDungeon()
{
    removeDeadMobs();    // Does what the name suggests.

    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end() ; obj++)     //Set Objects first, since actors can be on top.
    {
        // Spawn the stairs or idol first.
        if ((*obj)->getName() == "Golden Idol")
            map[(*obj)->getRow()][(*obj)->getCol()] = '&';
        else if ((*obj)->getName() == "Stairs")
            map[(*obj)->getRow()][(*obj)->getCol()] = '>';
        
        // Spawn the scrolls and weapons next.
        Scroll* testScroll = dynamic_cast<Scroll*>(*obj);
        if (testScroll != nullptr)
            map[(*obj)->getRow()][(*obj)->getCol()] = '?';
        else
            map[(*obj)->getRow()][(*obj)->getCol()] = ')';
    }
        // Spawn Idol or Stairs last.
    if (level == 4)
        map[goldenIdol->getRow()][goldenIdol->getCol()] = '&';
    else if (level < 4)
        map[m_stairs->getRow()][m_stairs->getCol()] = '>';
    
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++)   //Set Monsters.
    {
        string name = (*mon)->getName();
        int monRow = (*mon)->getRowPos();
        int monCol = (*mon)->getColPos();
        
        if (name == BOGEYMAN)
            map[monRow][monCol] = BOGEYMAN_DISPLAY;
        else if (name == SNAKEWOMAN)
            map[monRow][monCol] = SNAKEWOMAN_DISPLAY;
        else if (name == DRAGON)
            map[monRow][monCol] = DRAGON_DISPLAY;
        else if (name == GOBLIN)
            map[monRow][monCol] = GOBLIN_DISPLAY;
    }
    
    // Set the player last, so nothing cover it up.
    if (m_player != nullptr)
        map[m_player->getRowPos()][m_player->getColPos()] = '@';

    for (int r = 0; r < MAXROWS; r++)           //Print map
    {
        for (int c = 0; c < MAXCOLS; c++)
        {
            cout << map[r][c];
        }
        cout << endl;
    }
    
    // Cout Player stats
    //ie. Dungeon Level: 3, Hit points: 10, Armor: 3, Strength: 2, Dexterity: 2
    cout << "Dungeon Level: " << level << ", Hit points: " << m_player->getHP() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDex() << endl;
    cout << endl;
    
    
    //Cout game text
    //ie. Player slashes short sword at the Dragon and misses.
    for (vector<string>::iterator txt = textVector.begin(); txt != textVector.end(); txt++)
    {
        cout << *txt << endl;
    }
    textVector.clear();       //clear the text vector with each turn.
}






Monster* Dungeon::getMob(int row, int col, Monster* &mob)
{
    int i = 0;
    // check the vector for any monsters matching the coordinates.
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++, i++)
    {
        if ((*mon)->getRowPos() == row && (*mon)->getColPos() == col)
        {
            mob = (*mon);
            return mob;
        }
    }
    // if no corresponding monster in monstervector, set mob to null and return.
    mob = nullptr;
    return mob;
}

Object* Dungeon::getObj(int row, int col, Object* &obj)
{
    // check objvector for corresponding object.
    for (vector<Object*>::iterator obs = objectVector.begin(); obs != objectVector.end(); obs++)
        if ((*obs)->getRow() == row && (*obs)->getCol() == col)
        {
            obj = *obs;
            return obj;
        }
    // if no corresponding object, set to null and return
    obj = nullptr;
    return obj;
}


bool Dungeon::actorPosValid(int row, int col)   // returns true as long as position isn't occupied by a wall or another actor.
{
    if (getSymbol(row, col) == WALL_DISPLAY
        || getSymbol(row, col) == PLAYER_DISPLAY
        || getSymbol(row, col) == BOGEYMAN_DISPLAY
        || getSymbol(row, col) == GOBLIN_DISPLAY
        || getSymbol(row, col) == SNAKEWOMAN_DISPLAY
        || getSymbol(row, col) == DRAGON_DISPLAY )
        return false;
    else
        return true;
}

bool Dungeon::objectPosValid(int row, int col) // returns true as long as position isnt occupied by walls, another object, or stairs.
{
    if (getSymbol(row, col) == WALL_DISPLAY
        || getSymbol(row, col) == SCROLL_DISPLAY
        || getSymbol(row, col) == WEAPON_DISPLAY
        || getSymbol(row, col) == STAIR_DISPLAY
        || getSymbol(row, col) == GOLDEN_IDOL_DISPLAY)
        return false;
    else
        return true;
}

void Dungeon::removeDeadMobs()      //clears B,S,D,G characters form the map after they die.
{
    for (vector<Monster*>::iterator mon = monsterVector.begin() ; mon != monsterVector.end(); )
    {
        if ((*mon)->isDead())
        {
            map[(*mon)->getRowPos()][(*mon)->getColPos()] = ' ';    //delete monster from map
            delete (*mon);                                          //delete the monster from memory
            mon = monsterVector.erase(mon);                           //remove monster pointer from vector.
        }
        else
            mon++;
    }
}

void Dungeon::clearMonsters()
{
    for (vector<Monster*>::iterator mon = monsterVector.begin(); mon != monsterVector.end(); mon++)
    {
        delete (*mon);          //deletes all the monster objects
    }
    monsterVector.clear();      //clears the vector of dead pointers
}

void Dungeon::clearObjects()
{
    for (vector<Object*>::iterator obj = objectVector.begin(); obj != objectVector.end(); obj++)
    {
        delete (*obj);          //delete all the object objects (lol)
    }
    objectVector.clear();       //clears the vector of dead pointers
}
