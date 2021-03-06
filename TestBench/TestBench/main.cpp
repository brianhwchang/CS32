//
//  main.cpp
//  TestBench
//
//  Created by Brian Chang on 4/16/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//


//newset long tests

//#include "newSet.h"
//        #include <iostream>
//        #include <cassert>
//        using namespace std;
//
//        void test()
//        {
//            Set uls;
//            assert(uls.insert(20));
//            assert(uls.insert(10));
//            assert(uls.size() == 2);
//            assert(uls.contains(10));
//            ItemType x = 30;
//            assert(uls.get(0, x)  &&  x == 10);
//            assert(uls.get(1, x)  &&  x == 20);
//        }
//
//        int main()
//        {
//            test();
//            cout << "Passed all tests" << endl;
//        }



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




//long tests
//
//#include "Set.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
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



//string tests

//#include "Set.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Set ss;
//    assert(ss.insert("roti"));
//    assert(ss.insert("pita"));
//    assert(ss.size() == 2);
//    assert(ss.contains("pita"));
//    ItemType x = "laobing";
//    assert(ss.get(0, x)  &&  x == "pita");
//    assert(ss.get(1, x)  &&  x == "roti");
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
