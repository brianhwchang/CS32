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
    Object();
    Object(int row, int col) {m_row = row; m_col = col;}
    Object(int row, int col, string name) {m_row = row; m_col = col; m_name = name;}
    Object(int row, int col, string name, string effect) {m_row = row; m_col = col; m_name = name; m_effect = effect;}
    Object(string name, string effect) {m_name = name; m_effect = effect;}
    virtual ~Object() {};
    
    //Getters
    int getRow() const {return m_row;}
    int getCol() const {return m_col;}
    string getName() const {return m_name;}
    string getEffect() const {return m_effect;}
    
    //Setters
    void setPos(int row, int col) {m_row = row; m_col = col;}
    
private:
    int m_row;
    int m_col;
    string m_name;
    string m_effect;
};


#endif /* Object_h */
