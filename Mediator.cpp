
#include <iostream>
#include <string>

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
    BaseComponent(Mediator* mediator = nullptr) : m_mediator(mediator) {}
    void setMediator(Mediator* mediator) {
        m_mediator = mediator;
    }
    Mediator* getMediator() const {
        return m_mediator;
    }
private:
    Mediator* m_mediator;
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

class Component2 : public BaseComponent {
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
    ConcreteMediator(Component1* c1, Component2 *c2) : m_component1(c1), m_component2(c2) {
        m_component1->setMediator(this);
        m_component2->setMediator(this);
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
    Component1* m_component1;
    Component2* m_component2;
};

void clientCode() {
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A." << endl;
    c1->doA();
    cout << endl;
    cout << "Client triggers operation D." << endl;
    c2->doD();
    
    delete c1;
    delete c2;
    delete mediator;
}

int main()
{
    clientCode();
    
    
    return 0;
}