//
//  newSet.hpp
//  TestBench
//
//  Created by Brian Chang on 4/16/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
//
//  newSet.hpp
//  Homework 1
//
//  Created by Brian Chang on 4/16/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef newSet_h
#define newSet_h

#include <stdio.h>
#include <string>
using namespace std;

using ItemType = std::string;
const int DEFAULT_MAX_ITEMS = 240;

class Set
{
  public:
    
    Set();         // Create an empty set (i.e., one with no items).
    
    Set(int storage);    // Dynamic set constructor. (Overloaded)
    
    Set(const Set & originalSet); // Copy compiler from "old" set
    
    ~Set(); //Destructor
    
    Set& operator = (const Set s);

    bool empty() const;  // Return true if the set is empty, otherwise false. //const

    int size() const;    // Return the number of items in the set. // const

    bool insert(const ItemType& value); //not const
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if the value was not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value); //not const
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
     
    bool contains(const ItemType& value) const; //const
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const; //const
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other); // not const
      // Exchange the contents of this set with the other one.
    
private:
    int m_size;
    int m_storage;
    ItemType *m_set;
};




#endif /* newSet_h */
