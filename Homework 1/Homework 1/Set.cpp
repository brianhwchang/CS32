//
//  Set.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Set.h"
#include <string>
#include <iostream>

Set::Set() //creates an empty set of size 0, because it has no items.
{
    m_size = 0;
}

bool Set::empty() const // Return true if the set is empty, otherwise false.
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Set::size() const    // Return the number of items in the set. // const
{
    return m_size;
}



// Insert value into the set if it is not already present.  Return
// true if the value is actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).
bool Set::insert(const std::string& value) //not const
{
    return m_size;
}


// Remove the value from the set if it is present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
bool Set::erase(const std::string& value) //not const
{
    return m_size;
}
 

// Return true if the value is in the set, otherwise false.
bool Set::contains(const std::string& value) const //const
{
    return m_size;
}


// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.
bool Set::get(int i, std::string& value) const //const
{
    return m_size;
}



// Exchange the contents of this set with the other one.
void Set::swap(Set& other) // not const
{
    
}
