//
//  main.cpp
//  Project 2
//
//  Created by Brian Chang on 4/21/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <iostream>
#include <string>
#include "Set.h"

using namespace std;

int main()
{
//    string test routine

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
    assert(ss.erase("roti"));
    assert(ss.size() == 4);
    assert(!ss.empty());

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
    assert(!gg.empty());

//    test code for swapper

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

//    //copy constructor test code
//
    Set d(aa);
    Set e(bb);

    assert(d.size() == 3);
    assert(e.size() == 4);
    assert(d.contains("chicken"));
    assert(e.contains("rice"));
    assert(!d.contains("pasta"));
    assert(!e.contains("beef"));
    
    //Destructor and assignment operator test code.
    
    Set abc;
    abc.insert("Kobe");
    abc.insert("Shaq");
    abc.insert("Lebron");
    
    Set xyz;
    xyz.insert("Kareem");
    xyz.insert("Magic");
    
    xyz.operator=(abc);
    assert(xyz.size() == 3);
    assert(xyz.contains("Kobe"));
    assert(xyz.contains("Shaq"));
    assert(xyz.contains("Lebron"));
    assert(!xyz.contains("Kareem"));
    assert(!xyz.contains("Magic"));
    
    //unite fxn test code
    
    Set result;
    result.insert("Sprouts");
    result.insert("Okra");
    result.insert("Asparagus");
    
    Set bloo;
    bloo.insert("apples");
    bloo.insert("pears");
    bloo.insert("melons");
    bloo.insert("grapes");
    bloo.insert("bananas");
    
    Set bbo;
    bbo.insert("oranges");
    bbo.insert("pears");
    bbo.insert("mangoes");
    bbo.insert("grapes");
    bbo.insert("lychees");
    
//    void unite(const Set& bloo, const Set& bbo, Set& result);
//    
//    assert(result.contains("apples"));
//    assert(result.contains("grapes"));
//    assert(result.contains("oranges"));
//    assert(result.contains("lychees"));
//    assert(!result.contains("Sprouts"));
//    assert(!result.contains("Asparagus"));
//    assert(result.size() == 8);
    
//    Set jj;
//    jj.insert("1");
//    jj.insert("2");
//    jj.insert("3");
//    jj.insert("4");
//    jj.insert("5");
//
//    Set kk;
//    kk.insert("1");
//    kk.insert("6");
//    kk.insert("2");
//    kk.insert("8");
//    kk.insert("3");
//
//    void subtract(const Set& s1, const Set& s2, Set& result);
//
//    assert(result.contains("2"));
//    assert(result.contains("4"));
//    assert(result.contains("6"));
//    assert(result.contains("8"));
//    assert(!result.contains("1"));
//    assert(!result.contains("2"));
//    assert(!result.contains("3"));
    
    cout << "All tests passed" << endl;
    return (1);
    
}


//Unsigned long test routine
//
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
