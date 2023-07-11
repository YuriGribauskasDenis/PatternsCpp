
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Marine;

class State
{
public:
    virtual ~State() {}
    void setMarine(shared_ptr<Marine> marine) {
        this->m_marine = marine;
    }
    virtual string name() const = 0;
    virtual void go() = 0;
    virtual void shoot() = 0;
    Marine* getMarine() {return m_marine.get();}
private:
    shared_ptr<Marine> m_marine;
};

class Marine
{
public:
    Marine(shared_ptr<State> state) : m_state(nullptr) {
        transitionTo(state);
    }
    ~Marine() {}
    void transitionTo(shared_ptr<State> state) {
        cout << "Marine: Transition to " << (*state).name() << endl;
        m_state = state;
        m_state->setMarine(make_shared<Marine>(*this));
    }
    void move() {
        m_state->go();
    }
    void attack() {
        m_state->shoot();
    }
private:
    shared_ptr<State> m_state;
};

class Normal : public State
{
public:
    virtual string name() const override {
        return "Normal";
    }
    virtual void go() override;
    virtual void shoot() override {
        cout << "Normal Marine order Attack." << endl;
    }
};

class SteamPacked : public State
{
public:
    virtual string name() const override {
        return "SteamPacked";
    }
    virtual void go() override {
        cout << "SteamPacked Marine order Move." << endl;
    }
    virtual void shoot() override {
        cout << "SteamPacked Marine order Attack." << endl;
        cout << "SteamPacked Marin wants to change his state." << endl;
        getMarine()->transitionTo(make_shared<Normal>());
    }
};

void Normal::go() {
    cout << "Normal Marine order Move." << endl;
    cout << "Normal Marine wants to change his state." << endl;
    this->getMarine()->transitionTo(make_shared<SteamPacked>());
}

void clientCode() {
    unique_ptr<Marine> context = make_unique<Marine>(make_unique<Normal>());
    context->move();
    context->attack();
}

int main() {
    clientCode();
    
    return 0;
}