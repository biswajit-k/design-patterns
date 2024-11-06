#include<bits/stdc++.h>
using namespace std;

class Transport {
    public:
    virtual void deliver() = 0;
};

class Ship: public Transport {

    public:
    void deliver() override {
        cout << "delivering using ship";
    }
};


class TransportFactory {

    public:
    virtual Transport* getInstance() = 0;
    
};

class ShipFactory: public TransportFactory {
    public:
    Transport* getInstance() {
        return new Ship();
    }
};

int main() {

    ShipFactory shipFactory;

    Transport* ship = shipFactory.getInstance();

    ship->deliver();

    return 0;
}

