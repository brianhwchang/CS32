//
//  Object.hpp
//  Project 3
//
//  Created by Brian Chang on 5/21/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <stdio.h>
#include <string>

using namespace std;

class Player;
class Dungeon;

class Object
{
public:
    
    //Constructors and Destructors

    //Position Only
    Object(int row, int col) {m_row = row; m_col = col;}
    //Name and Action Only.
    Object(string name, string action) {m_name = name; m_action = action;}
    //Position and Name Only.
    Object(int row, int col, string name) {m_row = row; m_col = col; m_name = name;}
    //Postion, Name, Action.
    Object(int row, int col, string name, string action) {m_row = row; m_col = col; m_name = name; m_action = action;}
    
    virtual ~Object() {};
    
    //Getters
    int getRow() const {return m_row;}
    int getCol() const {return m_col;}
    string getName() const {return m_name;}
    string getAction() const {return m_action;}
    
    //Setters
    void setPos(int row, int col) {m_row = row; m_col = col;}
    
private:
    int m_row;
    int m_col;
    string m_name;
    string m_action;
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------WEAPON CLASSES-----------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class Weapon : public Object
{
public:
    Weapon(string name, string action, int dexb, int dmg);
    Weapon(int row, int col, string name, string action, int dexb, int dmg);
    virtual ~Weapon() {};
    
    int getDex() {return dexBonus;}
    int getDmg() {return dmgAmt;}
    
private:
    int dexBonus;
    int dmgAmt;
};

class Mace : public Weapon
{
    Mace();
    ~Mace() {};
};

class ShortSword : public Weapon
{
    ShortSword();
    ~ShortSword() {};
};

class LongSword : public Weapon
{
    LongSword();
    ~LongSword() {};
};

class MagicAxe : public Weapon
{
    MagicAxe();
    MagicAxe(int row, int col);         //Drop Constructor
    ~MagicAxe() {};
};

class MagicFangs : public Weapon
{
    MagicFangs();
    MagicFangs(int row, int col);       //Drop Constructor
    ~MagicFangs() {};
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------SCROLL CLASSES-----------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class Scroll : public Object
{
public:
    Scroll(string name, string action);
    Scroll(int row, int col, string name, string action);
    virtual ~Scroll() {}
};

class HPScroll : public Scroll
{
    HPScroll();
    HPScroll(int row, int col);
    ~HPScroll() {}
};

class ArmorScroll : public Scroll
{
    ArmorScroll();
    ArmorScroll(int row, int col);
    ~ArmorScroll() {}
};

class StrengthScroll : public Scroll
{
    StrengthScroll();
    StrengthScroll(int row, int col);
    ~StrengthScroll() {}
};

class DexScroll : public Scroll
{
    DexScroll();
    DexScroll(int row, int col);
    ~DexScroll() {}
};

class TPScroll : public Scroll
{
    TPScroll();
    TPScroll(int row, int col);
    ~TPScroll() {};
};


#endif /* Object_h */
