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
    Monster* getMob(int row, int col, Monster* &mob);
    Object* getObj(int row, int col, Object* &obj);
    Object* getStair() {return m_stairs;}
    Object* getGoldenIdol() {return goldenIdol;}

    vector<Monster*>& getMonsterVector() {return monsterVector;}
    vector<Object*>& getObjectVector() {return objectVector;}
    vector<string>& getTextVector() {return textVector;}


    //setter functions
    void drawDungeon();
    void setChar(int row, int col, char ch);
    void genPlayer();       //generate 1 player.
    void genMonsters();     //generate new monsters
    void genObjects();      //generate new objects
    void spawnPlayer();     //Randomly spawns player in dungeon
    void spawnObjects();    //spawn objects in map.
    void spawnMonsters();   //spawn Monsters in map.
    
    void clearMonsters() {monsterVector.clear();}   //wipes current monster vector
    void clearObjects() {objectVector.clear();}     //wipes current object vector

    //---------------------Helper Functions------------------
    
    bool isValidPos(int row, int col);
    bool actorPosValid(int row, int col);
    bool objectPosValid(int row, int col);
    
    void removeDead();
    char getCurrentMove() const { return m_currentMove; };
    void setCurrentMove(char c) { m_currentMove = c; };
    void playMove();
    
    bool isPlayer(int row, int col);
    bool isMob(int row, int col);
    bool isObj(int row, int col);

private:
    char map[18][70];   //2D Char Array that functions as the map.
    Player* m_player;
    Object* goldenIdol;
    Object* m_stairs;
    vector<Monster*> monsterVector;
    vector<Object*> objectVector;
    vector<string> textVector;         //could be done as a vector but I dont think its a big deal
    
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
