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
#include <cassert>

using namespace std;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//-----------------OBJECT STRUCTS--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//Chat struct that keeps track of chat name, total contributions made to the chat, and it's members.
struct Chats
{
    string m_chatname;                //name of chat
    int totalContributions;           //total number of contributions
    list<string> memberList;            //vector that stores the names of all the chat's members
};

//A member object of the user struct. Keeps track of their unique contributions to a chat.
struct MemberChats
{
    string memChatName;             //name of chat
    int userContributionNum;        //number of contributions made by the user
};

//User struct that has the usersname and list of chats they are associated with.
struct Users
{
    string m_username;                //name of user
    list<MemberChats*> memChatsList;   //chats user is a member of
                                      //the order of the list is the order of the chats. Front = current.
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------CHATS HASHTABLE--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class ChatTable
{
public:
    ChatTable(int maxBuckets);
    ~ChatTable();
    
    unsigned int hasher(const string chatName);
    
    // setters
    void insertChat(string chatName);
    void removeChat(string chatName);
    void addMember(string chatName, string memberName);
    void removeMember(string chatName, string memberName);
    void addContribution(string chatName);
    
    // getters
    int getContributions(string chatName);
    vector<string> getChatMembers(string chatName);
    
    bool chatExists(string chatName);
    
private:
    int BUCKETS;                                  //Assuming 1000 chats, load factor would be 0.5
    vector<list<Chats*>> chatTable;              //chatTable is an array where each element is a list of chats.
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------USERS HASHTABLE--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class UserTable
{
public:
    UserTable(int maxBuckets);
    ~UserTable();
    
    unsigned int hasher(const string userName);
    
    void insertUser(string userName);
    void removeUser(string userName);
    void addMemberChat(string userName, string memberChatName);
    void removeMemberChat(string userName, string memberChatName);
    int addContribution(string userName, string memberChatName);
    
    int leaveCurrentChat(string userName);
    int leaveGivenChat(string userName, string chatName);
    
    int getContributions(string userName, string memberChatName);
    string getCurrentChat(string userName);
    
    bool userExists(string userName);
    
private:
    int BUCKETS;             //Assuming 1000 chats, load factor would be 0.5
    vector<list<Users*>> userTable;              //UserTable is an array where each element is a list of user.
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------CHATTRACKER IMPL-------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets) : maxBuckets(maxBuckets), userTable(maxBuckets), chatTable(maxBuckets) {};
    
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);

  private:
    
    const unsigned int maxBuckets;
    UserTable userTable;
    ChatTable chatTable;
};


void ChatTrackerImpl::join(string user, string chat)
{
    userTable.insertUser(user);
    userTable.addMemberChat(user, chat);
    chatTable.insertChat(chat);
    chatTable.addMember(chat, user);
}

int ChatTrackerImpl::terminate(string chat)
{
    if (chatTable.chatExists(chat) == false)        //if the chat doesnt exist.
        return 0;
    
    //get a list of users.
    vector<string> memberList = chatTable.getChatMembers(chat);

    vector<string>::iterator iter;
    for (iter = memberList.begin(); iter != memberList.end(); iter++)
    {
        userTable.leaveGivenChat(*iter, chat);           //remove memberchats from users.
        chatTable.removeMember(chat, *iter);             //remove all users from the chat.
    }

    int totContributions = chatTable.getContributions(chat);        //get the number of contributions
    chatTable.removeChat(chat);                                     //destroy the chat
    return totContributions;
}

int ChatTrackerImpl::contribute(string user)
{
    string curChatName = userTable.getCurrentChat(user);                        // get the user's current chat
    int contributionNum = userTable.addContribution(user, curChatName);         // increment the users contribution number, store the value
    chatTable.addContribution(curChatName);                                     // increment the chat's total contribution number.
    return contributionNum;                                                     // return the stored value.
}

