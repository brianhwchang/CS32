//
//  main.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <string>
#include "Set.h"
using namespace std;

int main()
{
    Set ss;
    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    ss.insert("injera");
    ss.insert("roti");
    ss.insert("matzo");
    ss.insert("injera");
    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    string x;
    ss.get(0, x);
    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, x);
    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, x);
    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss
    
    Set gg;
    gg.insert("dosa");
    assert(!gg.contains(""));
    gg.insert("tortilla");
    gg.insert("");
    gg.insert("focaccia");
    assert(gg.contains(""));
    gg.erase("dosa");
    assert(gg.size() == 3  &&  gg.contains("focaccia")  &&  gg.contains("tortilla")  &&  gg.contains(""));
    string v;
    assert(gg.get(1, v)  &&  v == "focaccia");
    assert(gg.get(0, v)  &&  v == "");
    
    
    // Code for testing my swap function.
    
    Set aa;
    aa.insert("rice");
    aa.insert("beans");
    aa.insert("bread");
    aa.insert("pasta");
    
    Set bb;
    bb.insert("chicken");
    bb.insert("pork");
    bb.insert("beef");
    
    aa.swap(bb);
    assert(aa.size()==3);
    assert(bb.size()==4);
    assert(aa.contains("chicken"));
    assert(bb.contains("rice"));
    assert(!aa.contains("pasta"));
    assert(!bb.contains("beef"));
}
