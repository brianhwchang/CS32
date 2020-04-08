//
//  Vampire.hpp
//  Project 1
//
//  Created by Brian Chang on 4/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Vampire_h
#define Vampire_h

#include <stdio.h>
#include "Arena.h"
using namespace std;

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Vampire declaration.

class Vampire
{
  public:
      // Constructor
    Vampire(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* Vampire_h */
