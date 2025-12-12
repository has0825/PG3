#include <iostream>
#include <string>

class Animal {
protected:
    std::string species; 

public:

    Animal(std::string s) : species(s) {}

    virtual ~Animal() {}

    virtual void Cry() {
        std::cout << "（動物が鳴いている...）" << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog() : Animal("犬") {}

    void Cry() override {
        std::cout << "[" << species << "] が吠えました:ワンワン" << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat() : Animal("猫") {}

    void Cry() override {
        std::cout << "[" << species << "] が鳴きました:ニャー" << std::endl;
    }
};

class Sheep : public Animal {
public:
    Sheep() : Animal("羊") {}

    void Cry() override {
        std::cout << "[" << species << "] が鳴きました:メェ～" << std::endl;
    }
};

int main() {
    Animal* zoo[3];

    zoo[0] = new Dog();
    zoo[1] = new Cat();
    zoo[2] = new Sheep();

    for (int i = 0; i < 3; i++) {
        zoo[i]->Cry();
    }

    for (int i = 0; i < 3; i++) {
        delete zoo[i];
    }
    return 0;
}