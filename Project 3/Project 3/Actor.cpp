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



//Player strikes magic fangs at the Goblin and hits, putting the Goblin to sleep.











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
: Actor(69, 69, PLAYER_HP, PLAYER_MAX_HP, PLAYER_ARMOR, PLAYER_STRENGTH, PLAYER_DEXTERITY, new ShortSword, PLAYER_SLEEP_TIME, dungeon, "Player")
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

void Player::pickUp()                  //pick up and object you're standing on with 'g'
{
    
    
    
}


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


void Monster::dropItem(Monster* monster, Dungeon* dungeon)
{
    string name = monster->getName();
    
    if (name == "Bogeyman")
    {
        //When a bogeyman dies, there is a 1 in 10 chance it will drop a magic axe if there is no item at the position where it dies.
        bool itemDropped = trueWithProbability(1.0/10.0);
        
        if (itemDropped)
            dungeon->getObjectList().push_back(new MagicAxe(monster->getRowPos(), monster->getColPos()));
    }
    
    else if (name == "Snakewoman")
    {
        //When a snakewoman dies, there is a 1 in 3 chance she will drop her magic fangs of sleep if there is no item at the position where she dies.
        bool itemDropped = trueWithProbability(1.0/3.0);
        
        if (itemDropped)
            dungeon->getObjectList().push_back(new MagicFangs(monster->getRowPos(), monster->getColPos()));
    }
    
    else if (name == "Dragon")
    {
        //When a dragon dies, there is a 100% chance it will drop a scroll of some kind if there is no item at the position where it dies.
        int whichScroll = randInt(1, 5);
        
        switch (whichScroll) {
            case 1:
                dungeon->getObjectList().push_back(new HPScroll(monster->getRowPos(), monster->getColPos()));
                break;
            case 2:
                dungeon->getObjectList().push_back(new ArmorScroll(monster->getRowPos(), monster->getColPos()));
                break;
            case 3:
                dungeon->getObjectList().push_back(new StrengthScroll(monster->getRowPos(), monster->getColPos()));
                break;
            case 4:
                dungeon->getObjectList().push_back(new DexScroll(monster->getRowPos(), monster->getColPos()));
                break;
            case 5:
                dungeon->getObjectList().push_back(new TPScroll(monster->getRowPos(), monster->getColPos()));
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
            dungeon->getObjectList().push_back(new MagicAxe(monster->getRowPos(), monster->getColPos()));
        
        else if (itemDropped && !whichItem)
            dungeon->getObjectList().push_back(new MagicFangs(monster->getRowPos(), monster->getColPos()));
    }
}

//char ChasePlayer(Monster* monster, Player* player, Dungeon* dungeon)
//{
//    int monRow = monster->getRowPos();
//    int monCol = monster->getColPos();
//    int playRow = player->getRowPos();
//    int playCol = player->getColPos();
//
//    int deltaRow = abs(monRow - playRow);
//    int deltaCol = abs(monCol - playCol);
//
//    int curDist = deltaRow + deltaCol;      //how far is the monster from player currently?
//
//    char move = '';     //no move
//
//    if (curDist = 1)    //monster is on an adjacent square to player.
//        return move;    //return no move.
//
//
//
//}

//Monster::Monster(int row, int col, int healthPoints, int maxHP, int armor, int strength, int dex, Weapon* weapon, int sleepTime, Dungeon* dungeon, string name)
//:Actor(row, col, healthPoints, maxHP, armor, strength, dex, weapon, sleepTime, dungeon, name) {}

