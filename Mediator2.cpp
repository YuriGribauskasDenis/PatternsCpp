
#include <iostream>
#include <string>
#include <memory>

using namespace std;


class BaseComponent;

class Mediator
{
public:
    virtual void notify(BaseComponent* sender, string event) const = 0;
};

class BaseComponent
{
public:
    BaseComponent(shared_ptr<Mediator> mediator = nullptr) : m_mediator(mediator) {}
    void setMediator(shared_ptr<Mediator> mediator) {
        m_mediator = mediator;
    }
    Mediator* getMediator() const {
        return m_mediator.get();
    }
private:
    shared_ptr<Mediator> m_mediator;
};

class Component1 : public BaseComponent
{
public:
    void doA() {
        cout << "Component 1 does A." << endl;
        getMediator()->notify(this, "A");
    }
    void doB() {
        cout << "Component 1 does B." << endl;
        getMediator()->notify(this, "B");
    }
};

class Component2 : public BaseComponent
{
public:
    void doC() {
        cout << "Component 2 does C." << endl;
        getMediator()->notify(this, "C");
    }
    void doD() {
        cout << "Component 2 does D." << endl;
        getMediator()->notify(this, "D");
    }
};

class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator(shared_ptr<Component1> c1, shared_ptr<Component2> c2) : m_component1(c1), m_component2(c2) {
        m_component1->setMediator(shared_ptr<ConcreteMediator>(this));
        m_component2->setMediator(shared_ptr<ConcreteMediator>(this));
    }
    virtual void notify(BaseComponent* sender, string event) const override {
        if (event == "A") {
            cout << "Mediator reacts on A and triggers following operations:" << endl;
            m_component2->doC();
        }
        if (event == "D") {
            cout << "Mediator reacts on D and triggers following operations:" << endl;
            m_component1->doB();
            m_component2->doC();
        }
    }
private:
    shared_ptr<Component1> m_component1;
    shared_ptr<Component2> m_component2;
};

void clientCode() {
    shared_ptr<Component1> c1(new Component1);
    shared_ptr<Component2> c2(new Component2);
    unique_ptr<ConcreteMediator> mediator(new ConcreteMediator(c1, c2));
    cout << "Client triggers operation A." << endl;
    c1->doA();
    cout << endl;
    cout << "Client triggers operation D." << endl;
    c2->doD();
}

int main()
{
    clientCode();
    
    
    return 0;
}