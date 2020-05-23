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
    Actor(int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    Actor(int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    Actor(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    virtual ~Actor();
    
    
    virtual void takeTurn() = 0;            //pure virtual function, such that Actor is an abstract base class.
    void attack(Actor* attacker, Actor* defender);
    //TODO: Move/Take turn
    
    //Setter Functions
    void setHP(int amt) {m_hp = amt;}
    void setMaxHP (int amt) {m_maxHP = amt;}
    void setPosition(int r, int c) { m_row = r; m_col = c; }
    void setWeapon(Weapon* weapon);
    
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
    
    // Misc Setters
    // Sets the last space of an actor to SPACE. Would be called before
    // updating an actors m_row/m_col attributes to clear it's dungeon's grid
    void clearLastPositionOnMap();
    
    //Misc Getters
    string getName() {return m_name;}
    Dungeon* getDungeon() { return m_dungeon;}
    Weapon* getWeapon() { return m_weapon;}
    bool isDead();
    bool isAsleep();

    
private:
    int m_row;                          // Current row
    int m_col;                          // Current column
    int m_hp;                           // Current HP
    int m_maxHP;                        // Maximum HP
    int m_armor;                        // Armor
    int m_strength;                     // Strength
    int m_dex;                          // Dexterity
    int m_sleepTime;                    // Sleep time
    string m_name;                      // String representation of actor type
    Weapon* m_weapon;                   // Pointer to a weapon
    Dungeon* m_dungeon;                 // Dungeon this actor is in
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
    bool standingOnObject();
    
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
    Monster(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    
    Monster(int healthPoints, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    
    Monster(int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name);
    virtual ~Monster() {};
    
    virtual void takeTurn() {};
    
    void dropItem(Dungeon* dungeon);
    bool CanSmellPlayer(Dungeon* dungeon, int ReqDist);                     //Used by Bogeymen and Snakewomen.
    void chasePlayer(Player* player, Dungeon* dungeon);   //Used by Bogeymen and Snakewomen.
};


class Bogeyman : public Monster
{
    //only spawn at level 2 or deeper.
public:
    Bogeyman(Dungeon* dungeon);
    ~Bogeyman();

    virtual void takeTurn();
    
    //if there are 5 or fewer spaces between the player and BG, the bg can smell the player
    //If the BG smells the player, it'll move closer.
    //Doesnt care about pathfinding, just wants to be as close as possible
        //could impletement like judge closeness by BG_xcoord - Player_xcoord, or BG_ycoord - Player_ycoord
        //as long as the difference between the coordintates decreases, its a "good" move for the BG

    // 1/10 chance of dropping magic axe upon death.
};


class Snakewoman : public Monster
{
    //Spawn at all levels.
public:
    Snakewoman(Dungeon* dungeon);
    ~Snakewoman();
    
    virtual void takeTurn();
//    virtual void dropItem();

    //if it can reach the player in 3 or fewer moves, it can smell player. (bool - Can smell player (SW coord, Player Coord, max dist)
        // can smell if (Delta X + Delta Y <= 3)
                //return true
    //if it can smell player move towards
        // if post-move delta X or delta Y is less than pre-move Delta-X or Delta-Y. Good move.

    // 1/3 chance of dropping magic fangs of sleep upon death.
};


class Dragon : public Monster
{
    //Spawns at level 3 or deeper.

    // Between 20 to 25 HP
    // 4 Armor, 4 Strength, 4 Dex.
    // Weapon: Long Sword
public:
    Dragon(Dungeon* dungeon);
    ~Dragon();
    
//    virtual void takeTurn();
//    virtual void dropItem();

    // 1/10 chance of regaining 1 HP at start of turn.
    // 100% chance of dropping a scroll upon death.
};


//fuckin goblins.
class Goblin : public Monster
{
    // Spawn at all levels.

    // Between 15 to 20 HP.
    // 1 Armor
    // 3 Strength
    // 1 Dex
    // Weapon: Short Sword
public:
    Goblin(Dungeon* dungeon);
    ~Goblin();
    
//    virtual void takeTurn();
//    virtual void dropItem();
//    bool pathExists();
    
    

    //if Pathexists between goblin and player within 15 steps, can smell.
    //Makes optimal move.

    // 1/3 chance of dropping magic axe or fang of sleep on death.
};


#endif /* Actor_h */
