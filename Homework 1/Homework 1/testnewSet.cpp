//
//  testnewSet.cpp
//  Homework 1
//
//  Created by Brian Chang on 4/16/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

//newset string tests

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

//main routine to test longs


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


