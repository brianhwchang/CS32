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
                map[r][c] = '#';
            else if (c == 0 || c == 69)              //leftmost and rightmost cols are walls.
                map[r][c] = '#';
            else
                map[r][c] = ' ';
        }
    
    m_player = new Player(this);
}

Dungeon::~Dungeon()
{
    if (m_player != nullptr) {
        delete m_player;
        m_player = nullptr;
    }
}

void Dungeon::playMove()
{
    m_player->makeMove();
}

void Dungeon::printDungeon()
{
    for (int r = 0; r < MAXROWS; r++)
    {
        for (int c = 0; c < MAXCOLS; c++)
        {
            cout << map[r][c];
        }
    cout << endl;
    }
}

//TODO: SPAWN PLAYER FXN.
//bool Dungeon::spawnPlayer(int row, int col)
//{
//    if (! isPostionValid(row, col))           //make sure the spot isnt occupied by a wall or another actor.
//        return false;
//
//    if (m_player != nullptr)                  //Only one player per dungeon (per game)
//        return false;
//
//    m_player = new Player(this, r, c);
//    return true;
//}

void Dungeon::setChar(int row, int col, char ch)
{
    map[row][col] = ch;
}

void Dungeon::spawnPlayer()
{
    int temp_row, temp_col;
    do {
        temp_row = randInt(1,17);       //@@@@@@@@@@@@@@@ ASK ALISSA
        temp_col = randInt(1,69);
    } while (!actorPosValid(temp_row, temp_col));
    
    m_player->setPosition(temp_row, temp_col);
    //m_Dungeon->setChar(temp_row, temp_col, '@');   //@@@@@@@ ASK ALISSA @@@@@@@@@@@
}



bool Dungeon::actorPosValid(int row, int col)   //returns true as long as position isn't occupied by a wall or another actor.
{
    if (getSymbol(row, col) == '#' || getSymbol(row, col) == '@' || getSymbol(row, col) == 'B' || getSymbol(row, col) == 'G' || getSymbol(row, col) == 'S' || getSymbol(row, col) == 'D')
        return false;
    else
        return true;
}

bool Dungeon::objectPosValid(int row, int col) //returns true as long as position isnt occupied by walls, another object, or stairs.
{
    if (getSymbol(row, col) == '#' || getSymbol(row, col) == '?' || getSymbol(row, col) == ')' || getSymbol(row, col) == '>' || getSymbol(row, col) == '&')
        return false;
    else
        return true;
}
