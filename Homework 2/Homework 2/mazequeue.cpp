//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Brian Chang on 4/28/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <stdio.h>
#include <queue>

using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

