
#include <iostream>
#include <memory>

class B
{
public:
    B() { std::cout << "B+" << std::endl; }
    ~B() { std::cout << "B-" << std::endl; }
};

class D : B
{
public:
    D() { std::cout << "D+" << std::endl; }
    ~D() { std::cout << "D-" << std::endl; }
};

class A
{
    D d;
public:
    A() { std::cout << "A+" << std::endl; }
    ~A() { std::cout << "A-" << std::endl; }
};

int main() 

{
    {
        A a;
    }
    std::cout << "========================" << std::endl;
    std::unique_ptr<B> spb = std::unique_ptr<B>(new B());
    std::cout << "========================" << std::endl;
    spb.reset(new B);
    std::cout << "========================" << std::endl;
    B* pb = spb.release();
    // spb.release();
    std::cout << "========================" << std::endl;
    delete pb;
    std::cout << "========================" << std::endl;



    return 0; 
}