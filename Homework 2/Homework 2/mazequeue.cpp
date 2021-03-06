//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Brian Chang on 4/28/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//
//
//#include <stdio.h>
//#include <iostream>
//#include <queue>
//
//using namespace std;
//
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
//// Return true if there is a path from (sr,sc) to (er,ec)
//// through the maze; return false otherwise
//
//class Coord
//{
//  public:
//    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//  private:
//    int m_row;
//    int m_col;
//};
//
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
//{
//    queue<Coord> coordQueue;            //Creating a queue of coordinates.
//    coordQueue.push(Coord(sr, sc));     //Enqueing starting coordinates.
//    maze[sr][sc] = '#';                 //marking starting coord as "discovered".
//
//    while (!coordQueue.empty())
//    {
//        Coord cur = coordQueue.front();     //assinging front coord to var current.
//        int row = cur.r();                  //creating a var to hold current row index.
//        int col = cur.c();                  //creating a var to hold current col index.
//        coordQueue.pop();                   //dequeue-ing front var.
//
//        if (row == er && col == ec)         //If we reach the end point, return true.
//            return true;
//
//        else
//        {
//            //Check SOUTH
//            if (row+1 < 9 && maze[row+1][col] != 'X' && maze[row+1][col] != '#')
//            {
//                coordQueue.push(Coord(row+1, col));     //enque coordinate
//                maze[row+1][col] = '#';                 //update maze
//            }
//            //Check WEST
//            if (col-1 > 0 && maze[row][col-1] != 'X' && maze[row][col-1] != '#')
//            {
//                coordQueue.push(Coord(row, col-1));     //enque coordinate
//                maze[row][col-1] = '#';                 //update maze
//            }
//            //Check NORTH
//            if (row-1 > 0 && maze[row-1][col] != 'X' && maze[row-1][col] != '#')
//            {
//                coordQueue.push(Coord(row-1, col));     //enque coordinate
//                maze[row-1][col] = '#';                 //update maze
//            }
//            //Check EAST
//            if (col+1 > 0 && maze[row][col+1] != 'X' && maze[row][col+1] != '#')
//            {
//                coordQueue.push(Coord(row, col+1));     //enque coordinate
//                maze[row][col+1] = '#';                 //update maze
//            }
//        }
//    }
//    return false; //No solution found.
//}
//
//
//int main()
//{
//    char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','.','X','.','.','.','X' },
//        { 'X','.','X','X','.','X','X','.','.','X' },
//        { 'X','X','X','.','.','.','.','X','.','X' },
//        { 'X','.','X','X','X','.','X','X','X','X' },
//        { 'X','.','X','.','.','.','X','.','.','X' },
//        { 'X','.','.','.','X','.','X','.','.','X' },
//        { 'X','X','X','X','X','.','X','.','X','X' },
//        { 'X','.','.','.','.','.','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(maze, 3,5, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
