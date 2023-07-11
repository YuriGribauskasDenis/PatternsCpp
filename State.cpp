
#include <iostream>
// #include <typeinfo>

using namespace std;

class Context;

class State
{
public:
    virtual ~State() {}
    void setContext(Context* context) {
        this->m_context = context;
    }
    virtual void handle1() = 0;
    virtual void handle2() = 0;
    Context* getContext() {return m_context;}
private:
    Context* m_context;
};

class Context
{
public:
    Context(State* state) : m_state(nullptr) {
        this->transitionTo(state);
    }
    ~Context() { delete m_state; }
        void transitionTo(State* state) {
        cout << "Context: Transition to " << typeid(*state).name() << endl;
        if (this->m_state != nullptr) {
            delete this->m_state;
        }
        this->m_state = state;
        this->m_state->setContext(this);
    }
    void request1() {
        this->m_state->handle1();
    }
    void request2() {
        this->m_state->handle2();
    }
private:
    State* m_state;
};

class ConcreteStateA : public State
{
public:
    virtual void handle1() override;
    virtual void handle2() override {
        cout << "ConcreteStateA handles request2." << endl;
    }
};

class ConcreteStateB : public State
{
public:
    virtual void handle1() override {
        cout << "ConcreteStateB handles request1." << endl;
    }
    virtual void handle2() override {
        cout << "ConcreteStateB handles request2." << endl;
        cout << "ConcreteStateB wants to change the state of the context." << endl;
        this->getContext()->transitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::handle1() {
    cout << "ConcreteStateA handles request1." << endl;
    cout << "ConcreteStateA wants to change the state of the context." << endl;
    this->getContext()->transitionTo(new ConcreteStateB);
}

void clientCode() {
    Context* context = new Context(new ConcreteStateA);
    context->request1();
    context->request2();
    delete context;
}

int main() {
    clientCode();
    
    return 0;
}