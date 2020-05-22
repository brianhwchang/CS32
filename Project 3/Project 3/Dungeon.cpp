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
#include <list>
#include <iostream>

using namespace std;

Dungeon::Dungeon()
{
    drawDungeon();
    level = 0;                      //start at top level 0
    n_objects = randInt(2, 3);      //spawn between 2-3 objects per level
    m_player = new Player(this);
}

Dungeon::~Dungeon()
{
    if (m_player != nullptr) {
        delete m_player;
        m_player = nullptr;
    }
    for (list<Monster*>::iterator mon = monsterList.begin(); mon != monsterList.end(); mon++)   //Freeing memory allocated for monsters
    {
        delete (*mon);
    }
    for (list<Object*>::iterator obj = objectList.begin(); obj != objectList.end(); obj++)      //Free memory allocated for objects
    {
        delete (*obj);
    }
    
    //TODO: CLEAR MEMORY FOR STAIRS AND GOLDEN IDOL
}

//genMonsters();
//looks at the level to decide number (using formula)
//creates a random number of monsters

void Dungeon::genMonsters()
{
    // M randomly placed monsters, where M = randInt(2, 5*(L+1)+1) (So, for example, level 3 will have between 2 and 21 monsters.)
    int n_mobs = randInt(2, 5*(level+1)+1 );

    if (level < 2) //only goblins and snakewomen
    {
        for (int i = 0; i < n_mobs; i++)
        {
            bool snake = trueWithProbability(1.0/2.0);
            if (snake)
            {
                monsterList.push_back(new Snakewoman(this));
            }
            else
                monsterList.push_back(new Goblin(this));
        }
    }
    
    else if (level == 2) //Goblins, Snakes, and Bogeyboys
    {
        for (int i = 0; i < n_mobs; i++)
        {
            int whoDatBoi = randInt(1, 3);
            
            if (whoDatBoi == 1)
                monsterList.push_back(new Snakewoman(this));
            else if (whoDatBoi == 2)
                monsterList.push_back(new Goblin(this));
            else if (whoDatBoi == 3)
                monsterList.push_back(new Bogeyman(this));
        }
    }
    
    else if (level > 2)     //Goblins, Snakes, Bogeybuddies, and Dragoons.
    {
        for (int i = 0; i < n_mobs; i++)
        {
            int whoHimIs = randInt(1, 4);
            
            if (whoHimIs == 1)
                monsterList.push_back(new Snakewoman(this));
            else if (whoHimIs == 2)
                monsterList.push_back(new Goblin(this));
            else if (whoHimIs == 3)
                monsterList.push_back(new Bogeyman(this));
            else if (whoHimIs == 4)
                monsterList.push_back(new Dragon(this));
        }
    }
}

//spawnmonsters
//goes through the list and puts them on the map

//genObjects


//spawnobjects
//goes through list and puts them on the map


void Dungeon::playMove()
{
    m_player->takeTurn();
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

void Dungeon::printDungeon()
{
    removeDead();
    if (m_player != nullptr)                                                                    //Set player
        map[m_player->getRowPos()][m_player->getColPos()] = '@';
    
    
    for (list<Monster*>::iterator mon = monsterList.begin(); mon != monsterList.end(); mon++)   //Set Monsters.
    {
        string name = (*mon)->getName();
        int monRow = (*mon)->getRowPos();
        int monCol = (*mon)->getColPos();
        
        if (name == "Bogeyman")
            map[monRow][monCol] = 'B';
        else if (name == "Snakewoman")
            map[monRow][monCol] = 'S';
        else if (name == "Dragon")
            map[monRow][monCol] = 'D';
        else if (name == "Goblin")
            map[monRow][monCol] = 'G';
    }
    
    for (list<Object*>::iterator obj = objectList.begin(); obj != objectList.end() ; obj++)     //Set Objects
    {
        Scroll* testScroll = dynamic_cast<Scroll*>(*obj);
        
        if (testScroll != nullptr)
            map[(*obj)->getRow()][(*obj)->getCol()] = '?';
        else
            map[(*obj)->getRow()][(*obj)->getCol()] = ')';
    }
    
    //TODO: Spawn stairs or golden idol depending on level
    

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
    cout << "Dungeon Level: " << level << ", Hit points: " << m_player->getHP() << ", Armor: " << m_player->getArmor();
    cout << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDex();
    
    //Cout game text
    //ie. Player slashes short sword at the Dragon and misses.
    for (list<string>::iterator txt = textList.begin(); txt != textList.end(); txt++)
    {
        cout << *txt;
    }
    textList.clear();       //clear the text list with each turn.
}






void Dungeon::setChar(int row, int col, char ch)
{
    map[row][col] = ch;
}

//TODO: SPAWN PLAYER FXN.

void Dungeon::spawnPlayer()
{
    int temp_row, temp_col;
    
    do {
        temp_row = randInt(1,17);       //@@@@@@@@@@@@@@@ ASK ALISSA
        temp_col = randInt(1,69);
    } while (!actorPosValid(temp_row, temp_col));
    
    m_player->setPosition(temp_row, temp_col);
    setChar(temp_row, temp_col, '@');   //@@@@@@@ ASK ALISSA @@@@@@@@@@@
}

//void Dungeon::spawnMonster(string name)          //should take in what kind of monster right?
//{
//    int temp_row, temp_col;
//    
//    do {
//        temp_row = randInt(1,17);       //@@@@@@@@@@@@@@@ ASK ALISSA
//        temp_col = randInt(1,69);
//    } while (!actorPosValid(temp_row, temp_col));
//    
//    switch (name) {
//        case "bogeyman":
//            <#statements#>
//            break;
//            
//        default:
//            break;
//    }
//}

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

void Dungeon::removeDead()      //clears B,S,D,G characters form the map after they die.
{
    for (list<Monster*>::iterator mon = monsterList.begin() ; mon != monsterList.end(); )
    {
        if ((*mon)->isDead())
        {
            map[(*mon)->getRowPos()][(*mon)->getColPos()] = ' ';    //delete monster from map
            delete (*mon);                                          //delete the monster from memory
            mon = monsterList.erase(mon);                           //remove monster pointer from list.
        }
        else
            mon++;
    }
}


