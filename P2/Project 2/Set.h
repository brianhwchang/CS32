//
//  Set.hpp
//  Project 2
//
//  Created by Brian Chang on 4/21/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <stdio.h>
#include <string>

using namespace std;

using ItemType = std::string;


class Set
{
public:
    
    Set(); //Constructor
    ~Set(); //Destructor
    Set(const Set& other); //Copy Constructor
    Set& operator=(const Set& rhs); //Assignment Operator
    
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const;
    
private:
    
    struct Node
    {
        ItemType m_value;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    Node* tail;
    int m_size;
};

//non-member functions

void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);






#endif /* Set_h */
