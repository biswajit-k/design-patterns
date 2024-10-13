# Design Patterns

design patterns are way to approach to commonly occuring problems. 
They are not the exact solution but they give the idea and line of though for
certain problems on how you should approach them.

They are divided into three categories:
* Creational
* Structural
* Behavioural


## Creational Design Patterns
Ways on how to create objects when there is some complex structure or requirements.


### Factory Method

When we have more than one type of an item and we need to decide at runtime what to use. Factory method gives way to separate object creation and also provides common way to access these object using interface extension.

**Example**

We have truck and sea transports. Both provide methods `load`, `unload` and `ship`.


**Steps**

* Have `transport` interface and its chlidren `truck` and `ship`.
* Have `transportFactory` interface and its chlidren `truckFactory` and `ShipFactory`


```cpp

// Object Implementation
#include <iostream>

// Base class for Transport
class Transport {
public:
    // Pure virtual methods
    virtual void load() = 0;
    virtual void unLoad() = 0;
    virtual void ship() = 0;

    // Virtual destructor for proper cleanup
    virtual ~Transport() = default;
};

// Derived class Truck
class Truck : public Transport {
public:
    void load() override {
        // Truck load logic
        std::cout << "Loading truck\n";
    }

    void unLoad() override {
        // Truck unload logic
        std::cout << "Unloading truck\n";
    }

    void ship() override {
        // Truck ship logic
        std::cout << "Shipping by truck\n";
    }
};

// Derived class Ship
class Ship : public Transport {
public:
    void load() override {
        // Ship load logic
        std::cout << "Loading ship\n";
    }

    void unLoad() override {
        // Ship unload logic
        std::cout << "Unloading ship\n";
    }

    void ship() override {
        // Ship ship logic
        std::cout << "Shipping by ship\n";
    }
};

// Object Creator/Factory Interface
class TransportFactory {
public:
    // Pure virtual method for creating transport objects
    virtual Transport* getTransport() = 0;

    // Virtual destructor for cleanup
    virtual ~TransportFactory() = default;
};

// Factory for creating Truck objects
class TruckFactory : public TransportFactory {
public:
    Transport* getTransport() override {
        return new Truck();
    }
};

// Factory for creating Ship objects
class ShipFactory : public TransportFactory {
public:
    Transport* getTransport() override {
        return new Ship();
    }
};

// Example usage
int main() {
    // Create a Truck using the factory
    TransportFactory* factory = new TruckFactory();
    Transport* truck = factory->getTransport();
    truck->load();
    truck->ship();
    truck->unLoad();

    // Cleanup
    delete truck;
    delete factory;

    // Create a Ship using the factory
    factory = new ShipFactory();
    Transport* ship = factory->getTransport();
    ship->load();
    ship->ship();
    ship->unLoad();

    // Cleanup
    delete ship;
    delete factory;

    return 0;
}


```

Advantages of factory are-
* Managing any configuration and pre-steps of object creation at one place. Like-
    
    * Singleton object logic
    * Caching logic
    * Storing objects in a vector
     
* Separating creation logic. Client doesn't need to know how to create item. Plus if creation logic needs to be changed, client code doesn't need to be altered.

### Builder Pattern

When you have multiple different configurations possible to create an
object. For example, to create a burger, you have options to add/not add
like - cheese, capsicum, corn, olives, and more. Some would want only corn
and cheese, others would want capsicum, olives and corn, etc

**Simple Method**

To handle all configurations we can have a big parameter list
in constructor and depending on the parameters we can decide to
take item or not.

But this method is a code smell. A better method is to use Builder
pattern.

**Builder Method**

Have functions for each item. If we want some item, we can call the 
function and the item will be returned after adding that item.

Example,

```cpp

class House {

    protected:
    string walls, doors;
    int windows, garage;

    public:
    void setWalls(string walls) {
        this.walls = walls;
    }
    void setDoors(string doors) {
        this.doors = doors;
    }
    void setWindows(int windows) {
        this.windows = windows;
    }
    void setGarage(int garage) {
        this.garage = garage;
    }
};

class HouseBuilder {

    House* house;

    public:

    HouseBuilder() {
        house = new House();
    }

    HouseBuilder* buildWalls() {
        // building walls logic
        string walls = buildWallsLogic();
        house->setWalls(walls);
        return this;
    }

    HouseBuilder* buildDoors() {
        // building doors logic
        string doors = buildDoorsLogic();
        house->setDoors(doors);
        return this;
    }

    ...
    ...

    House* getHouse() {
        return house;
    }
};

// main code

// my house has only walls and doors
House* myHouse = (new HouseBuilder())->buildWalls()->buildDoors()->getHouse();
```

**Director**

When we have multiple ways of building like - `WoodenHouseBuilder` and 
`CementHouseBuilder` (each implementing the common `HouseBuilder` interface 
with methods - *buildWalls*, *buildDoors*, etc).

The logic of building wooden resides in woodenbuilder and similarly for cement.
We will have a director as below-

```cpp
class HouseDirector {
    HouseBuilder* builder;

    public:
    void setBuilder(Builder* builder) {
        this.builder = builder;
    }

    House* constructHouse() {
        builder->buildWalls();
        builder->buildDoors();
        ...
        ...
        return builder->getHouse();
    }
};

// main code

HouseDirector* director = new HouseDirector();
WoodenBuilder* woodenBuilder = new WoodenBuilder();
CementBuilder* cementBuilder = new CementBuilder();

director->setBuilder(woodenBuilder);
WoodenHouse* myWoodenHouse = director->constructHouse();


director->setBuilder(cementBuilder);
CementHouse* myCementHouse = director->constructHouse();

// yay! I have myWoodenHouse and myCementHouse
```

### Singleton Pattern

It restricts a class to have only one instance. No matter how many times we create an object, the same instance is returned.

This is useful when we want to have single object to be used application wide. For example - a database connection, a logger.

This is also used when we want to get global access to an object.

This is a shared resource so in case of concurrent access, we need to design it accordingly.

#### Method
1. Make the constructor private
2. Have a public function for object creation calls the constructor first time and saves object in a static field, further calls return the same object.

```cpp
class DatabaseConnection {

    string uri;

    DatabaseConnection(string databaseUri) : uri(databaseUri) {
        cout << "database connection created" << endl;
    }

    DatabaseConnection(DatabaseConnection&) = delete;
    DatabaseConnection& operator=(DatabaseConnection&) = delete;

    public:

    static DatabaseConnection& getInstance(string databaseUri) {
        static DatabaseConnection instance(databaseUri);
        return instance;
    }

    void executeQuery(string query) {
        // call database with the query using uri
    }

};

// main

DatabaseConnection& connection = DatabaseConnection::getInstance("http://localhost:3456");

connection.executeQuery("select * from accounts");

```