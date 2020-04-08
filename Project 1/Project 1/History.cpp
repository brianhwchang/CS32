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
    for (int i = 0; i < nRows; i++) { //for each row
        for (int j = 0; j < nCols; j++) { // for each column
            vialsDropped[i][j] = '.'; //initialise every gridpoint as '.', bcos no vials dropped at game start.
        }
    }
}