int ChatTrackerImpl::leave(string user)
{
    string curChatName = userTable.getCurrentChat(user);                    // get the name of users current chat
    int contributionNum = userTable.leaveCurrentChat(user);                 // User leaves chat, get the number of contributions made.
    chatTable.removeMember(curChatName, user);                              // remove user from chat's list of members.
    return contributionNum;                                                 // return contribution num.
}

int ChatTrackerImpl::leave(string user, string chat)
{
    int contributionNum = userTable.leaveGivenChat(user, chat);             //User leaves chat, save contribution num.
    chatTable.removeMember(chat, user);                                     //remove user from chat's list of members.
    return contributionNum;                                                 //return contribution num
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------CHATTABLE IMPLT--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// Constructor
ChatTable::ChatTable(int maxBuckets)
{
    BUCKETS = maxBuckets;
    //list<Chats*> chatTable[BUCKETS];
    
    for (int i = 0; i < BUCKETS; i++)
    {
        list<Chats*> l;
        chatTable.push_back(l);
    }
}

// Destructor
ChatTable::~ChatTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
{
    for (int index = 0; index < BUCKETS; index++)       //for each bucket
    {
        if (!chatTable[index].empty())                  //if list is NOT EMPTY.
        {
            list<Chats*>::iterator i;
            for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)        //delete each chat object within the list.
            {
                delete (*i);
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
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i)->m_chatname) {
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
        Chats* newChat = new Chats;
        //Chats newChat;                             //make a new chat object
        newChat->m_chatname = chatName;             //assign input name as chatname
        chatTable[index].push_back(newChat);      //add chat to chatTable at index.
    }
}


void ChatTable::removeChat(string chatName)
{
    int index = hasher(chatName);
    
    //Does it already exist?
    bool chatExists = false;
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i)->m_chatname)
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
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
    {
        if (chatName == (*i)->m_chatname)                                    //find the correct chat.
        {
            list<string>::iterator it;
            for (it = (*i)->memberList.begin(); it != (*i)->memberList.end(); it++)   //parse the member list
            {
                if ((*it) == memberName)                                            //if member already exist
                    return;                                                         //return.
            }
                                                            //if member doesn't exist.
            (*i)->memberList.push_back(memberName);         //add the user to the member list.
            break;
        }
    }
}



void ChatTable::removeMember(string chatName, string memberName)
{
    if (!chatExists(chatName))          //can't remove a member if chat doesn't exist.
        return;
    
    int index = hasher(chatName);           // Find the index
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
    {
        if (chatName == (*i)->m_chatname)                                    //find the correct chat.
        {
            list<string>::iterator it;
            for (it = (*i)->memberList.begin(); it != (*i)->memberList.end(); it++)   //parse the member list
            {
                if ((*it) == memberName) {                                          //if member exists
                    (*i)->memberList.erase(it);                                      //erase the member.
                    return;
                }
            }
            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
            break;
        }
    }
}


void ChatTable::addContribution(string chatName)
{
    if (!chatExists(chatName))          //Can't add to a non-existent chat.
        return;
    
    int index = hasher(chatName);
    
    list<Chats*>::iterator it;
    for (it = chatTable[index].begin(); it != chatTable[index].end(); it++)
    {
        if ((*it)->m_chatname == chatName)
        {
            (*it)->totalContributions++;
            return;
        }
    }
}


int ChatTable::getContributions(string chatName)
{
    if (chatExists(chatName) == false)              //if chat doesn't exist, return 0.
        return 0;
    
    int index = hasher(chatName);                   //get the bucket
    
    list<Chats*>::iterator it;
    for (it = chatTable[index].begin() ; it != chatTable[index].end(); it++)
    {
        if ((*it)->m_chatname == chatName)
            return (*it)->totalContributions;
    }
    
    //just a catch all
    return 0;
}

