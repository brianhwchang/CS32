//
//  Set.hpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <stdio.h>
#include <string>


class Set
{
  public:
    Set();         // Create an empty set (i.e., one with no items).

    bool empty() const;  // Return true if the set is empty, otherwise false. //const

    int size() const;    // Return the number of items in the set. // const

    bool insert(const std::string& value); //not const
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if the value was not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const std::string& value); //not const
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
     
    bool contains(const std::string& value) const; //const
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, std::string& value) const; //const
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other); // not const
      // Exchange the contents of this set with the other one.
    
private:
    int m_size;
    
};

#endif /* Set_h */
