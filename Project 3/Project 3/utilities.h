//
//  utilities.hpp
//  Project 3
//
//  Created by Brian Chang on 5/19/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

const char ARROW_LEFT  = 'h';
const char ARROW_RIGHT = 'l';
const char ARROW_UP    = 'k';
const char ARROW_DOWN  = 'j';

char getCharacter();
void clearScreen();
int randInt(int lowest, int highest);  // random int from lowest to highest
int randInt(int limit);                // random int from 0 to limit-1
bool trueWithProbability(double p);    // return true with probability p

#endif // UTILITIES_INCLUDED

