//
//  Player.hpp
//  Project 1
//
//  Created by Brian Chang on 4/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string>
#include "Arena.h"

using namespace std;

class Arena; //uses arena variable

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;


      // Mutators
    string dropPoisonVial();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* Player_h */
