
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Component
{
public:
    virtual ~Component() {}
    virtual string report() const = 0;
};

class ComponentA : public Component
{
public:
    virtual string report() const { return "using CompA"; }
};

class Decorator : public Component
{
public:
    Decorator(unique_ptr<Component> wrap) : m_wrapped(move(wrap)) {}
    virtual string report() const override { return m_wrapped->report(); }
private:
    unique_ptr<Component> m_wrapped;
};

class DecoratorA : public Decorator
{
public:
    DecoratorA(unique_ptr<Component> wrap) : Decorator(move(wrap)) {}
    virtual string report() const override { return "DecA: " + Decorator::report(); }
};

class DecoratorB : public Decorator
{
public:
    DecoratorB(unique_ptr<Component> wrap) : Decorator(move(wrap)) {}
    virtual string report() const override { return "DecB: " + Decorator::report(); }
};

void ClientCode(Component& component) {
    cout << "RESULT: " << component.report() << endl;
}

int main()
{
    unique_ptr<ComponentA> compA(new ComponentA());
    cout << compA->report() << endl;
    Decorator dec(move(compA));
    cout << dec.report() << endl;
    cout << "----------" << endl;
    unique_ptr<Component> simple(new ComponentA());
    ClientCode(*simple);
    unique_ptr<Component> dec1(new DecoratorA(move(simple)));
    ClientCode(*dec1);
    unique_ptr<Component> dec2(new DecoratorB(move(dec1)));
    ClientCode(*dec2);
    if (dec1) {
    cout << dec1->report() << endl;
    } else {
    cout << "Empty content" << endl;
    }

    return 0;
}