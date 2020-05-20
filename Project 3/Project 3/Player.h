//
//  Player.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include "Actor.h"
#include "Dungeon.h"

class Dungeon;

class Player : public Actor
{
public:
    
    
private:
    Dungeon* m_dungeon;
    int m_row;
    int m_col;
    
};

#endif /* Player_h */
