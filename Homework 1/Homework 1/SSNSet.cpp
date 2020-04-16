//
//  SSNSet.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "SSNSet.h"
#include "Set.h"
#include <iostream>
#include <string>

using namespace std;


SSNSet::SSNSet()
{
    m_ssnSize = 0; //creating an empty SSN set.
}



bool SSNSet::add(unsigned long ssn) //Adding an SSN to the set.
{
    if (m_ssnSet.insert(ssn)) //using insert fxn from Set class.
    {
        m_ssnSize++; //incrementing counter
        return true;
    }
    else
        return false;
}



int SSNSet::size() const
{
    return m_ssnSize; //trivial getter fxn.
}



// Write to cout every SSN in the SSNSet exactly once, one per line.
// Write no other text.
void SSNSet::print() const
{
    unsigned long tempVal = 0; //creating placeholder to store SSNs for printing.
    
    for (int i = 0; i < m_ssnSize; i++) //iterating through set
    {
        m_ssnSet.get(i, tempVal); //using getter fxn to get each val. Storing in tempVal
        cout << tempVal << endl; //cout-ing tempVal.
    }
}

