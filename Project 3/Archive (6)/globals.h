//
//  GLOBALS.h
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef GLOBALS_h
#define GLOBALS_h

#include <string>
 
using namespace std;

const int MAXROWS = 18;                // max number of rows in the arena
const int MAXCOLS = 70;                // max number of columns in the arena


// NAMES
const string BOGEYMAN                 = "Bogeyman";
const string DRAGON                   = "Dragon";
const string SNAKEWOMAN               = "Snakewoman";
const string GOBLIN                   = "Goblin";

// DISPLAYS
const char PLAYER_DISPLAY               = '@';
const char BOGEYMAN_DISPLAY             = 'B';
const char SNAKEWOMAN_DISPLAY           = 'S';
const char DRAGON_DISPLAY               = 'D';
const char GOBLIN_DISPLAY               = 'G';
const char SCROLL_DISPLAY               = '?';
const char WEAPON_DISPLAY               = ')';
const char STAIR_DISPLAY                = '>';
const char GOLDEN_IDOL_DISPLAY          = '&';
const char WALL_DISPLAY                 = '#';
const char EMPTY                        = ' ';



#endif /* GLOBALS_h */
