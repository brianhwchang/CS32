//
//  main.cpp
//  Homework 3
//
//  Created by Brian Chang on 5/5/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//Every Animal has a name
//Every Animal can speak **Virtual
//Every Animal can move **Virtual

class Animal    //Animal is an abstract base class (as opposed to concrete)
{
public:
    Animal(string name) : m_name(name) {};                      //constructor that takes name as input
    string name() const {return m_name;};                             //returns name;
    virtual string moveAction() const { return "walk"; } ;            //returns string saying how it moves. Virtual.
    virtual void speak() const = 0;                             //declare a function without specifying implementation "pure virtual function"
    virtual ~Animal() {};
    
private:
    string m_name;
};

//Kat Miao.
class Cat : public Animal
{
public:
    Cat(string name) : Animal(name) {} ;
    virtual void speak() const {cout << "Meow";} ;
    virtual ~Cat()
    {
        cout << "Destroying " << name() << " the cat" <<endl;
    };
};


//Ducks "Quack!" and swim.
class Duck : public Animal
{
public:
    Duck(string name) : Animal(name) {} ;
    virtual void speak() const {cout << "Quack";} ;
    virtual string moveAction() const {return "swim";} ;
    virtual ~Duck()
    {
        cout << "Destroying " << name() << " the duck" <<endl;
    };
};


//Pigs Oink (m_weight < 160) or Grunt (m_weight >= 160).
class Pig : public Animal
{
public:
    Pig(string name, int weight) : Animal(name), m_weight(weight) {} ;
    
    virtual void speak() const
    {
        if (m_weight < 160)
            cout << "Oink";
        else
            cout << "Grunt";
    };
    
    virtual ~Pig()
    {
        cout << "Destroying " << name() << " the pig" <<endl;
    };
    
private:
    int m_weight;
};



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MAIN ROUTINE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void animate(const Animal* a)
{
    a->speak();
    cout << "!  My name is " << a->name() << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");

    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);

      // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}
