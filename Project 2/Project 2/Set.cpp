//
//  Set.cpp
//  Project 2
//
//  Created by Brian Chang on 4/21/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Set.h"
#include <iostream>

using namespace std;

Set::Set() //Constructor
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

Set::~Set()//Destructor
{
    if (m_size == 0) //checking for empty set
        return;
    
    Node* p = head;
    
    while (p != nullptr)
    {
        p = p->next;
        delete p->prev;
    }
    delete tail;
}

Set::Set(const Set& other)
{
    
    
}



bool Set::empty() const //trivial empty fxn. DONE.
{
    if (m_size == 0)
        return true;
    else
        return false;
}


int Set::size() const //trivial size fxn. DONE.
{
    return m_size;
}


bool Set::insert(const ItemType& value) // NOT DONE
{
    return true;
}


bool Set::erase(const ItemType& value) // NOT DONE
{
    return true;
}


bool Set::contains(const ItemType& value) const //DONE.
{
    Node* p = head;
    
    while (p != nullptr)            //Loop through the list.
    {
        if (p->m_value == value)    //if we find the value within the list, return true.
        {
            return true;
        }
        p = p->next;                //if no match is found, advance to next node.
    }
    
    return false;                   //assuming no matches are found in the list, return false.
}



bool Set::get(int pos, ItemType& value) const // NOT DONE
{
    return true;
}


void Set::swap(Set& other)          //Swapper fxn. DONE.
{
    int temp = m_size;              //Swapping m_sizes.
    m_size = other.m_size;
    other.m_size = temp;

    Node* tempHead = head;          //Swapping head pointers.
    head = other.head;
    other.head = tempHead;

    Node* tempTail = tail;          //Swapping tail pointers.
    tail = other.tail;
    other.tail = tempTail;
}


//----------------------------------------------------------------------------------------
//--------------------------non-member functions------------------------------------------
//----------------------------------------------------------------------------------------


void unite(const Set& s1, const Set& s2, Set& result)
{
    
}


void subtract(const Set& s1, const Set& s2, Set& result)
{
    
}
