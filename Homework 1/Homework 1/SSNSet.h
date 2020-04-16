//
//  SSNSet.hpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
//
#ifndef SSNSet_h
#define SSNSet_h

#include <stdio.h>
#include "Set.h"

class SSNSet
{
  public:
    SSNSet();          // Create an empty SSN set.

    bool add(unsigned long ssn);
      // Add an SSN to the SSNSet.  Return true if and only if the SSN
      // was actually added.

    int size() const;  // Return the number of SSNs in the SSNSet.

    void print() const;
      // Write to cout every SSN in the SSNSet exactly once, one per
      // line.  Write no other text.

  private:
    // Some of your code goes here.
    int m_ssnSize;
    Set m_ssnSet;
};


#endif /* SSNSet_h */
