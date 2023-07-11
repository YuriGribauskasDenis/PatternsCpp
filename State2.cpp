
#include <iostream>
#include <memory>

using namespace std;

class Context;

class State
{
public:
    virtual ~State() {}
    void setContext(shared_ptr<Context> context) {
        this->m_context = context;
    }
    virtual void handle1() = 0;
    virtual void handle2() = 0;
    Context* getContext() {return m_context.get();}
private:
    shared_ptr<Context> m_context;
};

class Context
{
public:
    Context(shared_ptr<State> state) : m_state(nullptr) {
        transitionTo(state);
    }
    ~Context() {}
    void transitionTo(shared_ptr<State> state) {
        cout << "Context: Transition to " << typeid(*state).name() << endl;
        m_state = state;
        m_state->setContext(make_shared<Context>(*this));
    }
    void request1() {
        m_state->handle1();
    }
    void request2() {
        m_state->handle2();
    }
private:
    shared_ptr<State> m_state;
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
        getContext()->transitionTo(make_shared<ConcreteStateA>());
    }
};

void ConcreteStateA::handle1() {
    cout << "ConcreteStateA handles request1." << endl;
    cout << "ConcreteStateA wants to change the state of the context." << endl;
    this->getContext()->transitionTo(make_shared<ConcreteStateB>());
}

void clientCode() {
    unique_ptr<Context> context = make_unique<Context>(make_unique<ConcreteStateA>());
    context->request1();
    context->request2();
}

int main() {
    clientCode();
    
    return 0;
}