//
//  main.cpp
//  CS32 Final
//
//  Created by Brian Chang on 6/7/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cassert>

using namespace std;

int fib(int N)
{
    if (N == 0 || N == 1)
        return 1;
    
    return fib(N-1) + fib(N-2);
}





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-------------MAIN ROUTINE---------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main()
{
    int a[10];
    
    for (int j = 1; j < 8; j++)
    {
       const int v = a[j];   // breakpoint
       int k;
       for (k = j; k > 0  &&  v < a[k-1]; k--)
          a[k] = a[k-1];
       a[k] = v;
    }
    
    for (int i=0; i < 10 ; i++)
        cout << a[i] <<endl;
}

