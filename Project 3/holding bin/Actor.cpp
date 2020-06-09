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

Actor::~Actor()
{ }



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

void Actor::randomRegen()
{
    bool feelingLucky = trueWithProbability(1.0/10.0);
    if (feelingLucky)
    {
        addHP(1);
        return;
    }
    else
        return;
}

void Actor::attack(Actor* attacker, Actor* defender)
{
    if (attacker == nullptr)
    {
        cout << "attacker is nullptr" << endl;
        return;
    }
    
    if (defender == nullptr)
    {
        cout << "defender is nullptr" << endl;
        return;
    }
    
    //Is hit successful?
    int atkPoint = attacker->getDex() + attacker->getWeapon()->getDex();
    int defPoint = defender->getDex() + defender->getWeapon()->getDex();
    
    if ( randInt(atkPoint) >= randInt(defPoint) )        //Condition for successful hit
    {
        int damage = randInt(attacker->getStrength() + attacker->getWeapon()->getDmg() - 1);    //using damage formula.
        
        if (damage >= defender->getHP())    //Fatal blow.
        {
            Monster* montest = dynamic_cast<Monster*>(defender);       //attempt to convert defender ptr into monster ptr.
            if (montest != nullptr)
            {
                defender->reduceHP(damage);     //reduce defender hp
                montest->dropItem(attacker->getDungeon());      //attacker would be the player.
                getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " dealing a final blow." );
            }
            Player* playtest = dynamic_cast<Player*>(defender);        //attempt to convert defend ptr into player ptr.
            if (playtest != nullptr)
            {
                defender->reduceHP(damage);     //reduce defender hp
                getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + defender->getName() + " dealing a final blow." );
                getDungeon()->getTextVector().push_back("press q to exit game.");
            }
                
        }
        
        else if (damage < defender->getHP())    //non-fatal attack.
        {
            if (attacker->getWeapon()->getName() != "magic fangs")
            {
                defender->reduceHP(damage);     //reduce defender hp
                getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits." );
                
            }
            
            else if (attacker->getWeapon()->getName() == "magic fangs" )        //Weapon is Magic Fangs of Sleep, sleep chance.
            {
                bool sleepChance = trueWithProbability(1.0/5.0);    //Successful sleep hit?
                
                if (!sleepChance) //nonsuccessful sleep hit (normal hit)
                {
                    defender->reduceHP(damage);     //reduce defender hp
                    getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits." );
                }
                
                if (sleepChance)        //Successful sleep hit
                {
                    int sleepDuration = randInt(2, 6);
                    
                    if (defender->getSleepTime() <= 0)  //Defender is awake when hit.
                    {
                        defender->addSleepTime(sleepDuration);      //add sleepTime.
                        defender->reduceHP(damage);                 //reduce defender hp
                        getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits, putting the " + defender->getName() + " to sleep." );
                        
                    }
                    else if (defender->getSleepTime() > 0)  //Defender is already asleep.
                    {
                        int deltaSleep = sleepDuration - defender->getSleepTime();
                        if (deltaSleep > 0)
                        {
                            defender->addSleepTime(deltaSleep);
                            defender->reduceHP(damage);                 //reduce defender hp
                            getDungeon()->getTextVector().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and hits, putting the " + defender->getName() + " to sleep." );
                        }
                    }
                }
            }
        }
    }

    else //Miss.
    {
        // "the *attacker* *action* *weapon* at the *defender* and misses"
        getDungeon()->getTextVector().push_back( "the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at the " + defender->getName() + " and misses." );
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
{
    win = false;
}

Player::~Player()
{
    if (getWeapon() != nullptr) {
        delete getWeapon();
    }
}

void Player::takeTurn()
{
    if (isDead()) {return;}             // Player cannot make any moves if it's dead.
    
    randomRegen();                      //10% HP regen chance function.
    
    if (isAsleep())
    {
        reduceSleepTime(1);
        return;
    }
    
    // Get the input move
    char move = getDungeon()->getCurrentMove();
    
    switch (move) {
        //Move Up
        case Game::MOVE_TYPE::UP:
            if (getDungeon()->isMob(getRowPos() -1 , getColPos()))      // If monster, attack it.
            {
                Monster* mob = nullptr;
                getDungeon()->getMob(getRowPos() -1 , getColPos(), mob);
                attack(this, mob);
            }
            else if (getDungeon()->actorPosValid(getRowPos() - 1, getColPos()))     // If not monster, just move (if valid)
            {
                clearLastPositionOnMap();
                setPosition(getRowPos() - 1, getColPos());
            }
            break;
            
        //Move Down
        case Game::MOVE_TYPE::DOWN:
            if (getDungeon()->isMob(getRowPos() +1 , getColPos()))      // If monster, attack it.
            {
                Monster* mob = nullptr;
                getDungeon()->getMob(getRowPos() +1 , getColPos(), mob);
                attack(this, mob);
            }
            else if (getDungeon()->actorPosValid(getRowPos() + 1, getColPos()))     // If not monster, just move (if valid)
            {
                clearLastPositionOnMap();
                setPosition(getRowPos() + 1, getColPos());
            }
            break;
            
        //Move Left
        case Game::MOVE_TYPE::LEFT:
            if (getDungeon()->isMob(getRowPos(), getColPos() - 1))      // If monster, attack it.
            {
                Monster* mob = nullptr;
                getDungeon()->getMob(getRowPos(), getColPos() - 1, mob);
                attack(this, mob);
            }
            else if (getDungeon()->actorPosValid(getRowPos(), getColPos() - 1))
            {
                clearLastPositionOnMap();
                setPosition(getRowPos(), getColPos() - 1);
            }
            break;
            
        //Move Right
        case Game::MOVE_TYPE::RIGHT:
            if (getDungeon()->isMob(getRowPos(), getColPos() + 1))      // If monster, attack it.
            {
                Monster* mob = nullptr;
                getDungeon()->getMob(getRowPos(), getColPos() + 1, mob);
                attack(this, mob);
            }
            else if (getDungeon()->actorPosValid(getRowPos(), getColPos() + 1))
            {
                clearLastPositionOnMap();
                setPosition(getRowPos(), getColPos() + 1);
            }
            break;
            
        default:
            break;
    }
}


bool Player::standingOnObject()
{
    int playRow = this->getRowPos();
    int playCol = this->getColPos();
    
    Object* targetItem = nullptr;
    getDungeon()->getObj(playRow, playCol, targetItem);     //will return a valid pointer to the object if its valid.
    
    if (targetItem != nullptr)
        return true;
    else
        return false;
}



void Player::pickUp()                  //pick up and object you're standing on with 'g'
{
    int playRow = this->getRowPos();
    int playCol = this->getColPos();
    
    if (getDungeon()->getLevel() == 4)
    {
        if (getDungeon()->isIdol(playRow, playCol))
        {
            //Winning condition.
            winGame();
            return;
        }
    }
    
    if (standingOnObject())
    {
        if (inventory.size() >= 25)
        {
            cout << "Your knapsack is full; you can't pick that up." << endl;
            return;
        }
        
        Object* targetItem = nullptr;
        getDungeon()->getObj(playRow, playCol, targetItem);         //get object
        inventory.push_back(targetItem);                            //store object
        
        Weapon* weaponTest = dynamic_cast<Weapon*>(targetItem);
        if (weaponTest != nullptr)
            getDungeon()->getTextVector().push_back("You pick up a " + targetItem->getName());
        else
            getDungeon()->getTextVector().push_back("You pick up a scroll called " + targetItem->getName());
        
        getDungeon()->eraseObject(targetItem);
    }
    else
        return;
}

//TODO: THESE BOYS
void Player::wieldWeapon(char ch)              //change weapons 'w'
{
    char index = 'a';
    for (vector<Object*>::iterator obj = inventory.begin(); obj != inventory.end(); obj++, index++)
    {
        // If the index matches character input
        if (index == ch)
        {
            // ...and if it's a weapon
            Weapon* testWeapon = dynamic_cast<Weapon*>(*obj);
            if (testWeapon != nullptr)
            {
                Weapon* lastWeapon = getWeapon();
                inventory.push_back(lastWeapon);
                setWeapon(testWeapon);
                // Erase from inventory
                cout << "You are wielding " << testWeapon->getName() << "." << endl;
                for (vector<Object*>::iterator obj = inventory.begin(); obj != inventory.end(); obj++, index++)
                {
                    if ((*obj) == testWeapon)
                    {
                        inventory.erase(obj);
                        return;
                    }
                }
                
                return;
                
            }
            else
                
            {
                cout << "You can't wield " << (*obj)->getName() << "." << endl;
            }
        }
    }
}

void Player::readScroll(char ch)       //read scroll 'r'
{
    char index = 'a';
    for (vector<Object*>::iterator obj = inventory.begin(); obj != inventory.end(); obj++, index++)
    {
        // If the index matches character input
        if (index == ch)
        {
            // ...and if it's a scroll
            Scroll* testScroll = dynamic_cast<Scroll*>(*obj);
            if (testScroll != nullptr)
            {
                int type = testScroll->getType();
                switch (type) {
                    // Increase max hp by random integer between 3 and 8
                    case HP_SCROLL:
                        setMaxHP(getMaxHP() + randInt(3, 8));
                        break;
                    // The player's armor points are increased by a random integer from 1 to 3.
                    case ARMOR_SCROLL:
                        addArmor(randInt(1, 3));
                        break;
                    // The player's strength points are increased by a random integer from 1 to 3.
                    case STRENGTH_SCROLL:
                        addStrength(randInt(1, 3));
                        break;
                    // The player's dexterity is increased by 1.
                    case DEX_SCROLL:
                        addDex(1);
                        break;
                    case TP_SCROLL:
                        getDungeon()->spawnPlayer();
                        break;
                    default:
                        break;
                }
                cout << "You read the scroll called " << testScroll->getName() << ". " << testScroll->getAction() << endl;
                // Erase from inventory
                for (vector<Object*>::iterator obj = inventory.begin(); obj != inventory.end(); obj++, index++)
                {
                    if ((*obj) == testScroll)
                    {
                        inventory.erase(obj);
                        return;
                    }
                }
            }
            else
            {
                cout << "You can't read a " << (*obj)->getName() << "." << endl;
            }
        }
    }
}

void Player::openIventory()
{
    if(isDead())
        return;
    
    clearScreen();
    char index = 'a';
    cout << "Inventory:" << endl;
    for (vector<Object*>::iterator obj = inventory.begin(); obj != inventory.end(); obj++, index++)
        cout << index << ". " + (*obj)->getName() << endl;
    
}

//void descend();                 //descend to lower level with '>'
    //Check if player is standing on '>'
    //Call nextLevel();
void Player::descend()
{
    if (getDungeon()->isStairs(this->getRowPos(), getColPos()))
        getDungeon()->nextLevel();
    else
        return;
}



//Cheat fxn for testing. HP = 50, STR = 9.
void Player::cheat()
{
    //Just add the difference
    addMaxHP(50 - getMaxHP());
    addHP(50 - getHP());
    addStrength(9 - getStrength());
}

void Player::winGame()
{
    win = true;
    cout << "You pick up the golden idol" << endl;
    cout << "Congratulations, you won!" << endl;
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
    int MonCol = getColPos();
    int PlayRow = dungeon->getPlayer()->getRowPos();
    int PlayCol = dungeon->getPlayer()->getColPos();
    
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
    
    if (name == BOGEYMAN)
    {
        //When a bogeyman dies, there is a 1 in 10 chance it will drop a magic axe if there is no item at the position where it dies.
        bool itemDropped = trueWithProbability(1.0/10.0);
        
        if (itemDropped)
            dungeon->getObjectVector().push_back(new MagicAxe(this->getRowPos(), this->getColPos()));
    }
    
    else if (name == SNAKEWOMAN)
    {
        //When a snakewoman dies, there is a 1 in 3 chance she will drop her magic fangs of sleep if there is no item at the position where she dies.
        bool itemDropped = trueWithProbability(1.0/3.0);
        
        if (itemDropped)
            dungeon->getObjectVector().push_back(new MagicFangs(this->getRowPos(), this->getColPos()));
    }
    
    else if (name == DRAGON)
    {
        //When a dragon dies, there is a 100% chance it will drop a scroll of some kind if there is no item at the position where it dies.
        int whichScroll = randInt(1, 5);
        
        switch (whichScroll) {
            case 1:
                dungeon->getObjectVector().push_back(new HPScroll(this->getRowPos(), this->getColPos()));
                break;
            case 2:
                dungeon->getObjectVector().push_back(new ArmorScroll(this->getRowPos(), this->getColPos()));
                break;
            case 3:
                dungeon->getObjectVector().push_back(new StrengthScroll(this->getRowPos(), this->getColPos()));
                break;
            case 4:
                dungeon->getObjectVector().push_back(new DexScroll(this->getRowPos(), this->getColPos()));
                break;
            case 5:
                dungeon->getObjectVector().push_back(new TPScroll(this->getRowPos(), this->getColPos()));
                break;
            default:
                break;
        }
    }
    
    else if (name == GOBLIN)
    {
        //When a goblin dies, there is a 1 in 3 chance it will drop either a magic axe or magic fangs of sleep if there is no item at the position where it dies.
        bool itemDropped = trueWithProbability(1.0/3.0);
        bool whichItem = trueWithProbability(1.0/2.0);      //if true, drop axes. if false, drop fangs.
        
        if (itemDropped && whichItem)
            dungeon->getObjectVector().push_back(new MagicAxe(this->getRowPos(), this->getColPos()));
        
        else if (itemDropped && !whichItem)
            dungeon->getObjectVector().push_back(new MagicFangs(this->getRowPos(), this->getColPos()));
    }
}


void Monster::chasePlayer(Player* player, Dungeon* dungeon)
{
    int monRow = getRowPos();
    int monCol = getColPos();
    int playerRow = player->getRowPos();
    int playerCol = player->getColPos();

    int deltaRow = abs(monRow - playerRow);
    int deltaCol = abs(monCol - playerCol);

    int curDist = deltaRow + deltaCol;      //how far is the monster from player currently?

    // Check moving down
    if (abs(monRow + 1 - playerRow) + deltaCol < curDist
        && getDungeon()->actorPosValid(monRow + 1, monCol)
        && !(monRow + 1 == playerRow && monCol == playerCol))
    {
        clearLastPositionOnMap();
        setPosition(monRow + 1, monCol);
    }
    // Check moving up
    else if (abs(monRow - 1 - playerRow) + deltaCol < curDist
             && getDungeon()->actorPosValid(monRow - 1, monCol)
             && !(monRow - 1 == playerRow && monCol == playerCol))
    {
        clearLastPositionOnMap();
        setPosition(monRow - 1, monCol);
    }
    // Check moving left
    else if (deltaRow + abs(monCol - 1 - playerCol) < curDist
             && getDungeon()->actorPosValid(monRow, monCol - 1)
             && !(monRow == playerRow && monCol - 1 == playerCol))
    {
        clearLastPositionOnMap();
        setPosition(monRow, monCol - 1);
    }
    // Check moving right
    else if (deltaRow + abs(monCol + 1 - playerCol) < curDist
             && getDungeon()->actorPosValid(monRow , monCol + 1)
             && !(monRow == playerRow && monCol + 1 == playerCol))
    {
        clearLastPositionOnMap();
        setPosition(monRow, monCol + 1);
    }
}

bool Monster::isNextToPlayer()
{
    int monRow = this->getRowPos();
    int monCol = this->getColPos();
    
    // Check up
    if (getDungeon()->isPlayer(monRow - 1, monCol))
        return true;
    // Check down
    else if (getDungeon()->isPlayer(monRow + 1, monCol))
        return true;
    // Check left
    else if (getDungeon()->isPlayer(monRow, monCol - 1))
        return true;
    // Check right
    else if (getDungeon()->isPlayer(monRow, monCol + 1))
        return true;
    else
        return false;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------SNAKEWOMEN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int SNAKE_HP             = randInt(3, 6);
const int SNAKE_ARMOR          = 3;
const int SNAKE_STRENGTH       = 2;
const int SNAKE_DEXTERITY      = 3;
const int SNAKE_SLEEP_TIME     = 0;
const int SNAKE_SMELL_DISTANCE = 3;
// Weapon: Magic Fangs of Sleep

Snakewoman::Snakewoman(Dungeon* dungeon)
:Monster(randInt(3, 6), 6, SNAKE_ARMOR, SNAKE_STRENGTH, SNAKE_DEXTERITY, new MagicFangs, SNAKE_SLEEP_TIME, dungeon, SNAKEWOMAN)
{}

Snakewoman::~Snakewoman()
{
    // If snakewoman dies there is a 1/3 chance of dropping fangs
    // at position where dies
    
    if (getWeapon() != nullptr)
    {
       delete getWeapon();
   }
}

void Snakewoman::takeTurn()
{
    if (isNextToPlayer())
    {
        attack(this, getDungeon()->getPlayer());
    }
    if (CanSmellPlayer(getDungeon(), SNAKE_SMELL_DISTANCE))
    {
        chasePlayer(getDungeon()->getPlayer(), getDungeon());
    }
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------BOGEYMEN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

const int BOGEY_HP             = randInt(5, 10);
const int BOGEY_ARMOR          = 2;
const int BOGEY_STRENGTH       = randInt(2, 3);
const int BOGEY_DEXTERITY      = randInt(2, 3);
const int BOGEY_SLEEP_TIME     = 0;
const int BOGEY_SMELL_DISTANCE = 5;

//Weapon ShortSword

Bogeyman::Bogeyman(Dungeon* dungeon)
:Monster(randInt(5, 10), 10, BOGEY_ARMOR, BOGEY_STRENGTH, BOGEY_DEXTERITY, new ShortSword, BOGEY_SLEEP_TIME, dungeon, BOGEYMAN)
{}

Bogeyman::~Bogeyman()
{
    if (getWeapon() != nullptr)
    {
        delete getWeapon();
    }
}

void Bogeyman::takeTurn()
{
    if (isNextToPlayer())
    {
        attack(this, getDungeon()->getPlayer());
    }
    else if (CanSmellPlayer(getDungeon(), BOGEY_SMELL_DISTANCE))
    {
        chasePlayer(getDungeon()->getPlayer(), getDungeon());
    }
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
:Monster(DRAGON_ARMOR, DRAGON_STRENGTH, DRAGON_DEXTERITY, new LongSword, DRAGON_SLEEP_TIME, dungeon, DRAGON)
{
    setHP(randInt(20, 25));
    setMaxHP(getHP());
}

Dragon::~Dragon()
{
    if (getWeapon() != nullptr)
    {
        delete getWeapon();
    }
}

void Dragon::takeTurn()
{
    randomRegen();
    if (isNextToPlayer())
    {
        attack(this, getDungeon()->getPlayer());
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------GOBLIN------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


const int GOBLIN_HP             = randInt(15, 20);
const int GOBLIN_ARMOR          = 1;
const int GOBLIN_STRENGTH       = 3;
const int GOBLIN_DEXTERITY      = 1;
const int GOBLIN_SLEEP_TIME     = 0;
const int GOBLIN_SMELL_DISTANCE = 15;
//const int GOBLIN_WEAPON         = SHORT_SWORD;  No longer relevant, designed weapon class

Goblin::Goblin(Dungeon* dungeon)
:Monster(randInt(15, 20), 20, GOBLIN_ARMOR, GOBLIN_STRENGTH, GOBLIN_DEXTERITY, new ShortSword, GOBLIN_SLEEP_TIME, dungeon, GOBLIN)
{}

Goblin::~Goblin()
{
    if (getWeapon() != nullptr)
    {
       delete getWeapon();
    }
}

void Goblin::takeTurn()
{
    if (isNextToPlayer())
    {
        attack(this, getDungeon()->getPlayer());
    }
    else if (CanSmellPlayer(getDungeon(), GOBLIN_SMELL_DISTANCE))
    {
        chasePlayer(getDungeon()->getPlayer(), getDungeon());
    }
}
