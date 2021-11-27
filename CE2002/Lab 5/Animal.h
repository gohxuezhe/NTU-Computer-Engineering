#include <iostream>
#include <string>

using namespace std;

enum COLOR
{
    Green,
    Blue,
    White,
    Black,
    Brown
};
class Animal
{
public:
    Animal() : _name("unknown") {}
    Animal(string n, COLOR c) : _name(n), _color(c) {}
    ~Animal() {}

    string getName()
    {
        return _name;
    }
    COLOR getColor()
    {
        return _color;
    }
    virtual void speak()
    {
        cout << "Animal speaks " << endl;
    }
    virtual void move() = 0;

private:
    string _name;
    COLOR _color;
};

class Mammal : public Animal
{
public:
    Mammal() : Animal() {}

    Mammal(string n, COLOR c) : Animal(n, c) {}

    ~Mammal() {}

    virtual void eat()
    {
        cout << "Mammal eat " << endl;
    }

    virtual void move()
    {
        cout << "Mammal moves" << endl;
    }
};