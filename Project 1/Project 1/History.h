//
//  History.hpp
//  Project 1
//
//  Created by Brian Chang on 4/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h" //for constants.

using namespace std;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    char vialsDropped[MAXROWS][MAXCOLS]; // why do we declare the var with MAXROWS and MAXCOLS to start with?
    int r;
    int c;
    
};

#endif /* History_h */
