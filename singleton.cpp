#include <iostream>
using namespace std;

/*
implement singleton class:
    1. At most one object of the class can exist at any time
    2. New objects created will point to the same object
    3. (bonus) How to handle concurrent situations

Attempt:
    1. Since, everytime I create a new object, it should point to the same instance, so 
        I need to have a reference of the object. It would let me know when creating an
        instance if I already have one.

    2. To control the object creation, which means that I need to prevent direct access
        to the constructors. So, I'll make them private. Then proivde a method for 
        creating an object.


Usecases:
1. Logger: We don't want to have multiple objects for logger. They can exist but, for
            cases like storing logging reports, log count, etc. we would want to have
            all those held by one logger object and not spread out.

2. Database connection: When 1 database connection required.

*/

class Singleton {

    // object reference
    static Singleton* ptr;

    // object member variables
    int x, y;

    // empty default constructor
    Singleton() {}      

    // delete copy constructor
    Singleton(Singleton& obj) = delete;

    public:

    static Singleton* getInstance() {
        if(ptr)
            return ptr;
        return ptr = new Singleton();
    }

    void setValue(int x, int y) {
        this -> x = x;
        this -> y = y;
    }

    void printValue() {
        cout << this -> x << ' ' << this -> y << '\n';
    }

};

// definition required outside class as this class could be present in a header file
// hence, each file which includes this class should have their own local static instance
Singleton* Singleton::ptr = nullptr;

int main() {
    
    Singleton* ptr = Singleton::getInstance();
    ptr->setValue(4, 3);
    ptr->printValue();

    Singleton* ptr2 = Singleton::getInstance();
    ptr2->setValue(1, 2);
    ptr2->printValue();

    cout << ptr << '\n' << ptr2 << '\n';

    return 0;
}