
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Device
{
public:
    Device() = delete;
    Device(int ind) : m_id{ind} {}
    const int& GetId() const { return m_id; }
    void SetId(int newId) { m_id = newId; }
    void report() const {
        cout << "Operational" << endl;
        cout << "id : " << m_id << endl;
    }
private:
    int m_id;
};

class Settings
{
public:
    Settings(unique_ptr<Device> device) : m_device(move(device)) { }
    Device* accessDevice() {
        return m_device.get();s
    }
    const Device* getDevice() {
        //return static_cast<const Device*>(m_device.get());
        return m_device.get();
    }
    void report() const {
        cout << "Checking" << endl;
        m_device->report();
    }
private:
    unique_ptr<Device> m_device;
};

void check_ptr(const Device* smth) {
    if (smth!=nullptr) {
        smth->report();
    } else {
        cout << "ptr expired" << endl;
    }
}

void doSomething(Device& smth){
    smth.report();
}

int main() {
    unique_ptr<Device> device(new Device(117));
    check_ptr(&*device);
    cout << "---------" << endl;
    Settings settings(move(device));
    settings.report();
    cout << "---------" << endl;
    Device* myDevice = settings.accessDevice();
    check_ptr(myDevice);
    cout << "---------" << endl;
    settings.report();
    cout << "---------" << endl;
    check_ptr(device.get());
    cout << "---------" << endl;
    if(device){
        doSomething(*device);
    }
    cout << "=========" << endl;
    myDevice = nullptr;
    check_ptr(myDevice);
    myDevice = settings.accessDevice();
    check_ptr(myDevice);
    myDevice->SetId(542);
    check_ptr(myDevice);
    const Device* cmyDevice = settings.getDevice();
    myDevice->SetId(879);
    check_ptr(myDevice);
    //cmyDevice->SetId(777);
    check_ptr(cmyDevice);
    cout << "---------" << endl;
    
    return 0;
}