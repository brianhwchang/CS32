//
//  main.cpp
//  jk
//
//  Created by Brian Chang on 4/27/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <iostream>
#include<string>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
    int   data;
    Node* child[3];
};

int countLessers(const Node* p)
{
    const Node* cur = p;            //creating a pointer that points to the current node.
    
    if (cur == nullptr)             //base case. If the cur nodes points to a nullptr, its the end of the tree, return.
        return 0;
    
    bool isLesser = false;          //bool to indicate whether cur node is lesser.
    
    for (int i = 0; i < 3; i++)     //checking all child nodes.
    {
        if (cur->child[i] != nullptr)
        {
            if (cur->data < cur->child[i]->data)
            {
                isLesser = true;    //since it is lesser, set bool to true.
                break;              //if any of the child nodes are lesser, cur is a lesser node. break.
            }
        }
    }
    return isLesser + countLessers(cur->child[0]) + countLessers(cur->child[1]) + countLessers(cur->child[2]);
}

//int countLessers(const Node* p)
//{
//    const Node* cur = p;            //creating a pointer that points to the current node.
//
//    if (cur == nullptr)             //base case. If the cur nodes points to a nullptr, its the end of the tree, return.
//        return 0;
//
//
//
//    for (int i = 0; i < 3; i++)
//    {
//        if (cur->child[i] != nullptr)
//            countLessers(cur->child[i]);
//
//        if (cur->data < cur->child[i]->data)
//            return 1;
//    }
//
//    int counter = 0;
//
//
////    for (int i = 0; i < 3; i++)
////    {
////        if (cur->child[i] != nullptr)
////        {
////            countLessers(cur->child[i]);            //enter recursive loop
////
////            if (cur->data < cur->child[i]->data)    //if cur is a lesser node, return 1.
////                return 1;
////            else                                    //if cur isnt a lesser node, return 0.
////                return 0;
////        }
////    }
//
////    for (int i = 0; i < 3; i++)
////    {
////        if (cur->child[i] != nullptr)
////        {
////            if (cur->data < cur->child[i]->data)
////                counter++;
////        }
////    }
////
//    return counter + countLessers(cur->child[0]) + countLessers(cur->child[1]) + countLessers(cur->child[2]);
//}


Node* makeNode(int d)
{
     Node* p = new Node;
     p->data = d;
     for (int k = 0; k < 3; k++)
         p->child[k] = nullptr;
     return p;
}


int main()
{
      // Build the 3-tree pictured in the problem as an example

    Node* n8 = makeNode(8);
    n8->child[2] = makeNode(3);
 
    Node* n2 = makeNode(2);
    n2->child[1] = n8;
     
    Node* n5 = makeNode(5);
    n5->child[0] = makeNode(8);
    n5->child[2] = makeNode(9);
     
    Node* n7 = makeNode(7);
    n7->child[1] = n5;
 
    Node* root = makeNode(4);
    root->child[0] = n2;
    root->child[1] = makeNode(1);
    root->child[2] = n7;
    
      // Test countLessers with that tree
 
    assert(countLessers(root) == 3);
    assert(countLessers(root->child[2]) == 1);
    assert(countLessers(nullptr) == 0);
    assert(countLessers(n8) == 0);
    cout << "All tests succeeded" << endl;

      // Clean up the tree

    delete n8->child[2];
    delete n8;
    delete n2;
    delete root->child[1];
    delete n5->child[0];
    delete n5->child[2];
    delete n5;
    delete n7;
    delete root;
}