vector<string> ChatTable::getChatMembers(string chatName)
{
//    if (!chatExists(chatName))          //can't remove a member if chat doesn't exist.
//        return;
//
    vector<string> memberNames;
    int index = hasher(chatName);           // Find the index
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)    //parse the chat list.
    {
        if (chatName == (*i)->m_chatname)                                    //find the correct chat.
        {
            list<string>::iterator it;
            for (it = (*i)->memberList.begin(); it != (*i)->memberList.end(); it++)   //parse the member list
            {
                memberNames.push_back((*it));
            }
            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
            break;
        }
    }
    return memberNames;
}




//Helper Function
bool ChatTable::chatExists(string chatName)
{
    int index = hasher(chatName);           // Find the index
    bool chatExists = false;                // Create a T/F var, initialised as false.
    
    list<Chats*>::iterator i;
    for (i = chatTable[index].begin(); i != chatTable[index].end(); i++)
    {
        if (chatName == (*i)->m_chatname)       // if the name match, chat exists.
            chatExists = true;                  // set to true.
    }
    return chatExists;
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------USERTABLE IMPLT--------------------
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// Constructor
UserTable::UserTable(int maxBuckets)
{
    BUCKETS = maxBuckets;
    
    for (int i = 0; i < BUCKETS; i++)
    {
        list<Users*> l;
        userTable.push_back(l);
    }
}

// Destructor
UserTable::~UserTable()                     //@@@@@@@@@@@@@@@@@@@@@@ THIS SEEMS SUPER INEFFICIENT @@@@@@@@@@@@@@@@@@@@@@@
{
    for (int index = 0; index < BUCKETS; index++)       //for each bucket
    {
        if (!userTable[index].empty())                  //if list is NOT EMPTY.
        {
            list<Users*>::iterator i;
            for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //delete each user object within the list.
            {
                delete (*i);                //deleteing user objects
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
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i)->m_username) {
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
        Users* newUser = new Users;                   //make a new chat object
        newUser->m_username = userName;             //assign input name as chatname
        userTable[index].push_back(newUser);       //add chat to chatTable at index.
    }
}


void UserTable::removeUser(string userName)
{
    int index = hasher(userName);
    
    //Does it already exist?
    bool userExists = false;
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i)->m_username) {
            userExists = true;
            break;
        }
    }
    
    if(!userExists)
        return;
    
    else if (userExists)
        userTable[index].erase(i);
}


//If memberchat exists, make it the current one (push it to the front of the list).
//If memberchat does NOT exist, create a new one and push front.
void UserTable::addMemberChat(string userName, string memberChatName)
{
    if (!userExists(userName))     //making sure the user even exists.
        return;
    
    int index = hasher(userName);
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i)->m_username)                                        //find the user.
        {
            list<MemberChats*>::iterator iter;
            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, bring chat to front
                {
                    MemberChats *tempMemChat = (*iter);          //store the chat in a temp var.
                    (*i)->memChatsList.erase(iter);              //erase the chat from the list.
                    (*i)->memChatsList.push_front(tempMemChat);  //push this memchat to the front of the list. (front = current)
                    return;
                }
            }
            //add the new memberchat to the memberchat list.
            MemberChats *newMemChat = new MemberChats;           //create new memberchat
            newMemChat->memChatName = memberChatName;            //name it
            (*i)->memChatsList.push_front(newMemChat);           //push front (this is impt)
        }
    }
}


void UserTable::removeMemberChat(string userName, string memberChatName)
{
    if (!userExists(userName))     //making sure the user even exists.
        return;
    
    int index = hasher(userName);
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i)->m_username)                                        //find the user.
        {
            list<MemberChats*>::iterator iter;
            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, return.
                {
                    (*i)->memChatsList.erase(iter);
                    return;
                }
            }
            //@@@@@@@@@@@@@@@@@@@ Should i have some method of saying it didn't work? @@@@@@@@@@@@@@@@@@@@@
            break;

        }
    }
}


