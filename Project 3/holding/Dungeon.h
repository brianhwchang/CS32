//
//  Dungeon.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Dungeon_h
#define Dungeon_h

#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>

#include "Actor.h"
#include "globals.h"
#include "Object.h"

using namespace std;

class Player;
class Monster;

class Dungeon
{
public:
    Dungeon();
    ~Dungeon();
    void printDungeon();

    //getter functions
    char getSymbol(int row, int col) {return map[row][col];}
    Player* getPlayer() const {return m_player;}
    Monster* getMonster(int row, int col);
    //object* getStair() const;
    //object* getGoldenIdol() const;
    
    list<Monster*>& getMonsterList() {return monsterList;}
    list<Object*>& getObjectList() {return objectList;}
    list<string>& getTextList() {return textList;}

    //setter functions
    void drawDungeon();
    void setChar(int row, int col, char ch);
    void genPlayer();       //generate 1 player.
    void genMonsters();     //generate new monsters
    void genObjects();      //generate new objects
    void spawnPlayer();     //Randomly spawns player in dungeon
    void spawnObjects();    //spawn objects in map.
    void spawnMonsters();   //spawn Monsters in map.

    //---------------------Helper Functions------------------
    
    bool isValidPos(int row, int col);
    bool actorPosValid(int row, int col);
    bool objectPosValid(int row, int col);
    bool isPlayer(int row, int col);
    bool isMob(int row, int col);
    bool isObj(int row, int col);
    
    //Turn-based functions
    
    void removeDead();
    char getCurrentMove() const { return m_currentMove; };
    void setCurrentMove(char c) { m_currentMove = c; };
    void playMove();

    
private:
    char map[18][70];             //2D Char Array that functions as the map.
    Player* m_player;             //Dat boi
    Object* goldenIdol;           //Idol
    Object* stairs;               //Stairs
    list<Monster*> monsterList;   //list of monster pointers (per level)
    list<Object*> objectList;     //list of object pointers (per level)
    list<string> textList;        //list of strings to communicate with client.
    
    int level;
    int n_objects;
    char m_currentMove;
};

    //Dungeon has to be 70 cols wide and 18 rows high.
    //All coords along row 0 (top row) and row 17 (bottom row) should be '#'
    //All coords along col 0 (left most col) and col 69 (right most col) should be '#'
    //Should look like rooms connected by corridors.
    
    //constructor should have some bool as argument 'FinalLevel' where if true, spawn the golden idol.
    
    
#endif /* Dungeon_h */
