//
//  ChatTracker.cpp
//  Project 4
//
//  Created by Brian Chang on 6/1/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "ChatTracker.h"
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-----------------OBJECT STRUCTS--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//
////Chat struct that keeps track of chat name, total contributions made to the chat, and it's members.
//struct Chats
//{
//    string m_chatname;                //name of chat
//    int totalContributions;           //total number of contributions
//    list<string> memberList;            //vector that stores the names of all the chat's members
//};

////A user's list of chats that they're in.
//struct MemberChats
//{
//    string memChatName;             //name of chat
//    int userContributionNum;        //number of contributions made by the user
//};
//
////User struct.
//struct Users
//{
//    string m_username;                //name of user
//    list<MemberChats> memChatsList;   //chats user is a member of
//    //the order of the list is the order of the chats
//};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------CHATTRACKER IMPL-------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


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

  private:
    
    const unsigned int maxBuckets;
    
    struct Info
    {
        Info(string u, string c) : user(u), chat(c), count(0) {}
        string user;
        string chat;
        int count;
    };
    
};
//
//
////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
////----------------CHATS HASHTABLE--------------------
////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//
////Chat struct that keeps track of chat name, total contributions made to the chat, and it's members.
//struct Chats
//{
//    string m_chatname;                //name of chat
//    int totalContributions;           //total number of contributions
//    list<string> memberList;            //vector that stores the names of all the chat's members
//};
//
//
//class ChatTable
//{
//public:
//    ChatTable();
//    ~ChatTable();
//    
//    unsigned int hasher(const string chatName);
//    
//    void insertChat(string chatName);
//    void removeChat(string chatName);
//    void addMember(string chatName, string memberName);
//    void removeMember(string chatName, string memberName);
//    
//    bool chatExists(string chatName);
//    
//private:
//    static const int BUCKETS = 2000;             //Assuming 1000 chats, load factor would be 0.5
//    list<Chats> chatTable[BUCKETS];              //chatTable is an array where each element is a list of chats.
//};
//
//
//// Constructor
//ChatTable::ChatTable() {}
//
//// Destructor
//ChatTable::~ChatTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
//{
//    for (int index = 0; index < BUCKETS; index++)       //for each bucket
//    {
//        if (!chatTable[index].empty())                  //if list is NOT EMPTY.
//        {
//            list<Chats>::iterator i;
//            for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)        //delete each chat object within the list.
//            {
//                //delete (*i);
//            }
//        }
//    }
//}
//
//// Hash Fxn
//unsigned int ChatTable::hasher(const string chatName)
//{
//    //using the hash function from the functional library
//    std::hash<string> strHash;
//    unsigned int hashVal = strHash(chatName);
//    unsigned int bucketNum = (hashVal % BUCKETS);
//    return bucketNum;
//}
//
//// Insert function (Just adds a new chat object to the chat table)
//// If it already exists, just return.
//// If it doesn't then create a new chat object and insert it.
//void ChatTable::insertChat(string chatName)
//{
//    int index = hasher(chatName);
//    
//    //Does it already exist?
//    bool chatExists = false;
//    
//    list<Chats>::iterator i;
//    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
//    {
//        if (chatName == (*i).m_chatname)
//            chatExists = true;
//    }
//    
//    //if it exists
//    if (chatExists)
//        return;             //@@@@@@@@@@@@@@@@@  What else should it do?  @@@@@@@@@@@@@@@@@@@
//    
//    // if it doesnt exist,
//    // create a new chat and add it to the table.
//    else if (!chatExists)
//    {
//        Chats newChat = Chats();                   //make a new chat object
//        newChat.m_chatname = chatName;             //assign input name as chatname
//        chatTable[index].push_back(newChat);       //add chat to chatTable at index.
//    }
//}
//
//
//void ChatTable::removeChat(string chatName)
//{
//    int index = hasher(chatName);
//    
//    //Does it already exist?
//    bool chatExists = false;
//    
//    list<Chats>::iterator i;
//    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
//    {
//        if (chatName == (*i).m_chatname)
//        {
//            chatExists = true;
//            break;                  //so we keep i for later.
//        }
//    }
//    
//    if (chatExists)                //get that bitch outta there
//    {
//        chatTable[index].erase(i);
//    }
//    
//    if (!chatExists)                    //if there's no such chat, just leave it.
//        return;
//}
//
//
//void ChatTable::addMember(string chatName, string memberName)
//{
//    if (!chatExists(chatName))          //can't add a member if chat doesn't exist.
//        return;
//    
//    int index = hasher(chatName);           // Find the index
//    
//    list<Chats>::iterator i;
//    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
//    {
//        if (chatName == (*i).m_chatname)                                    //find the correct chat.
//        {
//            list<string>::iterator it;
//            for (it = (*i).memberList.begin(); it != (*i).memberList.end(); it++)   //parse the member list
//            {
//                if ((*it) == memberName)                                            //if member already exist
//                    return;                                                         //return.
//            }
//                                                           //if member doesn't exist.
//            (*i).memberList.push_back(memberName);         //add the user to the member list.
//        }
//    }
//}
//
//
//void ChatTable::removeMember(string chatName, string memberName)
//{
//    if (!chatExists(chatName))          //can't add a member if chat doesn't exist.
//        return;
//    
//    int index = hasher(chatName);           // Find the index
//    
//    list<Chats>::iterator i;
//    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
//    {
//        if (chatName == (*i).m_chatname)                                    //find the correct chat.
//        {
//            list<string>::iterator it;
//            for (it = (*i).memberList.begin(); it != (*i).memberList.end(); it++)   //parse the member list
//            {
//                if ((*it) == memberName) {                                          //if member exists
//                    (*i).memberList.erase(it);                                      //erase the member.
//                    return;
//                }
//            }
//            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
//        }
//    }
//}
//
//
////Helper Function
//bool ChatTable::chatExists(string chatName)
//{
//    int index = hasher(chatName);           // Find the index
//    bool chatExists = false;                // Create a T/F var, initialised as false.
//    
//    list<Chats>::iterator i;
//    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
//    {
//        if (chatName == (*i).m_chatname)        // if the name match, chat exists.
//            chatExists = true;                  // set to true.
//    }
//    return chatExists;
//}