int UserTable::addContribution(string userName, string memberChatName)
{
    if (userExists(userName) == false)
        return 0;
    
    if (memberChatName == "")
        return 0;
    
    int index = hasher(userName);
    bool memChatExist = false;
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i)->m_username)                                        //find the user.
        {
            list<MemberChats*>::iterator iter;
            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter)->memChatName                           //if the memberchat already exists
                    && memberChatName == (*i)->memChatsList.front()->memChatName)    //and its the current one.
                {
                    memChatExist = true;
                    (*iter)->userContributionNum++;                                            //increment contribution num
                    return (*iter)->userContributionNum;
                }
            }
            break;
        }
    }
    // we really shouldn't get here.
    return 0;
}

int UserTable::getContributions(string userName, string memberChatName)
{
    if (userExists(userName) == false)
        return 0;
    
    int index = hasher(userName);
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)        //iterate through the list of users
    {
        if (userName == (*i)->m_username)                                        //find the user.
        {
            list<MemberChats*>::iterator iter;
            for (iter = (*i)->memChatsList.begin(); iter != (*i)->memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (memberChatName == (*iter)->memChatName)                                    //if the memberchat already exists, return.
                {
                    return (*iter)->userContributionNum;
                }
            }
            break;
        }
    }
    return 0;
}

string UserTable::getCurrentChat(string userName)
{
    if (userExists(userName) == false)              //no such user
        return "";
    
    int index = hasher(userName);
    
    list<Users*>::iterator it;
    for (it = userTable[index].begin(); it != userTable[index].end(); it++)
    {
        if (userName == (*it)->m_username)
        {
            if ((*it)->memChatsList.empty() == false)
            {
                string chatname = (*it)->memChatsList.front()->memChatName;         //get rid of the front one.
                return chatname;
            }
            else if ((*it)->memChatsList.empty() == true)                        //user has no current, return error.
                return "";
        }
    }
    return "";
}


int UserTable::leaveGivenChat(string userName, string chatName)
{
    if (userExists(userName) == false)              //no such user
        return -1;
    
    int index = hasher(userName);
    
    list<Users*>::iterator it;
    for (it = userTable[index].begin(); it != userTable[index].end(); it++)         //find the correct list
    {
        if (userName == (*it)->m_username)                                          //find the correct user
        {
            list<MemberChats*>::iterator iter;
            for (iter = (*it)->memChatsList.begin(); iter != (*it)->memChatsList.end(); iter++)   //iterate through the memberchat list.
            {
                if (chatName == (*iter)->memChatName)                                    //if the memberchat already exists, return.
                {
                    int contributions = (*iter)->userContributionNum;                   //save the number of contributions
                    (*it)->memChatsList.remove(*iter);                                  //remove the chat
                    return contributions;                                               //return the number of contributions
                }
            }
            break;
        }
    }
    // we shouldnt get here
    return -1;
}



int UserTable::leaveCurrentChat(string userName)
{
    if (userExists(userName) == false)              //no such user
        return -1;
    
    int index = hasher(userName);
    
    list<Users*>::iterator it;
    for (it = userTable[index].begin(); it != userTable[index].end(); it++)
    {
        if (userName == (*it)->m_username)
        {
            if ((*it)->memChatsList.empty() == false)
            {
                int contributions = (*it)->memChatsList.front()->userContributionNum;
                (*it)->memChatsList.remove((*it)->memChatsList.front());         //get rid of the front one.
                return contributions;
            }
            else if ((*it)->memChatsList.empty() == true)                        //user has no current, return error.
                return -1;
        }
    }
    return -1;
}


// Helper Function

bool UserTable::userExists(string userName)
{
    int index = hasher(userName);
    
    //Does it already exist?
    bool userExists = false;
    
    list<Users*>::iterator i;
    for (i = userTable[index].begin(); i != userTable[index].end(); i++)
    {
        if (userName == (*i)->m_username) {
            userExists = true;
            break;
        }
    }
    return userExists;
}
