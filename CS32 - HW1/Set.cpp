//
//  Set.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.


#include "Set.h"
#include <string>
#include <iostream>

using namespace std;

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
    if (m_size > DEFAULT_MAX_ITEMS) //Ensuring that we do no exceed max items in set.
        return false;
    
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
    m_set[m_size] = value; //adding value to the set
    m_size++; //incrementing size counter
    return true;
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
    
    
//    for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
//    {
//        duplicateSet[j] = m_set[j];
//    }
//
//    for (int k = 0; k < m_size; k++) //Using bubblesort to sort the list
//    {
//        for (int j = 0; j < m_size-k; j++)
//        {
//            if (duplicateSet[j] > duplicateSet[j+1]) //swapping indexes
//            {
//                ItemType temp = duplicateSet[j];
//                duplicateSet[j] = duplicateSet[j + 1];
//                duplicateSet[j + 1] = temp;
//            }
//        }
//    }
}



// Exchange the contents of this set with the other one.
void Set::swap(Set& other)
{
    ItemType duplicateSet[DEFAULT_MAX_ITEMS]; //creating duplicate set to store sorted set.
    
    int placeholderSize = m_size; //assigning original size to placeholder var
    m_size = other.m_size; //assigning size of other set to "original" set.
    other.m_size = placeholderSize; // assigning size of "original" set to other set.
    
    int longerSet; // creating temp var to hold longer size.
                   // such that, I wont have to run the loop 240 times for every swap.
    
    if (m_size > other.m_size)
        longerSet = m_size;
    else
        longerSet = other.m_size;
    
    for (int i = 0; i < longerSet; i++) // swapping each term. #efficiency #bigBrainTings
    {
        duplicateSet[i] = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = duplicateSet[i];
    }
}

