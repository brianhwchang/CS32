//
//  History.cpp
//  Project 1
//
//  Created by Brian Chang on 4/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "History.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

using namespace std;

History::History(int nRows, int nCols) // code for History constructor
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < nRows; i++) //for each row
    {
        for (int j = 0; j < nCols; j++) // for each column
        {
            vialsDropped[i][j] = '.'; //initialise every gridpoint as '.', bcos no vials dropped at game start.
        }
    }
}


bool History::record(int r, int c)
{
    if (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols) //checking if gridpoint is within arena bounds.
    {
        if (vialsDropped[r-1][c-1] >= 'A' && vialsDropped[r-1][c-1] <= 'Z')
            vialsDropped[r-1][c-1]++; //incrementing counter to next alphabet.
        else
            vialsDropped[r-1][c-1] = 'A'; //setting counter to 'A' which indicates 1 vial dropped.
        return true;
    }
    else // if gridpoint is out of bounds.
        return false;
}


void History::display() const
{
    clearScreen(); // using clearScreen fxn.
    
    for (int r = 0; r < m_rows; r++) //for each row
    {
        for (int c = 0; c < m_cols; c++) // for each column
        {
            cout << vialsDropped[r][c]; // printing the grid
        }
        cout << endl;
    }
    cout << endl;
}
