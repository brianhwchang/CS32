//
//  Actor.cpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Actor.h"


//All actors must have:
//Postion
//Health Points
//Armor
//Strength
//Dex
//Weapon
//SleepTime
Actor::Actor(int row, int col, int healthPoints, int armor, int strength, int dex, int weapon, int sleepTime)
: m_row(row), m_col(col), m_hp(healthPoints), m_armor(armor), m_strength(strength), m_dex(dex), m_weapon(weapon), m_sleepTime(sleepTime)
{ }


bool Actor::isDead()
{
    if (m_hp <= 0)
        return true;
    else
        return false;
}

