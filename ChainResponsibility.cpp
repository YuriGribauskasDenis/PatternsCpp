#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class InterfaceHandler
{
public:
    virtual InterfaceHandler* setNext(InterfaceHandler* handler) = 0;
    virtual string handle(const string& request) const = 0;
};

class AbstractHandler : public InterfaceHandler
{
public:
    AbstractHandler() : m_nextHandler(nullptr) {}
    virtual InterfaceHandler* setNext(InterfaceHandler* handler) override {
        m_nextHandler = handler;
        return handler;
    }
    virtual string handle(const string& request) const override {
        if (m_nextHandler) {
            return m_nextHandler->handle(request);
        }
        //return {};
        return "";
    }
private:
    InterfaceHandler* m_nextHandler;
};

class Mechanic : public AbstractHandler {
public:
    virtual string handle(const string& request) const override {
        if (request == "Test CarBody") {
            return "Mecanic " + request + "\n";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class Electrician : public AbstractHandler {
public:
    virtual string handle(const string& request) const override {
        if (request == "Test Cables") {
            return "Electrician " + request + "\n";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class Technician : public AbstractHandler {
public:
    virtual string handle(const string& request) const override {
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
        const string result = handler.handle(t);
        if (!result.empty()) {
            cout << "  " << result;
        } else {
            cout << "  " << t << " was left undone." << endl;
        }
    }
}

int main() {
    Mechanic* mech = new Mechanic;
    Electrician* electric = new Electrician;
    Technician* tech = new Technician;
    mech->setNext(electric)->setNext(tech);
    
    cout << "Chain: Mechanic >> Electrician >> Technician" << endl;
    clientCode(*mech);
    cout << endl;
    cout << "Subchain:  Electrician >> Technician" << endl;
    clientCode(*electric);
    
    delete mech;
    delete electric;
    delete tech;
    
    return 0;
}