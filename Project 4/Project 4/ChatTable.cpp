//
//  ChatTable.cpp
//  Project 4
//
//  Created by Brian Chang on 6/9/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <stdio.h>
#include "ChatTracker.h"
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>

using namespace std;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------CHATS HASHTABLE--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//Chat struct that keeps track of chat name, total contributions made to the chat, and it's members.
struct Chats
{
    string m_chatname;                //name of chat
    int totalContributions;           //total number of contributions
    list<string> memberList;            //vector that stores the names of all the chat's members
};


class ChatTable
{
public:
    ChatTable();
    ~ChatTable();
    
    unsigned int hasher(const string chatName);
    
    void insertChat(string chatName);
    void removeChat(string chatName);
    void addMember(string chatName, string memberName);
    void removeMember(string chatName, string memberName);
    
    bool chatExists(string chatName);
    
private:
    static const int BUCKETS = 2000;             //Assuming 1000 chats, load factor would be 0.5
    list<Chats> chatTable[BUCKETS];              //chatTable is an array where each element is a list of chats.
};


// Constructor
ChatTable::ChatTable() {}

// Destructor
ChatTable::~ChatTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
{
    for (int index = 0; index < BUCKETS; index++)       //for each bucket
    {
        if (!chatTable[index].empty())                  //if list is NOT EMPTY.
        {
            list<Chats>::iterator i;
            for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)        //delete each chat object within the list.
            {
                //delete (*i);
            }
        }
    }
}

// Hash Fxn
unsigned int ChatTable::hasher(const string chatName)
{
    //using the hash function from the functional library
    std::hash<string> strHash;
    unsigned int hashVal = strHash(chatName);
    unsigned int bucketNum = (hashVal % BUCKETS);
    return bucketNum;
}

// Insert function (Just adds a new chat object to the chat table)
// If it already exists, just return.
// If it doesn't then create a new chat object and insert it.
void ChatTable::insertChat(string chatName)
{
    int index = hasher(chatName);
    
    //Does it already exist?
    bool chatExists = false;
    
    list<Chats>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i).m_chatname) {
            chatExists = true;
            break;
        }
    }
    
    //if it exists
    if (chatExists)
        return;             //@@@@@@@@@@@@@@@@@  What else should it do?  @@@@@@@@@@@@@@@@@@@
    
    // if it doesnt exist,
    // create a new chat and add it to the table.
    else if (!chatExists)
    {
        Chats newChat = Chats();                   //make a new chat object
        newChat.m_chatname = chatName;             //assign input name as chatname
        chatTable[index].push_back(newChat);       //add chat to chatTable at index.
    }
}


void ChatTable::removeChat(string chatName)
{
    int index = hasher(chatName);
    
    //Does it already exist?
    bool chatExists = false;
    
    list<Chats>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i).m_chatname)
        {
            chatExists = true;
            break;                  //so we keep i for later.
        }
    }
    
    if (chatExists)                //get that bitch outta there
    {
        chatTable[index].erase(i);
    }
    
    if (!chatExists)                    //if there's no such chat, just leave it.
        return;
}


void ChatTable::addMember(string chatName, string memberName)
{
    if (!chatExists(chatName))          //can't add a member if chat doesn't exist.
        return;
    
    int index = hasher(chatName);           // Find the index
    
    list<Chats>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
    {
        if (chatName == (*i).m_chatname)                                    //find the correct chat.
        {
            list<string>::iterator it;
            for (it = (*i).memberList.begin(); it != (*i).memberList.end(); it++)   //parse the member list
            {
                if ((*it) == memberName)                                            //if member already exist
                    return;                                                         //return.
            }
                                                           //if member doesn't exist.
            (*i).memberList.push_back(memberName);         //add the user to the member list.
        }
    }
}



void ChatTable::removeMember(string chatName, string memberName)
{
    if (!chatExists(chatName))          //can't add a member if chat doesn't exist.
        return;
    
    int index = hasher(chatName);           // Find the index
    
    list<Chats>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
    {
        if (chatName == (*i).m_chatname)                                    //find the correct chat.
        {
            list<string>::iterator it;
            for (it = (*i).memberList.begin(); it != (*i).memberList.end(); it++)   //parse the member list
            {
                if ((*it) == memberName) {                                          //if member exists
                    (*i).memberList.erase(it);                                      //erase the member.
                    return;
                }
            }
            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
        }
    }
}


//Helper Function
bool ChatTable::chatExists(string chatName)
{
    int index = hasher(chatName);           // Find the index
    bool chatExists = false;                // Create a T/F var, initialised as false.
    
    list<Chats>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i).m_chatname)        // if the name match, chat exists.
            chatExists = true;                  // set to true.
    }
    return chatExists;
}





// test routine

int main()
{
    ChatTable ct;
    ct.insertChat("memes");
    ct.insertChat("dreams");
    ct.insertChat("schemes");
    
    assert(ct.chatExists("memes") == true);
    assert(ct.chatExists("dreams") == true);
    assert(ct.chatExists("schemes") == true);
    
    ct.addMember("memes", "brian");
    ct.addMember("memes", "brian");
    
    
    
    
    
    cout << "Passed all tests!" << endl;
}
