#include "Actor.h"
#include "Dungeon.h"
#include "Object.h"
#include "Game.h"

//All actors must have:
//Postion
//Health Points
//Armor
//Strength
//Dex
//Weapon
//SleepTime

#include <iostream>

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//--------------ACTOR CLASS-------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Constructor without speifying positon or health (for dragons)
Actor::Actor(int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
:m_armor(armor), m_strength(strength), m_dex(dex), m_weapon(weapon), m_sleepTime(sleepTime), m_dungeon(dungeon), m_name(name) { }

// Constructor without specifying position
Actor::Actor(int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
: m_hp(HP), m_maxHP(maxHP), m_armor(armor), m_strength(strength), m_dex(dex), m_weapon(weapon), m_sleepTime(sleepTime), m_dungeon(dungeon), m_name(name) { }

// Constructor specifying position
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

void Actor::clearLastPositionOnMap()
{
    m_dungeon->setChar(m_row, m_col, EMPTY);
}


void Actor::attack(Actor* attacker, Actor* defender)
{
    //Is hit successful?
    int atkPoint = attacker->getDex() + attacker->getWeapon()->getDex();
    int defPoint = defender->getDex() + defender->getWeapon()->getDex();
    
    if ( randInt(atkPoint) > randInt(defPoint) )        //Condition for successful hit
    {
        int damage = randInt(attacker->getStrength() + attacker->getWeapon()->getDmg() - 1);    //using damage formula.
        
        if (damage >= defender->getHP())    //Fatal blow.
        {
            Monster* montest = dynamic_cast<Monster*>(defender);       //attempt to convert defender ptr into monster ptr.
            if (montest != nullptr)
            {
                //TODO: Call drop function for loot.
                getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " dealing a final blow." );
            }
            Player* playtest = dynamic_cast<Player*>(defender);        //attempt to convert defend ptr into player ptr.
            if (playtest != nullptr)
            {
                getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + defender->getName() + " dealing a final blow." );
                getDungeon()->getTextList().push_back("press q to exit game.");
            }
                
        }
        
        else if (damage < defender->getHP())    //non-fatal attack.
        {
            if (attacker->getWeapon()->getName() != "magic fangs")
            {
                defender->reduceHP(damage);     //reduce defender hp
                getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits." );
                
            }
            
            else if (attacker->getWeapon()->getName() == "magic fangs" )        //Weapon is Magic Fangs of Sleep, sleep chance.
            {
                bool sleepChance = trueWithProbability(1.0/5.0);    //Successful sleep hit?
                
                if (!sleepChance) //nonsuccessful sleep hit (normal hit)
                {
                    defender->reduceHP(damage);     //reduce defender hp
                    getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits." );
                }
                
                if (sleepChance)        //Successful sleep hit
                {
                    int sleepDuration = randInt(2, 6);
                    
                    if (defender->getSleepTime() <= 0)  //Defender is awake when hit.
                    {
                        defender->addSleepTime(sleepDuration);      //add sleepTime.
                        defender->reduceHP(damage);                 //reduce defender hp
                        getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits, putting the" + defender->getName() + " to sleep." );
                        
                    }
                    else if (defender->getSleepTime() > 0)  //Defender is already asleep.
                    {
                        int deltaSleep = sleepDuration - defender->getSleepTime();
                        if (deltaSleep > 0)
                        {
                            defender->addSleepTime(deltaSleep);
                            defender->reduceHP(damage);                 //reduce defender hp
                            getDungeon()->getTextList().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits, putting the" + defender->getName() + " to sleep." );
                        }
                    }
                }
            }
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
//
const int PLAYER_HP             = 20;
const int PLAYER_MAX_HP         = 20;
const int PLAYER_ARMOR          = 2;
const int PLAYER_STRENGTH       = 2;
const int PLAYER_DEXTERITY      = 2;
const int PLAYER_SLEEP_TIME     = 0;

Player::Player(Dungeon* dungeon)
: Actor(PLAYER_HP, PLAYER_MAX_HP, PLAYER_ARMOR, PLAYER_STRENGTH, PLAYER_DEXTERITY, new ShortSword, PLAYER_SLEEP_TIME, dungeon, "Player")
//(int row, int col, int HP, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
{ }

Player::~Player()
{delete getWeapon();}

void Player::takeTurn()
{
    if (isDead()) {return;}             //Player cannot make any moves if it's dead.
    
    // Get the input move
    char move = getDungeon()->getCurrentMove();
    
    switch (move) {
        //Move Up
        case Game::MOVE_TYPE::UP:
            clearLastPositionOnMap();
            setPosition(getRowPos() - 1, getColPos());
            break;
            
        //Move Down
        case Game::MOVE_TYPE::DOWN:
            clearLastPositionOnMap();
            setPosition(getRowPos() + 1, getColPos());
            break;
            
        //Move Left
        case Game::MOVE_TYPE::LEFT:
            clearLastPositionOnMap();
            setPosition(getRowPos(), getColPos() - 1);
            break;
            
        //Move Right
        case Game::MOVE_TYPE::RIGHT:
            clearLastPositionOnMap();
            setPosition(getRowPos(), getColPos() + 1);
            break;
            
        default:
            break;
    }
}

//bool Player::standingOnObject()
//{
//    int playRow = getRowPos();
//    int playCol = getColPos();
//    list<Object*> objList = getDungeon()->getObjectList();
//
//    for (list<Object*>::iterator i = objList.begin() ; i != objList.end() ; i++)
//    {
//        int objRow = (*i)->getRow();
//        int objCol = (*i)->getCol();
//
//
//    }
//}


//TODO: pickup
//void Player::pickUp()                  //pick up and object you're standing on with 'g'
//{
//
//
//
//}

//TODO: THESE BOYS
//void weildWeapon(char ch);      //change weapons 'w'
//void readScroll(char ch);       //read scroll 'r'
//void openIventory();            //open inventory with 'i'
//void descend();                 //descend to lower level with '>'

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

Monster::Monster(int row, int col, int healthPoints, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
:Actor(row, col, healthPoints, maxHP, armor, strength, dex, weapon, sleepTime, dungeon, name) {}

Monster::Monster(int healthPoints, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
:Actor(healthPoints, maxHP, armor, strength, dex, weapon, sleepTime, dungeon, name) {}

Monster::Monster(int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
:Actor(armor, strength, dex, weapon, sleepTime, dungeon, name) {}

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


void Monster::dropItem(Dungeon* dungeon)
{
    string name = this->getName();
    
    if (name == "Bogeyman")
    {
        //When a bogeyman dies, there is a 1 in 10 chance it will drop a magic axe if there is no item at the position where it dies.
        bool itemDropped = trueWithProbability(1.0/10.0);
        
        if (itemDropped)
            dungeon->getObjectList().push_back(new MagicAxe(this->getRowPos(), this->getColPos()));
    }
    
    else if (name == "Snakewoman")
    {
        //When a snakewoman dies, there is a 1 in 3 chance she will drop her magic fangs of sleep if there is no item at the position where she dies.
        bool itemDropped = trueWithProbability(1.0/3.0);
        
        if (itemDropped)
            dungeon->getObjectList().push_back(new MagicFangs(this->getRowPos(), this->getColPos()));
    }
    
    else if (name == "Dragon")
    {
        //When a dragon dies, there is a 100% chance it will drop a scroll of some kind if there is no item at the position where it dies.
        int whichScroll = randInt(1, 5);
        
        switch (whichScroll) {
            case 1:
                dungeon->getObjectList().push_back(new HPScroll(this->getRowPos(), this->getColPos()));
                break;
            case 2:
                dungeon->getObjectList().push_back(new ArmorScroll(this->getRowPos(), this->getColPos()));
                break;
            case 3:
                dungeon->getObjectList().push_back(new StrengthScroll(this->getRowPos(), this->getColPos()));
                break;
            case 4:
                dungeon->getObjectList().push_back(new DexScroll(this->getRowPos(), this->getColPos()));
                break;
            case 5:
                dungeon->getObjectList().push_back(new TPScroll(this->getRowPos(), this->getColPos()));
                break;
            default:
                break;
        }
    }
    
    else if (name == "Goblin")
    {
        //When a goblin dies, there is a 1 in 3 chance it will drop either a magic axe or magic fangs of sleep if there is no item at the position where it dies.
        bool itemDropped = trueWithProbability(1.0/3.0);
        bool whichItem = trueWithProbability(1.0/2.0);      //if true, drop axes. if false, drop fangs.
        
        if (itemDropped && whichItem)
            dungeon->getObjectList().push_back(new MagicAxe(this->getRowPos(), this->getColPos()));
        
        else if (itemDropped && !whichItem)
            dungeon->getObjectList().push_back(new MagicFangs(this->getRowPos(), this->getColPos()));
    }
}


char Monster::chasePlayer(Player* player, Dungeon* dungeon)
{
    int monRow = getRowPos();
    int monCol = getColPos();
    int playerRow = player->getRowPos();
    int playerCol = player->getColPos();

    int deltaRow = abs(monRow - playerRow);
    int deltaCol = abs(monCol - playerCol);

    int curDist = deltaRow + deltaCol;      //how far is the monster from player currently?

    // Check moving right
    if (abs(monRow + 1 - playerRow) + deltaCol < curDist && getDungeon()->actorPosValid(monRow + 1, monCol))
    {
        return Game::MOVE_TYPE::RIGHT;
    }
    // Check moving left
    else if (abs(monRow - 1 - playerRow) + deltaCol < curDist && getDungeon()->actorPosValid(monRow - 1, monCol))
    {
        return Game::MOVE_TYPE::LEFT;
    }
    // Check moving up
    else if (deltaRow + abs(monCol - 1 - playerCol) < curDist && getDungeon()->actorPosValid(monRow, monCol - 1))
    {
        return Game::MOVE_TYPE::UP;
    }
    // Check moving down
    else if (deltaRow + abs(monCol + 1 - playerCol) < curDist  && getDungeon()->actorPosValid(monRow , monCol + 2))
    {
        return Game::MOVE_TYPE::DOWN;
    }
    
    return ' ';
}




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------SNAKEWOMEN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int SNAKE_HP             = randInt(3, 6);
const int SNAKE_ARMOR          = 3;
const int SNAKE_STRENGTH       = 2;
const int SNAKE_DEXTERITY      = 3;
const int SNAKE_SLEEP_TIME     = 0;
// Weapon: Magic Fangs of Sleep

Snakewoman::Snakewoman(Dungeon* dungeon)
:Monster(randInt(3, 6), 6, SNAKE_ARMOR, SNAKE_STRENGTH, SNAKE_DEXTERITY, new MagicFangs, SNAKE_SLEEP_TIME, dungeon, "Snakewoman")
{}

Snakewoman::~Snakewoman()
{
    delete getWeapon();
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------BOGEYMEN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int BOGEY_HP             = randInt(5, 10);
const int BOGEY_ARMOR          = 2;
const int BOGEY_STRENGTH       = randInt(2, 3);
const int BOGEY_DEXTERITY      = randInt(2, 3);
const int BOGEY_SLEEP_TIME     = 0;
//Weapon ShortSword

Bogeyman::Bogeyman(Dungeon* dungeon)
:Monster(randInt(5, 10), 10, BOGEY_ARMOR, BOGEY_STRENGTH, BOGEY_DEXTERITY, new ShortSword, BOGEY_SLEEP_TIME, dungeon, "Bogeyman")
{}

Bogeyman::~Bogeyman()
{
    delete getWeapon();
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------DRAGONS------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int DRAGON_HP             = randInt(20, 25);
const int DRAGON_ARMOR          = 4;
const int DRAGON_STRENGTH       = 4;
const int DRAGON_DEXTERITY      = 4;
const int DRAGON_SLEEP_TIME     = 0;
//const int DRAGON_WEAPON         = LONG_SWORD;

Dragon::Dragon(Dungeon* dungeon)
:Monster(DRAGON_ARMOR, DRAGON_STRENGTH, DRAGON_DEXTERITY, new LongSword, DRAGON_SLEEP_TIME, dungeon, "Dragon")
{
    setHP(randInt(20, 25));
    setMaxHP(getHP());
}

Dragon::~Dragon()
{
    delete getWeapon();
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------GOBLIN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


const int GOBLIN_HP             = randInt(15, 20);
const int GOBLIN_ARMOR          = 1;
const int GOBLIN_STRENGTH       = 3;
const int GOBLIN_DEXTERITY      = 1;
const int GOBLIN_SLEEP_TIME     = 0;
//const int GOBLIN_WEAPON         = SHORT_SWORD;  No longer relevant, designed weapon class

Goblin::Goblin(Dungeon* dungeon)
:Monster(randInt(15, 20), 20, GOBLIN_ARMOR, GOBLIN_STRENGTH, GOBLIN_DEXTERITY, new ShortSword, GOBLIN_SLEEP_TIME, dungeon, "Gobin")
{}

Goblin::~Goblin()
{
    delete getWeapon();
}
