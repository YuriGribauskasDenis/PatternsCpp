#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>

using namespace std;

class InterfaceHandler
{
public:
    virtual shared_ptr<InterfaceHandler> setNext(const shared_ptr<InterfaceHandler>& handler) = 0;
    virtual optional<string> handle(const string& request) const = 0;
};

class AbstractHandler : public InterfaceHandler
{
public:
    AbstractHandler() : m_nextHandler(nullptr) {}
    virtual shared_ptr<InterfaceHandler> setNext(const shared_ptr<InterfaceHandler>& handler) override {
        m_nextHandler = handler;
        return handler;
    }
    virtual optional<string> handle(const string& request) const override {
        if (m_nextHandler) {
            return m_nextHandler->handle(request);
        }
        return {};
    }
private:
    shared_ptr<InterfaceHandler> m_nextHandler;
};

class Mechanic : public AbstractHandler {
public:
    virtual optional<string> handle(const string& request) const override {
        if (request == "Test CarBody") {
            return "Mecanic " + request + "\n";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class Electrician : public AbstractHandler {
public:
    virtual optional<string> handle(const string& request) const override {
        if (request == "Test Cables") {
            return "Electrician " + request + "\n";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class Technician : public AbstractHandler {
public:
    virtual optional<string> handle(const string& request) const override {
        if (request == "Test Computer") {
            return "Technician " + request + "\n";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

void clientCode(const InterfaceHandler& handler) {
    vector<string> tests = {"Test Cables", "Test CarBody", "Test Wheels"};
    for (const string& t : tests) {
        cout << "Client: Who is doing the " << t << " ?" << endl;
        const optional<string> result = handler.handle(t);
        if (result) {
            cout << "  " << *result;
        } else {
            cout << "  " << t << " was left undone." << endl;
        }
    }
}

int main() {
    shared_ptr<Mechanic> mech = make_shared<Mechanic>();
    shared_ptr<Electrician> electric = make_shared<Electrician>();
    shared_ptr<Technician> tech = make_shared<Technician>();
    mech->setNext(electric)->setNext(tech);
    
    cout << "Chain: Mechanic >> Electrician >> Technician" << endl;
    clientCode(*mech);
    cout << endl;
    cout << "Subchain:  Electrician >> Technician" << endl;
    clientCode(*electric);

    
    return 0;
}