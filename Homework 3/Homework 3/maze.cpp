//
//  maze.cpp
//  Homework 3
//
//  Created by Brian Chang on 5/6/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cassert>

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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    
    if (sr == er && sc == ec)           //return true if we're at the end (hence found a path)
        return true;
    
    int row = sr;
    int col = sc;
    maze[sr][sc] = '#';                 //marking starting point as discovered/explored.

    //Check NORTH.
    if (maze[row-1][col] != 'X' && maze[row-1][col] != '#')
    {
        if (pathExists(maze, sr-1, sc, er, ec))
            return true;
    }
    
    //Check SOUTH
    if (maze[row+1][col] != 'X' && maze[row+1][col] != '#')
    {
        if (pathExists(maze, sr+1, sc, er, ec))
            return true;
    }
    
    //Check EAST.
    if (maze[row][col+1] != 'X' && maze[row][col+1] != '#')
    {
        if (pathExists(maze, sr, sc+1, er, ec))
            return true;
    }
    
    //Check WEST.
    if (maze[row][col-1] != 'X' && maze[row][col-1] != '#')
    {
        if (pathExists(maze, sr, sc-1, er, ec))
            return true;
    }
    
    return false;       //no path found
}


//int main()
//{
//    char maze[10][10] = {
//
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','X','.','X','.','.','.','X' },
//        { 'X','.','X','X','.','X','X','.','.','X' },
//        { 'X','.','X','.','.','.','.','.','.','X' },
//        { 'X','.','X','X','X','.','X','X','.','X' },
//        { 'X','.','X','.','.','.','X','.','.','X' },
//        { 'X','.','.','.','X','.','X','.','.','X' },
//        { 'X','X','X','X','X','.','X','.','X','X' },
//        { 'X','.','.','.','.','.','X','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(maze, 1,1, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
