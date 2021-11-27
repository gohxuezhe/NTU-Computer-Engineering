#include <iostream>
#include "Animal.h"

using namespace std;

class Dog : public Mammal
{
public:
    Dog() : Mammal()
    {
        _owner = "Unknown_Owner";
    }

    Dog(string n, COLOR c, string owner) : Mammal(n, c)
    {
        _owner = owner;
    }

    ~Dog() {}

    void speak()
    {
        cout << "Dog woofs" << endl;
    };
    void move()
    {
        cout << "Dog moves" << endl;
    };
    void eat()
    {
        cout << "Dog eats" << endl;
    };

private:
    string _owner;
};

class Cat : public Mammal
{
public:
    Cat() : Mammal()
    {
        _owner = "Unknown_Owner";
    }

    Cat(string n, COLOR c, string owner) : Mammal(n, c)
    {
        _owner = owner;
    }

    ~Cat() {}

    void speak()
    {
        cout << "Cat meows" << endl;
    }
    void move()
    {
        cout << "Cat moves" << endl;
    }
    void eat()
    {
        cout << "Cat eats" << endl;
    }

private:
    string _owner;
};

class Lion : public Mammal
{
public:
    Lion() : Mammal()
    {
        _owner = "Unknown_Owner";
    }

    Lion(string n, COLOR c, string owner) : Mammal(n, c)
    {
        _owner = owner;
    }

    ~Lion() {}

    void speak()
    {
        cout << "Lion roars" << endl;
    }
    void move()
    {
        cout << "Lion moves" << endl;
    }
    void eat()
    {
        cout << "Lion eats" << endl;
    }

private:
    string _owner;
};