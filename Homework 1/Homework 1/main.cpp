//
//  main.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/15/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "pita");
    assert(ss.get(1, x)  &&  x == "roti");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include "Set.h"
//using namespace std;
//
//int main()
//{
//    Set ss;
//    ss.insert("lavash");
//    ss.insert("roti");
//    ss.insert("chapati");
//    ss.insert("injera");
//    ss.insert("roti");
//    ss.insert("matzo");
//    ss.insert("injera");
//    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
//    string x;
//    ss.get(0, x);
//    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
//    ss.get(4, x);
//    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
//    ss.get(2, x);
//    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss
//
//    Set gg;
//    gg.insert("dosa");
//    assert(!gg.contains(""));
//    gg.insert("tortilla");
//    gg.insert("");
//    gg.insert("focaccia");
//    assert(gg.contains(""));
//    gg.erase("dosa");
//    assert(gg.size() == 3  &&  gg.contains("focaccia")  &&  gg.contains("tortilla")  &&  gg.contains(""));
//    string v;
//    assert(gg.get(1, v)  &&  v == "focaccia");
//    assert(gg.get(0, v)  &&  v == "");
//
//
//    // Code for testing my swap function.
//
//    Set aa;
//    aa.insert("rice");
//    aa.insert("beans");
//    aa.insert("bread");
//    aa.insert("pasta");
//
//    Set bb;
//    bb.insert("chicken");
//    bb.insert("pork");
//    bb.insert("beef");
//
//    aa.swap(bb);
//    assert(aa.size()==3);
//    assert(bb.size()==4);
//    assert(aa.contains("chicken"));
//    assert(bb.contains("rice"));
//    assert(!aa.contains("pasta"));
//    assert(!bb.contains("beef"));
//}


//Alternate main() routine for testing unsigned longs.
//
//#include "Set.h"
//#include <iostream>
//#include <cassert>
//using namespace std;

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
//
////main routine for newSet
//#include <iostream>
//#include <cassert>
//#include <string>
//#include "newSet.h"
//using namespace std;


//int main()
//{
//    
//    Set a(1000);   // a can hold at most 1000 distinct items
//    Set b(5);      // b can hold at most 5 distinct items
//    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
//    ItemType v[6] = { 1, 2, 3, 4, 5, 6 };
//
//      // No failures inserting 5 distinct items into b
//    for (int k = 0; k < 5; k++)
//        assert(b.insert(v[k]));
//
//      // Failure if we try to insert a sixth distinct item into b
//    assert(!b.insert(v[5]));
//
//      // When two Sets' contents are swapped, their capacities are swapped
//      // as well:
//    a.swap(b);
//    assert(!a.insert(v[5])  &&  b.insert(v[5]));
//    
//    cout << "All tests passed" << endl;
//}


