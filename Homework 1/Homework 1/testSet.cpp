//
//  TestSet.cpp
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

int main() //main routine testing with strings
{
//    Set s;
//    assert(s.empty());
//    ItemType x = "arepa";
//    assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
//    s.insert("chapati");
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == "chapati");
//    cout << "Passed all tests" << endl;

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



//Unsigned long test routine

//void test()
//{
//    Set uls;
//    assert(uls.insert(20));
//    assert(uls.insert(10));
//    assert(uls.size() == 2);
//    assert(uls.contains(10));
//    ItemType x = 30;
//    assert(uls.get(0, x)  &&  x == 10);
//    assert(uls.get(1, x)  &&  x == 20);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}


//Alternate main() routine for testing unsigned longs.
//
//#include "Set.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    Set s;
//    assert(s.empty());
//    ItemType x = 9876543;
//    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
//    s.insert(123456789);
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == 123456789);
//    cout << "Passed all tests" << endl;
//}
//
