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

int main() {
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
    
//    Set ss;
//    ss.insert("dosa");
//    assert(!ss.contains(""));
//    ss.insert("tortilla");
//    ss.insert("");
//    ss.insert("focaccia");
//    assert(ss.contains(""));
//    ss.erase("dosa");
//    assert(ss.size() == 3  &&  ss.contains("focaccia")  &&  ss.contains("tortilla")  &&  ss.contains(""));
//    string v;
//    assert(ss.get(1, v)  &&  v == "focaccia");
//    assert(ss.get(0, v)  &&  v == "");
    
}
