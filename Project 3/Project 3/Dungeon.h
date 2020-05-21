//
//  Dungeon.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Dungeon_h
#define Dungeon_h

#include "Actor.h"

#include <stdio.h>
#include <vector>
#include <iostream>

#include "globals.h"

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
    Monster* getMonster(int row, int col, Monster* Mon);
    //object* getStair() const;
    //object* getGoldenIdol() const;
    //list<object*>& getObjectList();
    //list<monster*>& getMonsterList();
    
    //setter functions
    void setChar(int row, int col, char ch);
    
    
    void spawnPlayer();     //Randomly spawns player in dungeon
    char getCurrentMove() const { return m_currentMove; };
    void setCurrentMove(char c) { m_currentMove = c; };
    void playMove();

    
private:
    char map[18][70];   //2D Char Array that functions as the map.
    Player* m_player;
    
    char m_currentMove;
    
    //---------------------Helper Functions------------------
    
    bool isValidPos(int row, int col);
    bool actorPosValid(int row, int col);
    bool objectPosValid(int row, int col);
};

    //Dungeon has to be 70 cols wide and 18 rows high.
    //All coords along row 0 (top row) and row 17 (bottom row) should be '#'
    //All coords along col 0 (left most col) and col 69 (right most col) should be '#'
    //Should look like rooms connected by corridors.
    
    //constructor should have some bool as argument 'FinalLevel' where if true, spawn the golden idol.
    
    
#endif /* Dungeon_h */