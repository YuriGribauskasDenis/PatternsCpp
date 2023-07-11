
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Device
{
public:
    void report() const {
        cout << "Operationsl" << endl;
    }
};

class Settings
{
public:
    Settings(unique_ptr<Device>& device) : m_device(move(device)) { }
    unique_ptr<Device>& getDevice() {
        return m_device;
    }
    void report() const {
        cout << "Checking" << endl;
        m_device->report();
    }
private:
    shared_ptr<Device> m_device;
};

int main() {
    unique_ptr<Device> device = make_unique<Device>();
    Settings settings(move(device));
    unique_ptr<Device> myDevice = settings.getDevice();
    if (!myDevice.expired()) {
        myDevice.lock()->report();
    } else {
        cout << "ptr expired" << endl;
    }
    
    return 0;
}