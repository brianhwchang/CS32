//
//  Game.hpp
//  Project 1
//
//  Created by Brian Chang on 4/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

#include "Arena.h" //for the arena variables
#include <stdio.h>

using namespace std;

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

#endif /* Game_h */
