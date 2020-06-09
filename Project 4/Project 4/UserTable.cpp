//
//  UserTable.cpp
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

using namespace std;

// STRUCTS

//A user's list of chats that they're in.
struct MemberChats
{
    string memChatName;             //name of chat
    int userContributionNum;        //number of contributions made by the user
};

//User struct.
struct Users
{
    string m_username;                //name of user
    list<MemberChats> memChatsList;   //chats user is a member of
    //the order of the list is the order of the chats
};



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------USERS HASHTABLE--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



class UserTable
{
public:
    UserTable();
    ~UserTable();
    
    unsigned int hasher(const string userName);
    
    void insertUser(string userName);
    void removeUser(string userName);
    void addMemberChat(string userName, string memberChatName);
    void removeMemberChat(string userName, string memberChatName);
    
    bool userExists(string userName);
    
private:
    static const int BUCKETS = 20000;             //Assuming 1000 chats, load factor would be 0.5
    list<Users> userTable[BUCKETS];              //UserTable is an array where each element is a list of user.
};


// Constructor
UserTable::UserTable() {}

// Destructor
UserTable::~UserTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
{
    for (int index = 0; index < BUCKETS; index++)       //for each bucket
    {
        if (!userTable[index].empty())                  //if list is NOT EMPTY.
        {
            list<Users>::iterator i;
            for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //delete each chat object within the list.
            {
                //delete (*i);
            }
        }
    }
}

// Hash Fxn
unsigned int UserTable::hasher(const string userName)
{
    //using the hash function from the functional library
    std::hash<string> strHash;
    unsigned int hashVal = strHash(userName);
    unsigned int bucketNum = (hashVal % BUCKETS);
    return bucketNum;
}


// Insert function (Just adds a new user object to the user table)
// If it already exists, just return.
// If it doesn't then create a new user object and insert it.
void UserTable::insertUser(string userName)
{
    int index = hasher(userName);
    
    //Does it already exist?
    bool userExists = false;
    
    list<Users>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i).m_username) {
            userExists = true;
            break;
        }
    }
    
    //if it exists
    if (userExists)
        return;             //@@@@@@@@@@@@@@@@@  What else should it do?  @@@@@@@@@@@@@@@@@@@
    
    // if it doesnt exist,
    // create a new chat and add it to the table.
    else if (!userExists)
    {
        Users newUser = Users();                   //make a new chat object
        newUser.m_username = userName;             //assign input name as chatname
        userTable[index].push_back(newUser);       //add chat to chatTable at index.
    }
}


void UserTable::removeUser(string userName)
{
    int index = hasher(userName);
    
    //Does it already exist?
    bool userExists = false;
    
    list<Users>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i).m_username) {
            userExists = true;
            break;
        }
    }
    
    if(!userExists)
        return;
    
    else if (userExists)
        userTable[index].erase(i);
}


void UserTable::addMemberChat(string userName, string memberChatName)
{
    if (!userExists(userName))     //making sure the user even exists.
        return;
    
    int index = hasher(userName);
    
    list<Users>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i).m_username)                                        //find the user.
        {
            list<MemberChats>::iterator iter;
            for (iter = (*i).memChatsList.begin(); iter != (*i).memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter).memChatName)                                    //if the memberchat already exists, bring chat to front
                {
                    MemberChats tempMemChat = (*iter);          //store the chat in a temp var.
                    (*i).memChatsList.erase(iter);              //erase the chat from the list.
                    (*i).memChatsList.push_front(tempMemChat);  //push this memchat to the front of the list. (front = current)
                    return;
                }
            }
            
            //add the new memberchat to the memberchat list.
            MemberChats newMemChat = MemberChats();             //create new memberchat
            newMemChat.memChatName = memberChatName;            //name it
            (*i).memChatsList.push_front(newMemChat);           //push front (this is impt)
        }
    }
}






void UserTable::removeMemberChat(string userName, string memberChatName)
{
    if (!userExists(userName))     //making sure the user even exists.
        return;
    
    int index = hasher(userName);
    
    list<Users>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i).m_username)                                        //find the user.
        {
            list<MemberChats>::iterator iter;
            for (iter = (*i).memChatsList.begin(); iter != (*i).memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter).memChatName)                                    //if the memberchat already exists, return.
                {
                    (*i).memChatsList.erase(iter);
                    return;
                }
            }
            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
        }
    }
}


// Helper Function

bool UserTable::userExists(string userName)
{
    int index = hasher(userName);
    
    //Does it already exist?
    bool userExists = false;
    
    list<Users>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i).m_username) {
            userExists = true;
            break;
        }
    }
    return userExists;
}
