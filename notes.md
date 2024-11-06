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
    House(HouseBuilder builder) {
        this.walls = builder.walls;
        this.doors = builder.doors;
        this.windows = builder.windows;
        this.garage = builder.garage;
        
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

## Structural Design Patterns

Methods to create different structures using existing object/classes

### Adapter Pattern

Making two incompatible interfaces compatible by using an adpater.

**idea**

Interface 1 and interface 2 have different function signatures to execute
same thing. Adapter implements interface 1 and within that function it makes
call to function of interface 2 in the format it requests.

Below is the class diagram for the same-

![adapter pattern class diagram](/assets/adapter_class_diagram.png)

The adapter has adaptee as its class member i.e composition is used.

There is another method called class adapter where the adapter inherit the adaptee instead of using it as its member. Then it can simply call the inherited method

> In python, if you inherit from multiple classes, and they have common method, then `super.method_name()` will call method of first class listed in inheritance.
```python
class A():
    def drive():
        pass

class B():
    def drive():
        pass

class C(A, B):
    def drive():
        super.drive()   # will call A's drive as it is listed first in inheritance list

# If we want to call B's we can do B.drive()
```

**Usecases**
* We had a SQL service to store our e-commerce website data. Now we want to shift
to No-SQL database. We create an adapter that coverts existing commands to be executed
in our No-SQL database.
* We have to integrate multiple third party payment gateways like paypal, stripe.
And we already have a simple `PaymentProcesser`. We create adapters for each
payment gateway so exsitng codebase works normally, just we need to use the
adapter of the required payment gateway.
* Synchronous to muiti-threaded converter.
* Let's say a new implementation of a function came which has different signature. We can use an adapter which still takes old function's signature and internally calls the new function with required signature. In this way we don't have to change the existing code.


**Note**

Adapter and decorator both wrap an interface. However, they
are different in the sense that adapter makes call of one interface
to be compatible with similar call of another interface w/o changing
any functionality.

However, the decorator wraps and adds additional behaviour to the existing
functionality.

**Code**

In below code, we have a gear car, however our client wants automatic car
which takes speed and drive. So, we create an adapter that wraps over
the gear car, takes the speed as input and applies necessary gear to drive
at that speed.


```python
from abc import ABC, abstractmethod

class GearCar():

    def __init__(self) -> None:
        self.current_gear = 0   # neutral by default
    
    def drive(self, gear) -> None:
        self.current_gear = gear
        self.__acclerate(gear)

    def __acclerate(self, gear) -> None:
        pass


class AutoCar(ABC):

    @abstractmethod
    def drive(self, speed) -> None:
        pass


class AutoCarAdapter(AutoCar):

    def __init__(self) -> None:
        self._gear_car = GearCar()

    def drive(self, speed) -> None:
        if speed >= 0 and speed <= 10:
            self._current_gear = 1
        elif speed <= 25:
            self._current_gear = 2
        elif speed <= 30:
            self._current_gear = 3
        elif speed <= 50:
            self._current_gear = 4
        else:
            self._current_gear = 5

        self._gear_car.drive(self._current_gear)






# main code
auto_car_adapter = AutoCarAdapter()

SPEED = 40
auto_car_adapter.drive(40)  # take 40km/hr speed and call 4th gear of car internally
```

### Facade Pattern

When we have a system consisting of multiple classes each interacting with each other and we want a simple way to perform an operation. For example, a compiler that has a *parser*, *tokenizer*, *symbol table*, etc. and we want to compile a sentence.

The *tokenizer* would need *symbol table* before hand, in XYZ way, the *parser* would need some other thing. all of these would interact with each other in complex way.

**idea**

We will create a class that defines the method `compile` which would take care of initializing all the compiler components and calling them in whatever order in whatever way to give us the output.


![facade pattern](/assets/facade_pattern.png)


**code**

```python

class SymbolTable:
    ...

class Tokenizer:
    def __init__(self, symbol_table: SymbolTable) -> None:
        pass

class Parser:
    def __init__(self, symbol_table, tokenizer) -> None:
        pass

# compiler facade - hides all the complexity, and provides required, limited functionality access
class Compiler:
    def __init__(self) -> None:
        symbol_table = SymbolTable(...)
        symbol_table.init()

        tokenizer = Tokenizer(symbol_table)
        ...

    def compile(statement: str) -> str:
        symbols = symbol_table.get_symbols()
        ...
        return result


```


### Proxy Pattern

Controlling access to an object through another object(proxy). This is done for reasons like - security, caching, etc


There are three types of proxy-

* **Remote Proxy**: A proxy that interacts with a remote object. This is helpful when you want to control the identity/ip through which request is sent to server(say using user's token), or maybe in Nodejs, we can avoid returning promises by awaiting in our proxy and returning final result.

* **Virtual Proxy**: when an object is expensive to create(or expensive method) we can do things lazily. When we initialize the object/call the method, it will show us that it is created, on the back hand it will do things lazily(hence virtual).

* **Protection Proxy**: Authenticate/authorize before providing access to object.


It is different from decorator pattern in the sense that although it adds functionality, it is only to control access and not modify core behaviour

![proxy pattern](/assets/proxy%20pattern.png)

In above, the proxy has the `real subject` and both proxy and real subject implement the interface `Isubject` 


### Decorator Pattern

Adding additional functionality over existing object while keeping the interface same.

**idea**

The decorator is a wrapper with same interface as the object it is wrapping, which adds/modify functionality of the object

![decorator pattern](/assets/decorator_pattern.png)

In above, we have two main coffee(decaf, expresso) and we have additional flavours like caramel, soy. 

Then the decorator is a type of beverage and also it has a beverage.(this introduces recursion, meaning we can wrap decorator over decorator like caramel over soy... and finally it ends up with a decafe/expresso)

> The decorator doesn't add constraint over the order in which wrapping will be done.

**Code logic**

```python
from abc import abstractmethod, ABC


class Beverage:

    @abstractmethod
    def get_desc():
        pass
    
    @abstractmethod
    def cost():
        pass

class Decaf(Beverage):

    def cost():
        ...
    
    def get_desc():
        ...

class AddOnDecorator(Beverage, ABC):

    def __init__(self, beverage: Beverage):
        self.beverage = beverage

    @abstractmethod
    def cost():
        pass

    @abstractmethod
    def get_desc():
        pass

class Caramel(AddOnDecorator):

    def cost():
        ...     # some decoration
        xyz = self.beverage.cost()
        ...
        return xyz

    def get_desc():
        # similar to cost function


##### main code

decafe = Decafe()
carameled_decafe = Caramel(decafe)

carameled_decafe.cost()

```



## Misc Patterns

* We can pass a config object to another object's constructor. The object will
then use the configurations to decide what to do. For example, we could have
a class that database connection object. To that we could pass the loggingConfig
based on which logging of database would be done.

```
mainLoggingConfig = DatabaseConfig(indentation=2, logColor='red', logLevel=1)

DatabaseConnection(URI, loggingConfig=mainLoggingConfig)
    fun log(s):
        space = mainLoggingConfig.indentation
        color = mainLoggingConfig.color or color.BLUE
        ...
        ...

```

* We should avoid returning boolean from function as they would result in creating if/else statement elsewhere in our program.