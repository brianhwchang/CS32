#ifndef Actor_h
#define Actor_h

#include <stdio.h>
#include "globals.h"
#include "Dungeon.h"
#include "utilities.h"

using namespace std;

class Dungeon;

class Actor
{

public:
    Actor(int row, int col, int healthPoints, int armor, int strength, int dex, int weapon, int sleepTime, Dungeon* dungeon);
    virtual ~Actor();
    virtual void makeMove() = 0;            //pure virtual function, such that Actor is an abstract base class.
    
    //TODO: Move Function
        //Move Up (up arrow key or k)
            //if not occupied by a wall or another actor
            //position[m_x][m_y]
    
        //
    
    
    //TODO: Attack Function
    
    //Setter Functions
    void setPosition(int r, int c) { m_row = r; m_col = c; }
    

    //Getter Functions
    Dungeon* getDungeon() const { return m_dungeon; }
    
    int getRowPos() {return m_row;}
    int getColPos() {return m_col;}
    
    int getHP() {return m_hp;}
    int getMaxHP() {return m_maxHP;}
    int getArmor() {return m_armor;}
    int getStrength() {return m_strength;}
    int getDex() {return m_dex;}
    int getSleepTime() {return m_sleepTime;}
    
    
    //Incrementer Functions
    void addHP(int amt)
    {
        if (m_hp >= m_maxHP)           //Don't go above max hp.
            return;
        if ( (m_hp + amt) >= m_maxHP)  //if cur hp + amt > max_hp, just set HP to max.
            m_hp = m_maxHP;
        if ( (m_hp + amt) < m_maxHP)   //if cur hp + amt < max_hp, add amt to m_hp.
            m_hp = m_hp + amt;
        else
            return;
    }
    
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
    
    Dungeon* m_dungeon;
};

const int PLAYER_HP             = 20;
const int PLAYER_MAX_HP         = 20;
const int PLAYER_ARMOR          = 2;
const int PLAYER_STRENGTH       = 2;
const int PLAYER_DEXTERITY      = 2;
const int PLAYER_SLEEP_TIME     = 0;
const int PLAYER_WEAPON         = SHORT_SWORD;

class Player : public Actor
{
public:
    Player(Dungeon* dungeon);
    virtual ~Player();
    virtual void makeMove();
    
    
};





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//            MONSTERS IMPLEMENTATION
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int BOGEY_HP             = randInt(5, 10);
const int BOGEY_ARMOR          = 2;
const int BOGEY_STRENGTH       = randInt(2, 3);
const int BOGEY_DEXTERITY      = randInt(2, 3);
const int BOGEY_SLEEP_TIME     = 0;
const int BOGEY_WEAPON         = SHORT_SWORD;

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



const int SNAKE_HP             = randInt(3, 6);
const int SNAKE_ARMOR          = 3;
const int SNAKE_STRENGTH       = 2;
const int SNAKE_DEXTERITY      = 3;
const int SNAKE_SLEEP_TIME     = 0;
const int SNAKE_WEAPON         = MAGIC_FANG;

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

const int GOBLIN_HP             = randInt(15, 20);
const int GOBLIN_ARMOR          = 1;
const int GOBLIN_STRENGTH       = 3;
const int GOBLIN_DEXTERITY      = 1;
const int GOBLIN_SLEEP_TIME     = 0;
const int GOBLIN_WEAPON         = SHORT_SWORD;

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

const int DRAGON_HP             = randInt(20, 25);
const int DRAGON_ARMOR          = 4;
const int DRAGON_STRENGTH       = 4;
const int DRAGON_DEXTERITY      = 4;
const int DRAGON_SLEEP_TIME     = 0;
const int DRAGON_WEAPON         = LONG_SWORD;

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