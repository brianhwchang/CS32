////
////  UserTable.cpp
////  Project 4
////
////  Created by Brian Chang on 6/9/20.
////  Copyright © 2020 Brian Chang. All rights reserved.
////
//
//#include <stdio.h>
//#include "ChatTracker.h"
//#include <string>
//#include <list>
//#include <vector>
//#include <functional>
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//// STRUCTS
//
////A user's list of chats that they're in.
//struct MemberChats
//{
//    string memChatName;             //name of chat
//    int userContributionNum = 0;    //number of contributions made by the user
//};
//
////User struct.
//struct Users
//{
//    string m_username;                //name of user
//    list<MemberChats*> memChatsList;   //chats user is a member of
//    //the order of the list is the order of the chats
//};
//
//
//
////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
////----------------USERS HASHTABLE--------------------
////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//
//class UserTable
//{
//public:
//    UserTable(int maxBuckets);
//    ~UserTable();
//    
//    unsigned int hasher(const string userName);
//    
//    void insertUser(string userName);
//    void removeUser(string userName);
//    void addMemberChat(string userName, string memberChatName);
//    void removeMemberChat(string userName, string memberChatName);
//    void addContribution(string userName, string memberChatName);
//    int leaveCurrentChat(string userName);
//    
//    int getContributions(string userName, string memberChatName);
//    int getCurrentChat(string userName);
//    
//    bool userExists(string userName);
//    
//private:
//    int BUCKETS;             //Assuming 1000 chats, load factor would be 0.5
//    vector<list<Users*>> userTable;              //UserTable is an array where each element is a list of user.
//};
//
//
//// Constructor
//UserTable::UserTable(int maxBuckets)
//{
//    BUCKETS = maxBuckets;
//    
//    for (int i = 0; i < BUCKETS; i++)
//    {
//        list<Users*> l;
//        userTable.push_back(l);
//    }
//}
//
//// Destructor
//UserTable::~UserTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
//{
//    for (int index = 0; index < BUCKETS; index++)       //for each bucket
//    {
//        if (!userTable[index].empty())                  //if list is NOT EMPTY.
//        {
//            list<Users*>::iterator i;
//            for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //delete each user object within the list.
//            {
//                delete (*i);                //deleteing user objects
//            }
//        }
//    }
//}
//
//// Hash Fxn
//unsigned int UserTable::hasher(const string userName)
//{
//    //using the hash function from the functional library
//    std::hash<string> strHash;
//    unsigned int hashVal = strHash(userName);
//    unsigned int bucketNum = (hashVal % BUCKETS);
//    return bucketNum;
//}
//
//
//// Insert function (Just adds a new user object to the user table)
//// If it already exists, just return.
//// If it doesn't then create a new user object and insert it.
//void UserTable::insertUser(string userName)
//{
//    int index = hasher(userName);
//    
//    //Does it already exist?
//    bool userExists = false;
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
//    {
//        if (userName == (*i)->m_username) {
//            userExists = true;
//            break;
//        }
//    }
//    
//    //if it exists
//    if (userExists)
//        return;             //@@@@@@@@@@@@@@@@@  What else should it do?  @@@@@@@@@@@@@@@@@@@
//    
//    // if it doesnt exist,
//    // create a new chat and add it to the table.
//    else if (!userExists)
//    {
//        Users* newUser = new Users;                   //make a new chat object
//        newUser->m_username = userName;             //assign input name as chatname
//        userTable[index].push_back(newUser);       //add chat to chatTable at index.
//    }
//}
//
//
//void UserTable::removeUser(string userName)
//{
//    int index = hasher(userName);
//    
//    //Does it already exist?
//    bool userExists = false;
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
//    {
//        if (userName == (*i)->m_username) {
//            userExists = true;
//            break;
//        }
//    }
//    
//    if(!userExists)
//        return;
//    
//    else if (userExists)
//        userTable[index].erase(i);
//}
//
//
////If memberchat exists, make it the current one (push it to the front of the list).
////If memberchat does NOT exist, create a new one and push front.
//void UserTable::addMemberChat(string userName, string memberChatName)
//{
//    if (!userExists(userName))     //making sure the user even exists.
//        return;
//    
//    int index = hasher(userName);
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
//    {
//        if (userName == (*i)->m_username)                                        //find the user.
//        {
//            list<MemberChats*>::iterator iter;
//            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
//            {
//                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, bring chat to front
//                {
//                    MemberChats *tempMemChat = (*iter);          //store the chat in a temp var.
//                    (*i)->memChatsList.erase(iter);              //erase the chat from the list.
//                    (*i)->memChatsList.push_front(tempMemChat);  //push this memchat to the front of the list. (front = current)
//                    return;
//                }
//            }
//            //add the new memberchat to the memberchat list.
//            MemberChats *newMemChat = new MemberChats;           //create new memberchat
//            newMemChat->memChatName = memberChatName;            //name it
//            (*i)->memChatsList.push_front(newMemChat);           //push front (this is impt)
//        }
//    }
//}
//
//
//
//
//
//
//void UserTable::removeMemberChat(string userName, string memberChatName)
//{
//    if (!userExists(userName))     //making sure the user even exists.
//        return;
//    
//    int index = hasher(userName);
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
//    {
//        if (userName == (*i)->m_username)                                        //find the user.
//        {
//            list<MemberChats*>::iterator iter;
//            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
//            {
//                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, return.
//                {
//                    (*i)->memChatsList.erase(iter);
//                    return;
//                }
//            }
//            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
//            break;
//
//        }
//    }
//}
//
//
//void UserTable::addContribution(string userName, string memberChatName)
//{
//    if (userExists(userName) == false)
//        return;
//    
//    int index = hasher(userName);
//    bool memChatExist = false;
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
//    {
//        if (userName == (*i)->m_username)                                        //find the user.
//        {
//            list<MemberChats*>::iterator iter;
//            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
//            {
//                if (memberChatName == (*iter)->memChatName                           //if the memberchat already exists
//                    && memberChatName == (*i)->memChatsList.front()->memChatName)    //and its the current one.
//                {
//                    memChatExist = true;
//                    (*iter)->userContributionNum++;                                            //increment contribution num
//                }
//            }
////            //if it DOES NOT exist, add the new memberchat to the memberchat list.
////            MemberChats *newMemChat = new MemberChats;           //create new memberchat
////            newMemChat->memChatName = memberChatName;            //name it
////            (*i)->memChatsList.push_front(newMemChat);           //push front (this is impt)
////            (*i)->memChatsList.front()->userContributionNum++;   //add a contribution
//            break;
//        }
//    }
//}
//
//int UserTable::getContributions(string userName, string memberChatName)
//{
//    if (userExists(userName) == false)
//        return 0;
//    
//    int index = hasher(userName);
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
//    {
//        if (userName == (*i)->m_username)                                        //find the user.
//        {
//            list<MemberChats*>::iterator iter;
//            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
//            {
//                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, return.
//                {
//                    return (*iter)->userContributionNum;
//                }
//            }
//            break;
//        }
//    }
//    return 0;
//}
//
//
//int UserTable::leaveCurrentChat(string userName)
//{
//    if (userExists(userName) == false)              //no such user
//        return -1;
//    
//    int index = hasher(userName);
//    
//    list<Users*>::iterator it;
//    for (it = userTable[index].begin(); it != userTable[index].end(); it++)
//    {
//        if (userName == (*it)->m_username)
//        {
//            if ((*it)->memChatsList.empty() == false)
//            {
//                int contributions = (*it)->memChatsList.front()->userContributionNum;
//                (*it)->memChatsList.remove((*it)->memChatsList.front());         //get rid of the front one.
//                return contributions;
//            }
//            else if ((*it)->memChatsList.empty() == true)                        //user has no current, return error.
//                return -1;
//        }
//    }
//    return -1;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//// Helper Function
//
//bool UserTable::userExists(string userName)
//{
//    int index = hasher(userName);
//    
//    //Does it already exist?
//    bool userExists = false;
//    
//    list<Users*>::iterator i;
//    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
//    {
//        if (userName == (*i)->m_username) {
//            userExists = true;
//            break;
//        }
//    }
//    return userExists;
//}
//
//
//int main()
//{
//    UserTable ut(10);
//    
//    ut.insertUser("brian");
//    ut.insertUser("ando");
//    ut.insertUser("nes");
//    
//    assert(ut.userExists("brian"));
//    assert(ut.userExists("ando"));
//    assert(ut.userExists("nes"));
//    
//    ut.removeUser("nes");
//    assert(ut.userExists("nes") == false);
//    
//    ut.addMemberChat("brian", "running");
//    ut.addContribution("brian", "running");
//    ut.addMemberChat("brian", "swimming");
//    ut.addMemberChat("ando", "lifting");
//    
////    ut.removeMemberChat("brian", "running");
////    ut.removeMemberChat("brian", "running");
// //   ut.removeMemberChat("ando", "lifting");
//    
////    ut.addContribution("brian", "running");
////    assert(ut.getContributions("brian", "running") == 0);
//    assert(ut.getContributions("brian", "swimming") == 0);
//    ut.addContribution("brian", "swimming");
//    assert(ut.getContributions("brian", "swimming") == 1);
//    ut.addContribution("brian", "swimming");
//    assert(ut.getContributions("brian", "swimming") == 2);
//    ut.addContribution("ando", "lifting");
//    assert(ut.getContributions("ando", "lifting") == 1);
//    assert(ut.leaveCurrentChat("ando") == 1);
//    assert(ut.leaveCurrentChat("brian") == 2);
//    assert(ut.leaveCurrentChat("brian") == 1);
//    
//    
//    cout << "Passed all tests! :)" << endl;
//}
