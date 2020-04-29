//
//  main.cpp
//  jk
//
//  Created by Brian Chang on 4/27/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <iostream>
#include<string>

using namespace std;

class StringList
{
  public:
    void insertAfterEach(char c);
  private:
    struct Node
    {
      char  value;
      Node* next;
    };
    Node* head;  // points to first Node in the list
};

void StringList::insertAfterEach(char c)
{
   if (head == nullptr) //if no nodes in list, return.
      return;
   
   Node* cur = head;
   while (cur != nullptr)
   {
      Node* insertNode = new Node;      //create insert node.
      insertNode->value = c;            //storing value.
      insertNode->next = cur->next;     //linking insNode to cur->next node.
      Node* temp = cur->next;           //storing original cur->next.
      cur->next = insertNode;           //linking cur node to insert node.
      cur = temp;                       //advancing cur node, skipping insert node.
   }
   return;
}

int main()
{
    
}
