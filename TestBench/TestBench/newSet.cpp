
//  newSet.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/16/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "newSet.h"
#include <string>
#include <iostream>

using namespace std;

Set::Set() //creates an empty set of size 0, because it has no items.
{
    m_size = 0;
    m_storage = DEFAULT_MAX_ITEMS;
    m_set = new ItemType[DEFAULT_MAX_ITEMS]; //initialising a new array with max items storage size
}

Set::Set(int storage) //creates an empty set of size 0, because it has no items.
{
    if (storage < 0) //failing condition if negative interger is passed into the fxn.
        exit(1);

    m_size = 0;
    m_storage = storage; //taking argument for storage size
    m_set = new ItemType[storage]; //initialising new array with size determined by given storage argument.
}

Set::Set(const Set & originalSet)
{
    m_storage = originalSet.m_storage; // copying storage space
    m_size = originalSet.m_size; // copying size
    m_set = new ItemType[m_storage]; // initialising new array based on original conidtions.

    for (int i = 0; i < originalSet.m_size; i++) // looping through original set
    {
        m_set[i] = originalSet.m_set[i]; //copying each value from original set into the new set.
    }
}

Set::~Set()
{
    delete [] m_set; //destructor to free up allocated memory.
}

Set& Set::operator = (const Set s)
{
    if (this != &s)
    {
        delete [] m_set; //deleting existing set.

        m_size = s.m_size; //copying size and storage of input set s.
        m_storage = s.m_storage;
        m_set = new ItemType[m_storage]; //initialising new array based on input set parameters.

        for (int i = 0; i < m_size; i++) // looping through input set
        {
            m_set[i] = s.m_set[i]; //copying each value from original set into the new set.
        }
    }
    return *this;
}

bool Set::empty() const // Return true if the set is empty, otherwise false.
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Set::size() const    // Return the number of items in the set.
{
    return m_size;
}


// Insert value into the set if it is not already present.
// Return true if the value is actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).
bool Set::insert(const ItemType& value)
{
    if (m_size==0) //Just adding if set is empty. Saves us the time of parsing for duplicates.
    {
        m_set[0] = value;
        m_size++;
        return true;
    }

    if (contains(value)) // checking for duplicates within the set.
        return false;


    //Assuming set is not full.
    //Assuming value is not a duplicate.
    if (m_size < m_storage)
    {
    m_set[m_size] = value; //adding value to the set
    m_size++; //incrementing size counter
    return true;
    }

    else
        return false;
}


// Remove the value from the set if it is present.
// Return true if the value was removed;
// otherwise, leave the set unchanged and return false.
bool Set::erase(const ItemType& value)
{
    if (m_size == 0) // If the set is empty, nothing to be removed.
        return false;

    for (int i = 0; i < m_size; i++) //iterating through each value in the set.
    {
        if (m_set[i] == value) //Checking is value is present in set.
        {
            for (int j = i; j < m_size ;j++)
            {
                m_set[j] = m_set[j+1]; //overwriting value with next entry.
            }
            m_size--; //decrementing size
            return true;
        }
    }
    //Assuming no matching value was found to erase. Leave unchanged. Return false.
    return false;
}


// Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value) const
{
    if (m_size == 0) //empty set contains nothing lol.
    {
        return false;
    }

    for (int i = 0; i < m_size; i++) //iterating through the set array.
    {
        if (m_set[i] == value) //returning false if duplicate.
            return true;
    }

    //Assuming no duplicates were found
    return false;
}


// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.
bool Set::get(int i, ItemType& value) const
{
    if (m_size == 0) //can't get anything from an empty string
        return false;

    ItemType duplicateSet[DEFAULT_MAX_ITEMS]; //creating duplicate set to store sorted set.
    int index = 0;

    for (int j = 0; j < m_size; j++)
    {
        index = 0;
        for (int k = 0; k < m_size; k++)
        {
            if (m_set[j] > m_set[k])
                index++;
        }
        duplicateSet[index] = m_set[j];
    }

    if ( i >= 0 && i < m_size) //checking that int i is zero or greater, and less than m_size (within scope of array)
    {
        value = duplicateSet[i]; //storing i-th value of the duplicate set in the variable value
        return true;
    }
    else //catch all
        return false;

}



// Exchange the contents of this set with the other one.
void Set::swap(Set& other)
{
    int tempStorage;
    int tempSize;
    ItemType *tempPointer;

    //storage swap.

    tempStorage = m_storage;
    m_storage = other.m_storage;
    other.m_storage = tempStorage;

    //size swap

    tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    //Memory address swap

    tempPointer = m_set; //storing "original" mem address in ptr.
    m_set = other.m_set; //assigning mem address of other to "original.
    other.m_set = tempPointer; //assigning mem address of original (stored in tempPointer) to other.

}

