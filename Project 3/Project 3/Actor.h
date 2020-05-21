#ifndef Actor_h
#define Actor_h

#include <stdio.h>
#include "globals.h"
#include "Dungeon.h"
#include "utilities.h"
#include "Object.h"
#include <string>
#include <list>
 
using namespace std;

class Dungeon;

class Actor
{
public:
    //Constructor and Destructor
    Actor(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string species);
    virtual ~Actor();
    
    
    virtual void takeTurn() = 0;            //pure virtual function, such that Actor is an abstract base class.
    void attack(Actor* attacker, Actor* defender);
    //TODO: Attack Function
    //TODO: Move/Take turn
    
    //Setter Functions
    void setPosition(int r, int c) { m_row = r; m_col = c; }
    void setWeapon(Weapon* weapon);
    
    //Position Getters
    int getRowPos() {return m_row;}
    int getColPos() {return m_col;}
    //Stat Getters
    int getHP() {return m_hp;}
    int getMaxHP() {return m_maxHP;}
    int getArmor() {return m_armor;}
    int getStrength() {return m_strength;}
    int getDex() {return m_dex;}
    int getSleepTime() {return m_sleepTime;}
    //Misc Getters
    string getName() {return m_name;}
    Dungeon* getDungeon() const { return m_dungeon;}
    Weapon* getWeapon() const { return m_weapon;}
    
    //Incrementer Functions
    void addHP(int amt);
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
    bool isAsleep();
    
private:
    int m_row;
    int m_col;
    int m_hp;
    int m_maxHP;
    int m_armor;
    int m_strength;
    int m_dex;
    int m_sleepTime;
    string m_name;
    Weapon* m_weapon;
    Dungeon* m_dungeon;
};






//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//--------------PLAYER CLASS-------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//const Weapon* PLAYER_WEAPON     = ShortSword;             //@@@@@@@@  ASK ALISSA  @@@@@@@@@@@@@@@@

class Player : public Actor
{
public:
    Player(Dungeon* dungeon);
    ~Player();
    
    virtual void takeTurn();
    
    //input functions
    void pickUp();                  //pick up and object you're standing on with 'g'
    void weildWeapon(char ch);      //change weapons 'w'
    void readScroll(char ch);       //read scroll 'r'
    void openIventory();            //open inventory with 'i'
    void descend();                 //descend to lower level with '>'
    void cheat();                   //sets the player's strength to 9 and maximum hit points to 50.
    
    //misc
    list<Object*> getInventory();
    void winGame() {win = true;}    //sets win to true;

private:
    list<Object*> inventory;
    bool win;
    
};



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//            MONSTERS IMPLEMENTATION
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class Monster : public Actor
{
public:
    Monster(int row, int col, int healthPoints, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string species);
    virtual ~Monster() {};
    
    virtual void takeTurn();
    virtual void dropItem() = 0;
    bool CanSmellPlayer(Dungeon* dungeon, int ReqDist);
    void dropItem(Dungeon* dungeon, Monster* mon);
    
    
    
    
};

const int BOGEY_HP             = randInt(5, 10);
const int BOGEY_ARMOR          = 2;
const int BOGEY_STRENGTH       = randInt(2, 3);
const int BOGEY_DEXTERITY      = randInt(2, 3);
const int BOGEY_SLEEP_TIME     = 0;
//Weapon ShortSword

class Bogeyman : public Monster
{
    //only spawn at level 2 or deeper.

    Bogeyman(Dungeon* dungeon);
    ~Bogeyman();

    virtual void takeTurn();
    virtual void dropItem();
    
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
// Weapon: Magic Fangs of Sleep

class Snakewoman : public Monster
{
    //Spawn at all levels.
    
    Snakewoman(Dungeon* dungeon);
    ~Snakewoman();
    
    virtual void takeTurn();
    virtual void dropItem();

    //if it can reach the player in 3 or fewer moves, it can smell player. (bool - Can smell player (SW coord, Player Coord, max dist)
        // can smell if (Delta X + Delta Y <= 3)
                //return true
    //if it can smell player move towards
        // if post-move delta X or delta Y is less than pre-move Delta-X or Delta-Y. Good move.

    // 1/3 chance of dropping magic fangs of sleep upon death.
};


const int DRAGON_HP             = randInt(20, 25);
const int DRAGON_ARMOR          = 4;
const int DRAGON_STRENGTH       = 4;
const int DRAGON_DEXTERITY      = 4;
const int DRAGON_SLEEP_TIME     = 0;
//const int DRAGON_WEAPON         = LONG_SWORD;

class Dragon : public Monster
{
    //Spawns at level 3 or deeper.

    // Between 20 to 25 HP
    // 4 Armor, 4 Strength, 4 Dex.
    // Weapon: Long Sword
    
    Dragon(Dungeon* dungeon);
    ~Dragon();
    
    virtual void takeTurn();
    virtual void dropItem();

    // 1/10 chance of regaining 1 HP at start of turn.
    // 100% chance of dropping a scroll upon death.
};


//fuckin goblins.

const int GOBLIN_HP             = randInt(15, 20);
const int GOBLIN_ARMOR          = 1;
const int GOBLIN_STRENGTH       = 3;
const int GOBLIN_DEXTERITY      = 1;
const int GOBLIN_SLEEP_TIME     = 0;
//const int GOBLIN_WEAPON         = SHORT_SWORD;  No longer relevant, designed weapon class

class Goblin : public Monster
{
    // Spawn at all levels.

    // Between 15 to 20 HP.
    // 1 Armor
    // 3 Strength
    // 1 Dex
    // Weapon: Short Sword
    
    Goblin(Dungeon* dungeon);
    ~Goblin();
    
    virtual void takeTurn();
    virtual void dropItem();
    bool pathExists();
    
    

    //if Pathexists between goblin and player within 15 steps, can smell.
    //Makes optimal move.

    // 1/3 chance of dropping magic axe or fang of sleep on death.
};


#endif /* Actor_h */
