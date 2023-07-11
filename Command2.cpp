#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

class SimpleCommand : public Command {
public:
    explicit SimpleCommand(const string& payLoad) : m_payLoad(payLoad) {
    }
    void execute() const override {
        cout << "SimpleCommand does simple things like printing (" << m_payLoad << ")" << endl;
    }
private:
    string m_payLoad;
};

class Receiver
{
public:
    void doSomething(const string& a) {
        cout << "Receiver: Working on (" << a << ")" << endl;
    }
    void doSomethingElse(const string& a) {
        cout << "Receiver: Working on (" << a << ")" << endl;
    }
};

class ComplexCommand : public Command {
public:
    ComplexCommand(unique_ptr<Receiver> receiver, string a, string b) : m_receiver(move(receiver)), m_a(a), m_b(b) {}
    virtual void execute() const override {
        cout << "ComplexCommand delegates. Complex stuff should be done by a receiver object." << endl;
        m_receiver->doSomething(m_a);
        m_receiver->doSomethingElse(m_b);
    }
private:
    unique_ptr<Receiver> m_receiver;
    string m_a;
    string m_b;
};


class Invoker
{
public:
    ~Invoker() {}
    void setOnStart(const shared_ptr<Command>& command) {
        m_start = command;
    }
    void setOnFinish(const shared_ptr<Command>& command) {
        m_finish = command;
    }
    void doSomethingImportant() {
        cout << "Invoker: Does anybody want something done before I begin?" << endl;
        if (m_start) {
            m_start->execute();
        }
        cout << "Invoker: ...doing something really important..." << endl;
        cout << "Invoker: Does anybody want something done after I finish?" << endl;
        if (m_finish) {
            m_finish->execute();
        }
    }
private:
    shared_ptr<Command> m_start;
    shared_ptr<Command> m_finish;
};

int main() {
    unique_ptr<Invoker> invoker = make_unique<Invoker>();
    invoker->setOnStart(make_shared<SimpleCommand>("Say Hi!"));
    unique_ptr<Receiver> receiver = make_unique<Receiver>();
    invoker->setOnFinish(make_shared<ComplexCommand>(move(receiver), "Send email", "Save report"));
    invoker->doSomethingImportant();


    return 0;
}