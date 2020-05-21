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

#include "globals.h"
#include "Player.h"

class Player;

class Dungeon
{
public:
    Dungeon();
    void printDungeon();
    bool spawnPlayer(int row, int col);

    
private:
    char m_Dungeon[MAXROWS][MAXCOLS];
    Player* m_player;
    vector<Actor> ActorsV;
    
    
    //---------------------Helper Functions------------------
    
    bool isValidPos(int row, int col);
};

    //Dungeon has to be 70 cols wide and 18 rows high.
    //All coords along row 0 (top row) and row 17 (bottom row) should be '#'
    //All coords along col 0 (left most col) and col 69 (right most col) should be '#'
    //Should look like rooms connected by corridors.
    
    //constructor should have some bool as argument 'FinalLevel' where if true, spawn the golden idol.
    
    
#endif /* Dungeon_h */
