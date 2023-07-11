
#include <iostream>

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
    ProxyDataBase(DataBase* realDataBase) : m_realDataBase(new DataBase(*realDataBase)) {}
    ~ProxyDataBase() { delete m_realDataBase; }
    virtual void request() const override {
        if (checkAccess()) {
            m_realDataBase->request();
            logAccess();
        }
    }
private:
    DataBase* m_realDataBase;
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
    DataBase* realDataSet = new DataBase;
    clientCode(*realDataSet);
    cout << endl;
    cout << "Executing the same client code with a proxy database" << endl;
    ProxyDataBase* proxyDataBase = new ProxyDataBase(realDataSet);
    clientCode(*proxyDataBase);
    
    delete realDataSet;
    delete proxyDataBase;
    
    
    
    return 0;
}