//
//  ChatTracker.cpp
//  Project 4
//
//  Created by Brian Chang on 6/1/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "ChatTracker.h"
#include <string>
#include <vector>
#include <functional>
using namespace std;

  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets) : maxBuckets(maxBuckets) {};
    
    
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);
    
    unsigned int hasher(const string Hashme);
    
    
    struct Chats
    {
        string chatname;                //name of chat
        int totalContributions;         //total number of contributions
        vector<string> memberUsers;     //vector that stores the names of all the chat's members
    };
    
    struct MemberChats
    {
        string memChatName;             //name of chat
        int userContributionNum;        //number of contributions made by the user
        int chatOrder;                  //order
    };
    
    struct Users
    {
        string username;                //name of user
        vector<MemberChats> memChats;   //chats user is a member of
    };
    

    
  private:
    
    const unsigned int maxBuckets;
    
    vector<Chats*> chatVector;
    vector<Users*> userVector;
    vector<MemberChats*> memChatsVector;
    
    
    struct Info
    {
        Info(string u, string c) : user(u), chat(c), count(0) {}
        string user;
        string chat;
        int count;
    };
    
    
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------HASHTABLE CLASS--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


class HashTable
{
public:
    int BUCKETS;
    vector<string> *table;
    HashTable(int numBuckets);
    
    void addItem(string key);
    void removeItem(string key);
    
    unsigned int hasher(const string Hashme);

};

HashTable::HashTable(int numBuckets)
{
    this->BUCKETS = numBuckets;
    table = new vector<string>[BUCKETS];
    
}

unsigned int HashTable::hasher(const string Hashme)
{
    //using the hash function from the functional library
    std::hash<string> strHash;
    unsigned int hashVal = strHash(Hashme);
    
    unsigned int bucketNum = (hashVal % BUCKETS);
    return bucketNum;
}

void HashTable::addItem(string key)
{
    unsigned int index = hasher(key);
    table[index].push_back(key);
}

void HashTable::removeItem(string key)
{
    unsigned int index = hasher(key);
    
    vector<string>::iterator i;         //creating iterator var 'i'.
    for (i = table[index].begin() ; i < table[index].end() ; i++)
    {
        if (*i == key)
            break;
    }
    
    //now that 'i' is pointing to the target item in the bucketvector
    if (i != table[index].end())
        table[index].erase(i);
}


























//ChatTrackerImpl::ChatTrackerImpl(int /* maxBuckets */)
//{
//    // Since this implementation does not use a hash table, we don't do
//    // anything with the parameter and leave it unnamed so the compiler
//    // doesn't issue a warning about an unused parameter.
//}



