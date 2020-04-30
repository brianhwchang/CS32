//
//  mazestack.cpp
//  Homework 2
//
//  Created by Brian Chang on 4/28/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
//
#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

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
    stack<Coord> coordStack;            //Creating a stack of coordinates.
    coordStack.push(Coord(sr, sc));     //Pushing starting coordinates.
    maze[sr][sc] = '#';                 //marking starting coord as "discovered".

    while (!coordStack.empty())         //creating a loop that runs as long as stack isn't empty
    {
        Coord cur = coordStack.top();   //Assigning top stack value to variable cur.
        coordStack.pop();               //Getting rid of it.

        if (cur.r() == er && cur.c() == ec)     //if the current position == end position
            return true;                        //return true

        else
        {
            //Check SOUTH.
            if (cur.r()+1 < 9 && maze[cur.r()+1][cur.c()] != 'X' && maze[cur.r()+1][cur.c()] != '#')  //If coordinate is in range, is not a wall, and hasn't been discovered.
            {
                coordStack.push(Coord(cur.r()+1, cur.c()));         //Push discovered coord to stack
                maze[cur.r()+1][cur.c()] = '#';                     //Update Maze
            }
            //Check WEST.
            if (cur.c()-1 > 0 && maze[cur.r()][cur.c()-1] != 'X' && maze[cur.r()][cur.c()-1] != 'X')    //If coordinate is in range, is not a wall, and hasn't been discovered.
            {
                coordStack.push(Coord(cur.r(), cur.c()-1));         //Push discovered coord to stack
                maze[cur.r()][cur.c()-1] = '#';                     //Update Maze
            }
            //Check NORTH.
            if (cur.r()-1 > 0 && maze[cur.r()-1][cur.c()] != 'X' && maze[cur.r()-1][cur.c()] != '#')   //If coordinate is in range, is not a wall, and hasn't been discovered.
            {
                coordStack.push(Coord(cur.r()-1, cur.c()));         //Push discovered coord to stack
                maze[cur.r()-1][cur.c()] = '#';                     //Update maze
            }
            //Check EAST.
            if (cur.c()+1 < 9 && maze[cur.r()][cur.c()+1] != 'X' && maze[cur.r()][cur.c()+1] != '#')   //If coordinate is in range, is not a wall, and hasn't been discovered.
            {
                coordStack.push(Coord(cur.r(), cur.c()+1));         //Push discovered coord to stack
                maze[cur.r()][cur.c()+1] = '#';                     //Update maze
            }
        }
    }
    return false;                       //There was no solution, so return false
}


//Test routine
int main()
{   //Positive test case.
    char maze[10][10] = {
        // 0   1   2   3   4   5   6   7   8   9
        { 'X','X','X','X','X','X','X','X','X','X'}, //0
        { 'X','.','.','.','.','.','.','.','.','X'}, //1
        { 'X','X','.','X','.','X','X','X','.','X'}, //2
        { 'X','.','.','X','.','X','.','.','.','X'}, //3
        { 'X','.','.','X','.','.','.','.','.','X'}, //4
        { 'X','X','X','X','.','X','X','X','.','X'}, //5
        { 'X','.','X','.','.','.','.','X','X','X'}, //6
        { 'X','.','.','X','X','.','X','.','.','X'}, //7
        { 'X','.','.','.','X','.','.','.','.','X'}, //8
        { 'X','X','X','X','X','X','X','X','X','X'}  //9
    };

    if (pathExists(maze, 2,2, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

    //Negative test case
    char maze2[10][10] = {
        // 0   1   2   3   4   5   6   7   8   9
        { 'X','X','X','X','X','X','X','X','X','X'}, //0
        { 'X','.','.','X','.','.','.','.','.','X'}, //1
        { 'X','X','.','X','.','X','X','X','X','X'}, //2
        { 'X','.','.','X','.','X','.','.','.','X'}, //3
        { 'X','.','.','.','.','X','.','.','.','X'}, //4
        { 'X','X','X','X','X','X','.','X','.','X'}, //5
        { 'X','.','.','X','.','.','.','X','.','X'}, //6
        { 'X','.','.','X','.','.','.','X','.','X'}, //7
        { 'X','.','.','X','.','.','.','X','.','X'}, //8
        { 'X','X','X','X','X','X','X','X','X','X'}  //9
    };

    if (pathExists(maze2, 1,1, 8,8)) // why does this work?
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

    return 0;
}

