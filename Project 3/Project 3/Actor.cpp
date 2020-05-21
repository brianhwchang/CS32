#include "Actor.h"
#include "Dungeon.h"
#include "Object.h"

//All actors must have:
//Postion
//Health Points
//Armor
//Strength
//Dex
//Weapon
//SleepTime

#include <iostream>

Actor::Actor(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
: m_row(row), m_col(col), m_hp(HP), m_maxHP(maxHP), m_armor(armor), m_strength(strength), m_dex(dex), m_weapon(weapon), m_sleepTime(sleepTime), m_dungeon(dungeon), m_name(name) { }

Actor::~Actor() {delete m_weapon;}

void Actor::addHP(int amt)
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

void Actor::attack(Actor* attacker, Actor* defender)
{
    //Is hit successful?
    int atkPoint = attacker->getDex() + attacker->getWeapon()->getDex();
    int defPoint = defender->getDex() + defender->getWeapon()->getDex();
    
    if ( randInt(atkPoint) > randInt(defPoint) )        //Condition for successful hit
    {
        int damage = randInt(attacker->getStrength() + attacker->getWeapon()->getDmg() - 1);    //using damage formula.
        
        if (damage < defender->getHP()) //Successful hit, but non-fatal.
        {
            if (attacker->getWeapon() != MagicFangs)
        }
        
        
    }
    
    else //Miss.
    {
        // "the *attacker* *action* *weapon* at the *defender* and misses"
        getDungeon()->getTextList().push_back( "the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + "at the " + defender->getName() + "and misses." );
    }
        
    
    
}















//Status Checkers

bool Actor::isDead()
{
    if (m_hp <= 0)
        return true;
    else
        return false;
}

bool Actor::isAsleep()
{
    if (m_sleepTime > 0)
        return true;
    else
        return false;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//--------------PLAYER CLASS-------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int PLAYER_HP             = 20;
const int PLAYER_MAX_HP         = 20;
const int PLAYER_ARMOR          = 2;
const int PLAYER_STRENGTH       = 2;
const int PLAYER_DEXTERITY      = 2;
const int PLAYER_SLEEP_TIME     = 0;

//(int row, int col, int healthPoints, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string species)

Player::Player(Dungeon* dungeon)
: Actor(69, 69, PLAYER_HP, PLAYER_MAX_HP, PLAYER_ARMOR, PLAYER_STRENGTH, PLAYER_DEXTERITY, ShortSword, PLAYER_SLEEP_TIME, dungeon, "Player")
//(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
{ }

Player::~Player()
{ }

void Player::takeTurn()
{
    if (isDead()) {return;}             //Player cannot make any moves if it's dead.
    
    char move = getDungeon()->getCurrentMove();
    std::cout << "HERE\n";
    std::cout << move << std::endl;
    
    switch (move) {
            //Move Up
        case 'k':
            std::cout << "moved up in player\n";
            setPosition(getRowPos() - 1, getColPos());
            break;
            
            //Move Down
        case 'j':
            std::cout << "moved down in player\n";
            setPosition(getRowPos() + 1, getColPos());
            break;
            
            //Move Left
        case 'h':
            std::cout << "moved left in player\n";
            setPosition(getRowPos(), getColPos() - 1);

            //Move Right
        case 'l':
            std::cout << "moved right in player\n";
            setPosition(getRowPos(), getColPos() + 1);

        default:
            break;
    }
}


//Cheat fxn for testing. HP = 50, STR = 9.
void Player::cheat()
{
    addMaxHP(50 - getMaxHP());
    addHP(50 - getHP());
    addStrength(9 - getStrength());
}





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------.MONSTARS. S/0 LEBRON JAMES THE GOAT------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bool Monster::CanSmellPlayer(Dungeon* dungeon, int ReqDist)
{
    //Get Monster and Player positions
    int MonRow = getRowPos();
    int MonCol = getRowPos();
    int PlayRow = dungeon->getPlayer()->getRowPos();
    int PlayCol = dungeon->getPlayer()->getRowPos();
    
    //Find the distance between them in spaces
    int deltaRow = abs(MonRow-PlayRow);
    int deltaCol = abs(MonCol-PlayCol);
    int NumMovesNeeded = deltaRow + deltaCol;
    
    if (NumMovesNeeded <= ReqDist)
        return true;
    else
        return false;
}
