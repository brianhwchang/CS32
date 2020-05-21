//
//  Actor.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include <stdio.h>
#include "Dungeon.h"

using namespace std;


class Dungeon;

class Actor
{

public:
    Actor(int row, int col, int healthPoints, int armor, int strength, int dex, int weapon, int sleepTime);
    
    virtual void makeMove()=0;
    
    
    
    
    
    //TODO: Move Function
        //Move Up (up arrow key or k)
            //if not occupied by a wall or another actor
            //position[m_x][m_y]
    
        //
    
    
    //TODO: Attack Function
    
    //
    
    //Getter Functions
    
    int getRowPos() {return m_row;}
    int getColPos() {return m_col;}
    
    int getHP() {return m_hp;}
    int getArmor() {return m_armor;}
    int getStrength() {return m_strength;}
    int getDex() {return m_dex;}
    int getSleepTime() {return m_sleepTime;}
    
    
    //Incrementer Functions
    void addHP(int amt) {m_hp = m_hp + amt;}
    void addMaxHP(int amt) {m_maxHP = m_maxHP + amt;}
    void addArmor(int amt) {m_armor = m_armor + amt;}
    void addStrength(int amt) {m_strength = m_strength + amt;}
    void addDex(int amt) {m_dex = m_dex + amt;}
    void addSleepTime(int amt) {m_sleepTime = m_sleepTime + amt;}
    
    //Decrementer Functions
    void reduceHP(int amt) {m_hp = m_hp - amt;}
    void reduceSleepTime(int amt) {m_sleepTime = m_sleepTime - amt;}
    
    //Helper Functions
    bool isDead();
    
private:
    int m_row;
    int m_col;
    int m_hp;
    int m_maxHP;
    int m_armor;
    int m_strength;
    int m_dex;
    int m_weapon;
    int m_sleepTime;

};

class Bogeyman : public Actor
{
    //only spawn at level 2 or deeper.
    
    // Between 5-10 HP
    // 2 Armor
    // Between 2-3 Strength
    // Between 2-3 Dex
    // Weapon: Short Sword
    
    //if there are 5 or fewer spaces between the player and BG, the bg can smell the player
    //If the BG smells the player, it'll move closer.
    //Doesnt care about pathfinding, just wants to be as close as possible
        //could impletement like judge closeness by BG_xcoord - Player_xcoord, or BG_ycoord - Player_ycoord
        //as long as the difference between the coordintates decreases, its a "good" move for the BG
    
    // 1/10 chance of dropping magic axe upon death.
};

class Snakewoman : public Actor
{
    //Spawn at all levels.
    
    // Between 3 to 6 HP
    // 3 Armor
    // 2 Strength
    // 3 Dex
    // Weapon: Magic Fangs of Sleep
    
    //if it can reach the player in 3 or fewer moves, it can smell player. (bool - Can smell player (SW coord, Player Coord, max dist)
        // can smell if (Delta X + Delta Y <= 3)
                //return true
    //if it can smell player move towards
        // if post-move delta X or delta Y is less than pre-move Delta-X or Delta-Y. Good move.
    
    // 1/3 chance of dropping magic fangs of sleep upon death.
};

class Goblin : public Actor
{
    // Spawn at all levels.
    
    // Between 15 to 20 HP.
    // 1 Armor
    // 3 Strength
    // 1 Dex
    // Weapon: Short Sword
    
    //if Pathexists between goblin and player within 15 steps, can smell.
    //Makes optimal move.
    
    // 1/3 chance of dropping magic axe or fang of sleep on death.
};

class Dragon : public Actor
{
    //Spawns at level 3 or deeper.
    
    // Between 20 to 25 HP
    // 4 Armor, 4 Strength, 4 Dex.
    // Weapon: Long Sword
    
    // 1/10 chance of regaining 1 HP at start of turn.
    // 100% chance of dropping a scroll upon death.
};


#endif /* Actor_h */
