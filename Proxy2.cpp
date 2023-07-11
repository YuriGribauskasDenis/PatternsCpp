
#include <iostream>
#include <memory>

using namespace std;

class InterfaceDataBase
{
public:
    virtual void request() const = 0;
};

class DataBase : public InterfaceDataBase
{
public:
    virtual void request() const override {
        cout << "Real DataBase is handling request." << endl;
    }
};

class ProxyDataBase : public InterfaceDataBase {
public:
    ProxyDataBase(const shared_ptr<DataBase>& realDataBase) : m_realDataBase(realDataBase) {}
    ~ProxyDataBase() {}
    virtual void request() const override {
        if (checkAccess()) {
            m_realDataBase->request();
            logAccess();
        }
    }
private:
    shared_ptr<DataBase> m_realDataBase;
    bool checkAccess() const {
        cout << "ProxyDataBase is checking access prior to a real request." << endl;
        return true;
    }
    void logAccess() const {
        cout << "ProxyDataBase is logging the request." << endl;
    }

};

void clientCode(const InterfaceDataBase& dataBase) {
  dataBase.request();
}

int main() {
    cout << "Executing the client code with a real database" << endl;
    shared_ptr<DataBase> realDataSet = make_shared<DataBase>();
    clientCode(*realDataSet);
    cout << endl;
    cout << "Executing the same client code with a proxy database" << endl;
    unique_ptr<ProxyDataBase> proxyDataBase = make_unique<ProxyDataBase>(realDataSet);
    clientCode(*proxyDataBase);

    
    
    
    return 0;
}