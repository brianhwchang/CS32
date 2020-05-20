//
//  Dungeon.cpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Dungeon.h"
#include "globals.h"

#include <iostream>

using namespace std;

Dungeon::Dungeon()
{
    for (int r = 0; r < MAXROWS; r++)
        for (int c = 0; c < MAXCOLS; c++)
        {
            if (r == 0 || r == 17)              //top row and bottom row are walls
                m_Dungeon[r][c] = '#';
            else if (c == 0 || c == 69)              //leftmost and rightmost cols are walls.
                m_Dungeon[r][c] = '#';
            else
                m_Dungeon[r][c] = ' ';
        }
}



void Dungeon::printDungeon()
{
    for (int r = 0; r < MAXROWS; r++)
    {
        for (int c = 0; c < MAXCOLS; c++)
        {
            cout << m_Dungeon[r][c];
        }
    cout << endl;
    }
}

bool Dungeon::spawnPlayer(int row, int col)
{
    if (! isPostionValid(row, col))           //make sure the spot isnt occupied by a wall or another actor.
        return false;

    if (m_player != nullptr)                  //Only one player per dungeon (per game)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

bool Dungeon::isPostionValid(int row, int col)
{
    if (row <= 0 || row >= MAXROWS || col <= 0 || col >= MAXCOLS)
        return false;
    
    if (m_Dungeon[row][col] == '#' || m_Dungeon[row][col] == 'B' || m_Dungeon[row][col] == 'D' || m_Dungeon[row][col] == 'S'|| m_Dungeon[row][col] == 'G' || m_Dungeon[row][col] == '@')
        return false;
    else
        return true;
}
