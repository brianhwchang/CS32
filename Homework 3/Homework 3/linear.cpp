//
//  linear.cpp
//  Homework 3
//
//  Created by Brian Chang on 5/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//


// Return false if the somePredicate function returns true for at
// least one of the array elements; return true otherwise.

bool allFalse(const string a[], int n)
{
    if (n <= 0)
        return true;

    if (somePredicate(a[0]))            //if any of them are empty, return false.
        return false;

    else
        return allFalse(a+1, n-1);
}


// Return the number of elements in the array for which the
// somePredicate function returns false.

int countFalse(const string a[], int n)
{
    if (n <= 0)                                 //end search
        return 0;

    if (somePredicate(a[0]) == false)           //if false add 1 and continue
        return (1 + countFalse(a+1, n-1));

    else                                        //if true, just continue.
        return countFalse(a+1, n-1);
}


// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;                      //if we reach the end and no false, return -1.

    if (somePredicate(a[0]) == false)
        return 0;                       //"break the loop" and "stop incrementing implicit counter"

    else
    {
        if (firstFalse(a+1, n-1) == -1) //if the next iteration returns -1, return -1.
            return -1;
        else
            return 1 + firstFalse(a+1, n-1);    //increment implicit counter
    }
}


// Return the subscript of the greatest string in the array (i.e.,
// the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.

int locateMaximum(const string a[], int n)
{
    if (n <= 0)       //if we reach the end
        return -1;

    if (n == 1)
        return 0;     //only element = greatest element.

    int MaxIndexOfRest = 1 + locateMaximum(a+1, n-1);

    if (a[0] >= a[MaxIndexOfRest])
        return 0;
    else
        return MaxIndexOfRest;
}


// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 <= 0 && n2 > 0)
        return false;

    if (a1[0] == a2[0])
        return contains(a1+1, n1-1, a2+1, n2-1);
    else
        return contains(a1+1, n1-1, a2, n2);
}

