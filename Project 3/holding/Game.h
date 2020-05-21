//
//  Game.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Dungeon.h"

// You may add data members and other member functions to this class.

class Dungeon;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    
private:
    Dungeon* m_Dungeon;
};

#endif // GAME_INCLUDED
