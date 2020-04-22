//
//  testSSNSet.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <stdio.h>
#include "SSNSet.h"
#include "Set.h"
#include <iostream>
#include <string>

using namespace std;


//Main routine for testing SSN

int main()
{
    SSNSet aa;
    assert(aa.size() == 0); //testing constructor
    aa.add(987654321); //testing add fxn
    aa.add(123456789);
    aa.add(192837475);
    assert(aa.size() == 3); //testing size fxn
    aa.print(); //testing print fxn.

    cout << "All tests passed." << endl;
}

