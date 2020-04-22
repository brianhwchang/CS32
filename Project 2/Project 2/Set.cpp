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

Set::Set(const Set& other) // Copy constructor
{
    m_size = other.m_size; //copy sizes
    
    if (other.head == nullptr)
        head = nullptr;
    
    else
    {
        head = new Node;
        head->m_value = other.head->m_value;
        head->next = nullptr;
        
        Node* thisCur = head;   // @@@@@@@@@@ ASK ALISSA @@@@@@@@@@
        Node* otherCur = other.head;
        
        while(otherCur->next != nullptr)
        {
            thisCur->next = new Node;                         //creating next node
            thisCur->next->m_value = otherCur->next->m_value; //storing next val from other into current->next->val
            thisCur->next = nullptr;                          //assigning nullptr in to cur->next in case this is the last val
            
            thisCur = thisCur->next;
            otherCur = otherCur->next;
        }
        tail = thisCur;                       //ASK ALISSA ABOUT ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@@@@@@@@@@
    }
}

Set::~Set()//Destructor. DONE.
{
    if(m_size == 1)
        delete head;
    
    Node* p = head;
    while (p->next != nullptr)
    {
        p = p->next;
        delete p->prev;
    }
    delete tail;
}

Set& Set::operator=(const Set& rhs)
{
    return *this;
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


bool Set::insert(const ItemType& value) //DONE
{
    
    if (contains(value))            //check if it's already in there
        return false;
    
    if (empty() == true)            //If empty, add to front.
    {
        Node* p = new Node;
        p->m_value = value;
        p->next = nullptr;          //nothing before it
        p->prev = nullptr;          //nothing after it
        head = p;                   //If the list was empty, this is the first item
        tail = p;                   //If the list was empty, this is the last item
        m_size++;
        return true;
    }
    
    else if (value < head->m_value) //value is less than head (Which should be the smallest value)
    {
        Node* p = new Node;
        p->m_value = value;
        p->next = head;             //old head becomes 2nd node in list
        p->prev = nullptr;          //nothing precedes 1st val
        head->prev = p;             //p now precedes old head.
        head = p;                   //p becomes new head.
        m_size++;                   //up that counter, bitch.
        return true;
    }
    
    else if (value > tail->m_value) //value is greather than tail (Which should be the largest value)
    {
        Node* p = new Node;
        p->m_value = value;
        p->prev = tail;             //creating backwards link from p to old tail.
        p->next = nullptr;          //nothing comes after p, cause it's at the end.
        tail->next = p;             //creating forward link from old tail to p.
        tail = p;                   //p becomes the new tail.
        m_size++;                   //Bump those numbers up, those are rookie numbers.
        return true;
    }
    
    else
    {
        Node* p = head;
        while (p != nullptr) //traversing list
        {
            if (p->next != nullptr && p->next->m_value >= value)
                break;              //p is pointing to the right position.
            p = p->next;            //advance to next node.
        }
        
        if (p->next != nullptr)
        {
            Node* insertNode = new Node;
            insertNode->m_value = value;
            insertNode->prev = p;           //because p precedes insert node.
            insertNode->next = p->next;     //linking insert 
        }
        
        
    }
    
    
    
    
    
    
    Node* cur = head->next;         //creating a temp node pointer called cur.
    
    while (cur->next != nullptr)    //advancing to terminal node.         @@@@@@@@@@ ASK ALISSA IF I COULD JUST USE THE TAIL @@@@@@@@@@@@@
        cur = cur->next;
    
    Node* insertNode = new Node;    //creating new node
    insertNode->m_value = value;    //assigning value
    insertNode->next = nullptr;     //next points to nullptr
    insertNode->prev = cur;         //prev points to previous terminal node
    cur->next = insertNode;         //previous terminal node now points to insert node.
    tail = insertNode;              //this becomes the new tail
    
    return true;                    //return true after successful insertion. lol.
    
    
    
    
    
}


bool Set::erase(const ItemType& value) // NOT DONE
{
    if (contains(value))            //check if it's already in there
        return false;
    
    Node* p = head;
    
    while (p != nullptr) //traversing list
    {
        if (p->next != nullptr && p->next->m_value == value)
            break;
        p = p->next;
    }
    
    if (p != nullptr) //we found our value! (Thanks Carey.)
    {
        Node* eraseMe = p->next;        //Assigning target node to pointer "eraseMe"
        p->next = eraseMe->next;        //Skipping eraseMe node in forward link.
        eraseMe->next->prev = p;        //Skipping eraseMe node in backward link.
        
        delete eraseMe;                 //deleting the eraseMe node;
        return true;                    //Our work here is done.
    }
    
    return false;                       //if nothing is met?              @@@@@@@@@@@ ASK ALISSA @@@@@@@@@@@@@
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


bool Set::get(int pos, ItemType& value) const //DONE
{
    if (pos < 0 || pos > m_size) //checking that position is valid (positive and within range).
        return false;
    
    int index = 0;
    for (Node* p = head; p != nullptr; p = p->next)     //looping through each node.
    {
        if (index >= pos)                               //if index matches position
        {
            value = p->m_value;                         //assigned value stored at index node to value variable.
            break;
        }
        index++;
    }
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


void unite(const Set& s1, const Set& s2, Set& result) //NOT DONE.
{
    
}


void subtract(const Set& s1, const Set& s2, Set& result) //NOT DONE.
{
    
}
