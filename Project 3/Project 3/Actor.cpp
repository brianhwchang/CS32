#include "Actor.h"

//All actors must have:
//Postion
//Health Points
//Armor
//Strength
//Dex
//Weapon
//SleepTime

#include <iostream>

Actor::Actor(int row, int col, int healthPoints, int armor, int strength, int dex, int weapon, int sleepTime, Dungeon* dungeon)
: m_row(row), m_col(col), m_hp(healthPoints), m_armor(armor), m_strength(strength), m_dex(dex), m_weapon(weapon), m_sleepTime(sleepTime), m_dungeon(dungeon)
{ }

Actor::~Actor()
{ }

bool Actor::isDead()
{
    if (m_hp <= 0)
        return true;
    else
        return false;
}


Player::Player(Dungeon* dungeon)
: Actor(15, 15, PLAYER_HP, PLAYER_ARMOR, PLAYER_STRENGTH, PLAYER_DEXTERITY, PLAYER_WEAPON, PLAYER_SLEEP_TIME, dungeon)
{ }

Player::~Player()
{ }

void Player::makeMove()
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
