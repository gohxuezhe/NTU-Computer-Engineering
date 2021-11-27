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
    Animal() : _name("unknown")
    {
        cout << "constructing Animal object " << _name << endl;
    }
    Animal(string n, COLOR c) : _name(n), _color(c)
    {
        cout << "constructing Animal object " << _name << " " << _color << endl;
    }
    ~Animal()
    {
        cout << "destructing Animal object " << _name << endl;
    }

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
    Mammal() : Animal()
    {
        cout << "constructing Mammal object " << Animal::getName() << endl;
    }

    Mammal(string n, COLOR c) : Animal(n, c)
    {
        cout << "constructing Mammal object " << Animal::getName() << " " << Animal::getColor() << endl;
    }

    ~Mammal()
    {
        cout << "destructing Mammal object " << Animal::getName() << endl;
    }

    virtual void eat()
    {
        cout << "Mammal eat " << endl;
    }

    virtual void move()
    {
        cout << "Mammal moves " << endl;
    }
};

class Dog : public Mammal
{
public:
    Dog() : Mammal()
    {
        _owner = "unknown";
        cout << "constructing Dog object " << Animal::getName() << endl;
    }

    Dog(string n, COLOR c, string owner) : Mammal(n, c)
    {
        _owner = owner;
        cout << "constructing Dog object " << Animal::getName() << " " << Animal::getColor() << endl;
    }

    ~Dog()
    {
        cout << "destructing Dog object " << Animal::getName() << endl;
    }

    void speak()
    {
        cout << "woof" << endl;
    }

    void move()
    {
        cout << "Dog moves " << endl;
    }

    void eat()
    {
        cout << "Dog eats " << endl;
    }

private:
    string _owner;
};

int main()
{
    // Animal a("Ivan", Black);
    // a.speak();
    // cout << "Program exiting …. " << endl;

    Mammal b("Tim", Brown);
    b.speak();

    Dog c("Tom", White, "Ivan");
    c.move();

    Animal *animalPTR = new Dog("Lassie", White, "Andy");
    animalPTR->speak();
    animalPTR->move();
    delete animalPTR;

    // Dog dogi("Lassie", White, "Andy");
    // Mammal *aniPtr = &dogi ;
    // Mammal &aniRef = dogi ;
    // Mammal aniVal = dogi ;
    // aniPtr->speak() ;
    // aniRef.speak() ;
    // aniVal.speak() ;
    return 0;
}