//
//  linear test routines.cpp
//  Homework 3
//
//  Created by Brian Chang on 5/8/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <cassert>
//

//using namespace std;
//
//bool somePredicate(string s)        //return true if empty, false if full.
//{
//    return s.empty();
//}

//
//void testFirstFalse()
//{
//    const int SIZE = 3;
//
//    string a[SIZE] = {"", "abc", "asd"};
//
//    assert(firstFalse(a, 0) == -1);
//    assert(firstFalse(a, 1) == -1);
//    assert(firstFalse(a, 2) == 1);
//    assert(firstFalse(a, 3) == 1);
//
//    string b[SIZE] = {"abc", "", "asd"};
//
//    assert(firstFalse(b, 0) == -1);
//    assert(firstFalse(b, 1) == 0);
//    assert(firstFalse(b, 2) == 0);
//    assert(firstFalse(b, 3) == 0);
//
//    string c[SIZE] = {"", "", ""};
//
//    assert(firstFalse(c, 0) == -1);
//    assert(firstFalse(c, 1) == -1);
//    assert(firstFalse(c, 2) == -1);
//    assert(firstFalse(c, 3) == -1);
//
//    string d[SIZE] = {"", "asd", ""};
//
//    assert(firstFalse(d, 0) == -1);
//    assert(firstFalse(d, 1) == -1);
//    assert(firstFalse(d, 2) == 1);
//    assert(firstFalse(d, 3) == 1);
//
//    string e[SIZE] = {"abc", "as", "ae"};
//
//    assert(firstFalse(e, 0) == -1);
//    assert(firstFalse(e, 1) == 0);
//    assert(firstFalse(e, 2) == 0);
//    assert(firstFalse(e, 3) == 0);
//}
//
//
//
//
//
//
//void testAllFalse()
//{
//    const int SIZE = 3;
//
//    string a[SIZE] = {"ads", "abc", "asd"};
//
//    assert(allFalse(a, 0));
//    assert(allFalse(a, 1));
//    assert(allFalse(a, 2));
//    assert(allFalse(a, 3));
//
//    string b[SIZE] = {"", "", ""};
//
//    assert(allFalse(b, 0));
//    assert(!allFalse(b, 1));
//    assert(!allFalse(b, 2));
//    assert(!allFalse(b, 3));
//
//    string c[SIZE] = {"ab", "", ""};
//
//    assert(allFalse(c, 0));
//    assert(allFalse(c, 1));
//    assert(!allFalse(c, 2));
//    assert(!allFalse(c, 3));
//
//    string d[SIZE] = {"ab", "cd", ""};
//
//    assert(allFalse(d, 0));
//    assert(allFalse(d, 1));
//    assert(allFalse(d, 2));
//    assert(!allFalse(d, 3));
//
//    string e[SIZE] = {"ab", "", "cd"};
//
//    assert(allFalse(e, 0));
//    assert(allFalse(e, 1));
//    assert(!allFalse(e, 2));
//    assert(!allFalse(e, 3));
//}
//
//void testCountFalse()
//{
//    const int SIZE = 3;
//
//    string a[SIZE] = {"", "abc", "asd"};
//
//    assert(countFalse(a, 0) == 0);
//    assert(countFalse(a, 1) == 0);
//    assert(countFalse(a, 2) == 1);
//    assert(countFalse(a, 3) == 2);
//
//    string b[SIZE] = {"abc", "", "asd"};
//
//    assert(countFalse(b, 0) == 0);
//    assert(countFalse(b, 1) == 1);
//    assert(countFalse(b, 2) == 1);
//    assert(countFalse(b, 3) == 2);
//
//    string c[SIZE] = {"abc", "asd", ""};
//
//    assert(countFalse(c, 0) == 0);
//    assert(countFalse(c, 1) == 1);
//    assert(countFalse(c, 2) == 2);
//    assert(countFalse(c, 3) == 2);
//}
//
//
//
//void testlocateMax()
//{
//    const int SIZE = 3;
//
//    string a[SIZE] = {"", "abc", "asd"};
//
//    assert(locateMaximum(a, 0) == -1);
//    assert(locateMaximum(a, 1) == 0);
//    assert(locateMaximum(a, 2) == 1);
//    assert(locateMaximum(a, 3) == 2);
//
//    string b[SIZE] = {"abc", "", "asd"};
//
//    assert(locateMaximum(b, 0) == -1);
//    assert(locateMaximum(b, 1) == 0);
//    assert(locateMaximum(b, 2) == 0);
//    assert(locateMaximum(b, 3) == 2);
//
//    string c[SIZE] = {"abc", "asd", ""};
//
//    assert(locateMaximum(c, 0) == -1);
//    assert(locateMaximum(c, 1) == 0);
//    assert(locateMaximum(c, 2) == 1);
//    assert(locateMaximum(c, 3) == 1);
//
//    string d[SIZE] = {"", "asd", "db"};
//
//    assert(locateMaximum(d, 0) == -1);
//    assert(locateMaximum(d, 1) == 0);
//    assert(locateMaximum(d, 2) == 1);
//    assert(locateMaximum(d, 3) == 2);
//
//    string e[SIZE] = {"abc", "as", "ae"};
//
//    assert(locateMaximum(e, 0) == -1);
//    assert(locateMaximum(e, 1) == 0);
//    assert(locateMaximum(e, 2) == 1);
//    assert(locateMaximum(e, 3) == 1);
//}
//
//
//void testContains()
//{
//    const int SIZE = 7;
//    const int SIZE1 = 3;
//    const int SIZE2 = 0;
//
//    string a1[SIZE] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
//    string a2[SIZE1] = {"kyle", "kenny", "butters"};
//    string a3[SIZE1] = {"kyle", "cartman", "cartman"};
//    string a4[SIZE1] = {"kyle", "butters", "kenny"};
//    string a5[SIZE1] = {"stan", "kenny", "kenny"};
//    string a6[SIZE1] = {""};
//
//    assert(contains(a1, SIZE, a2, SIZE1));
//    assert(contains(a1, SIZE, a3, SIZE1));
//    assert(contains(a1, SIZE, a6, SIZE2));
//
//    assert(!contains(a1, SIZE, a4, SIZE1));
//    assert(!contains(a1, SIZE, a5, SIZE1));
//}
//
//
//int main()
//{
//    testAllFalse();
//    testCountFalse();
//    testFirstFalse();
//    testlocateMax();
//    testContains();
//    cout << "all tests passed" << endl;
//}