// to test


//// Driver program
//int main()
//{
//  // array that contains keys to be mapped
//  string a[] = {"brian", "brian", "alissa", "Jill", "connor", "Aly"};
//  int n = sizeof(a)/sizeof(a[0]);
//
//  // insert the keys into the hash table
//  HashTable h(7);   // 7 is count of buckets in
//               // hash table
//  for (int i = 0; i < n; i++)
//    h.addItem(a[i]);
//
//  // delete 12 from hash table
//  h.removeItem("Aly");
//
//  // display the Hash table
//  h.displayHash();
//
//  return 0;
//}








/*
joinfxn()
{
    if not already in Chats
        //blah blah
    if memberchat already exists.
        //remove memberchat from memchatvect and store in temp var
        //push back to "top" of vect
        
}
*/



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------HASHTABLE CLASS--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


class HashTable
{
public:
    int BUCKETS;           //Number of buckets in our table.
    vector<string> *table;
    
    HashTable(int numBuckets);
    
    bool isEmpty();
    void insertItem(string key);
    void removeItem(string key);
    void displayHash();
    
    unsigned int hasher(const string Hashme);

};

HashTable::HashTable(int numBuckets)
{
    this->BUCKETS = numBuckets;
    table = new vector<string>[BUCKETS];
    
}

//trivial fxn to check if table is empty.
bool HashTable::isEmpty()
{
    int sum = 0;
    for (int i = 0; i < BUCKETS; i++)
        sum += table[i].size();
    
    if (sum == 0) {return true;}
    else {return false;}
}


unsigned int HashTable::hasher(const string Hashme)
{
    //using the hash function from the functional library
    std::hash<string> strHash;
    unsigned int hashVal = strHash(Hashme);
    
    unsigned int bucketNum = (hashVal % BUCKETS);
    return bucketNum;
}


void HashTable::insertItem(string key)
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

// function to display hash table
void HashTable::displayHash()
{
  for (int i = 0; i < BUCKETS; i++) {
    cout << i;
    for (auto x : table[i])
      cout << " --> " << x;
    cout << endl;
  }
}
