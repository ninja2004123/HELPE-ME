#include <iostream>
#include <memory>


class Bevarage {
public:
    virtual std::string GetDescription() = 0;
    virtual float Cost() = 0;
};


class Espresso : public Bevarage {
public:
    std::string GetDescription() override {
        return "A Cup Of Espresso";
    }

    float Cost() override {
        return 1;
    }
};


class AddOnDecorator : public Bevarage {
protected:
    std::unique_ptr<Bevarage> bevarage;

public:
    AddOnDecorator(std::unique_ptr<Bevarage> BVR) {
        this->bevarage = std::move(BVR);
    }

    virtual std::string GetDescription() = 0;
    virtual float Cost() = 0;

    ~AddOnDecorator() = default;
};


class CaramelDecorator : public AddOnDecorator {
public:
    CaramelDecorator(std::unique_ptr<Bevarage> Bevarage_) :
        AddOnDecorator(std::move(Bevarage_)) {}
   


    std::string GetDescription() override {
        return this->bevarage->GetDescription() + " + Caramel";
    }

    float Cost() override {
        return this->bevarage->Cost() + 0.5;
    }
};



int main(){
    
    std::unique_ptr<Bevarage> UserOrder = std::make_unique<Espresso>();


    UserOrder = std::make_unique<CaramelDecorator>(std::move(UserOrder));

    std::cout << UserOrder->GetDescription() << std::endl;
    std::cout << UserOrder->Cost() << std::endl;
    

    return 0;
}
