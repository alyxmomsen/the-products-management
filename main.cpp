#include <iostream>
#include <string>

class IEntity {
public:
    virtual double getPrice() = 0;
    virtual double getCost () = 0 ;
    virtual double getAmount() = 0;
    virtual std::string getTitle() = 0 ;
};

class Entity : public IEntity {
    std::string title;
    double cost;
    double amount;

public:
    double getCost() override {
        return this->cost;
    }

    double getPrice () override {
        return this->cost / this->amount ;
    }

    double getAmount() override {
        return this->amount;
    }

    std::string getTitle() override {
        return this->title;
    }

    Entity(double cost, double amount , std::string title) : cost(cost), amount(amount) , title(title) {
    }
};

class Water : public Entity {
public:
    Water(double cost, double amount , std::string title) : Entity(cost, amount  , title) {
    }
};

class MagnitSmallWater : public Water {
public:
    MagnitSmallWater (double cost, double amount) : Water(cost , amount , "magnit water 1.5")  {

    }
};

class MagnitBigWater : public Water {
public:
    MagnitBigWater (double cost, double amount) : Water(cost , amount , "magnit water 5") {

    }
};

class Grain : public Entity {
public:
    Grain(double cost, double amount) : Entity(cost, amount , "grain") {
    }
};

class Cigarettes : public Entity {
public:
    Cigarettes(double cost, double amount) : Entity(cost, amount , "cigarettes") {
    }
};

class Decorator : public IEntity {

public:
    virtual double getPrice() override = 0;
    virtual double getCost () override = 0 ;
    virtual double getAmount() override = 0;
    virtual std::string getTitle() override = 0 ;

    Decorator(IEntity* entity) : entity(entity) {}
private:
protected:
    IEntity* entity ;
};

class BlockCigarretesDecorator : public Decorator {

    double getPrice() override {
        return this->entity->getPrice();
    };
    double getCost () override {
        return entity->getCost() * 10;
    };
    double getAmount() override {
        return entity->getAmount();
    };
    std::string getTitle() override {
        return  "block of " + entity->getTitle();
    } ;

public:
    BlockCigarretesDecorator(IEntity* entity):Decorator(entity) {}
};

template <typename T>
class SmartPointer {
private:
    T* pnt;

public:
    SmartPointer(T* pnt) : pnt(pnt) {
        std::cout << "contructor" << std::endl;
    }
    ~SmartPointer() {
        delete pnt;
        std::cout << "destructor" << std::endl;
    }
};

int main() {

    Decorator* blockSigarettesDecorator = new BlockCigarretesDecorator(new Cigarettes(230 , 1));
    blockSigarettesDecorator = new BlockCigarretesDecorator(blockSigarettesDecorator);

    int arrlength = 1000 ;
    IEntity* entities[arrlength] = {
        new MagnitBigWater(60.0 , 5.0) ,
        new MagnitSmallWater(30.0 , 1.5) ,
        new Grain(60 , 1.5) ,
        new Cigarettes(690 , 3) ,
        blockSigarettesDecorator ,
    } ;

    for (int i=0 ; i<arrlength ; i++) {
        // if(entities[i])
        std::cout << entities[i]->getTitle() << std::endl ;
        std::cout << entities[i]->getPrice() << std::endl ;
        std::cout << entities[i]->getCost() << std::endl ;

    }

    return 0;
}
