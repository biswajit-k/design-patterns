#include <iostream>
using namespace std;

/*

Read this only if unable to understand code

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

    // object member variables
    int x, y;

    // empty default constructor - no initialization
    Singleton() {}      

    // delete copy constructor
    Singleton(Singleton& obj) = delete;

    public:

    // reference to instance helps in avoding new and delete problems
    // also static member inside function would do two things
    // 1. Lazy instantiation, i.e when the function is first called, then only
    // instantiated
    // 2. We don't provide definition inside class, as class could be in a header file
    // so each cpp file which includes, should have its own definition of this function
    // hence their own 'instance', If instead we had added inside class, then this would
    // be shared by objects of different files also, which we might not want.
    static Singleton& getInstance();

    void setValue(int x, int y) {
        this -> x = x;
        this -> y = y;
    }

    void printValue() {
        cout << this -> x << ' ' << this -> y << '\n';
    }

};

// each cpp file would have its own 'instance'
Singleton& Singleton::getInstance() {
    static Singleton instance;
    return instance;
}

/*
    We could also implement it using pointer to instance instead of reference,
    also, in that case we should not worry about deleting the instance pointer 
    as there is no such 'memory leak' as the purpose of Singleton object is to 
    remain until the end of program(so no need to delete, get removed when program ends).
    Also see details here: https://stackoverflow.com/a/9968204/16165330 
*/

int main() {
    
    Singleton& obj = Singleton::getInstance();
    obj.setValue(4, 3);
    obj.printValue();

    Singleton& obj2 = Singleton::getInstance();
    obj2.setValue(1, 2);
    obj2.printValue();

    cout << &obj << '\n' << &obj2 << '\n';

    return 0;
}
