
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


class Memento
{
public:
    virtual ~Memento() {}
    virtual string getName() const = 0;
    virtual string date() const = 0;
    virtual string state() const = 0;
};

class ConcreteMemento : public Memento
{
public:
    ConcreteMemento(string state) : m_state(state) {
        time_t now = time(0);
        m_date = ctime(&now);
    }
    virtual string state() const override {
        return m_state;
    }
    virtual string getName() const override {
        return m_date + " / (" + m_state.substr(0, 9) + "...)";
    }
    virtual string date() const override {
        return m_date;
    }
private:
    string m_state;
    string m_date;
};

class Originator
{
public:
    Originator(string state) : m_state(state) {
        cout << "Originator: My initial state is: " << m_state << endl;
    }
    void doSomething() {
        cout << "Originator: I'm doing something important." << endl;
        m_state = generateRandomString(30);
        cout << "Originator: and my state has changed to: " << m_state << endl;
    }
    shared_ptr<Memento> save() {
        return make_shared<ConcreteMemento>(m_state);
    }
    void restore(shared_ptr<Memento> memento) {
        m_state = memento->state();
        cout << "Originator: My state has changed to: " << m_state << endl;
    }
private:
    string m_state;
    string generateRandomString(const int length = 10) {
        srand((unsigned)time(NULL));
        // srand((unsigned)time(NULL) * getpid());
        static const char alphabetNum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphabetNum) - 1;
        string randomString;
        randomString.reserve(length);
        for (int i = 0; i < length; i++) {
            randomString += alphabetNum[rand() % stringLength];
        }
        return randomString;
    }
};

class Caretaker
{
public:
    Caretaker(Originator* originator) : m_originator(originator) {}
    ~Caretaker() {}
    void backup() {
        cout << endl;
        cout << "Caretaker: Saving Originator's state..." << endl;
        m_mementos.push_back(m_originator->save());
    }
    void undo() {
        if (!m_mementos.size()) {
            return;
        }
        shared_ptr<Memento> memento = m_mementos.back();
        m_mementos.pop_back();
        cout << "Caretaker: Restoring state to: " << memento->getName() << endl;
        srand ((unsigned)time(NULL));
    }
    void showHistory() const {
        cout << "Caretaker: Here's the list of mementos:" << endl;
        for (const auto& memento : m_mementos) {
            cout << memento->getName() << endl;
        }
    }
private:
    vector<shared_ptr<Memento>> m_mementos;
    Originator* m_originator;
};

void clientCode() {
    shared_ptr<Originator> originator = make_shared<Originator>("Super-duper-super-puper-super.");
    shared_ptr<Caretaker> caretaker = make_shared<Caretaker>(&*originator);
    caretaker->backup();
    originator->doSomething();
    sleep(1);
    caretaker->backup();
    originator->doSomething();
    sleep(1);
    caretaker->backup();
    originator->doSomething();
    cout << endl;
    caretaker->showHistory();
    cout << endl;
    cout << "Client: Now, let's rollback!" << endl;
    cout << endl;
    caretaker->undo();
    cout << endl;
    cout << "Client: Once more!" << endl;
    cout << endl;
    caretaker->undo();
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    clientCode();
    
    
    
    return 0;
}