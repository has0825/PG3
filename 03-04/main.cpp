#include <iostream>

class Base {
public:

    virtual void Func() = 0;

    virtual ~Base() {}
};

class Sub : public Base {
public:
    void Func() override {
        std::cout << "Override!!" << std::endl;
    }
};

class IInf {
public:

    virtual void Func1() = 0;
    virtual void Func2() = 0;

    virtual ~IInf() {}
};

class CClass : public IInf {
public:
    void Func1() override {
        std::cout << "Func1" << std::endl;
    }

    void Func2() override {
        std::cout << "Func2" << std::endl;
    }
};

int main() {

    Base* basePtr = new Sub();

    basePtr->Func();

    delete basePtr;


    IInf* infPtr = new CClass();

    infPtr->Func1();
    infPtr->Func2();

    delete infPtr;

    return 0;
}