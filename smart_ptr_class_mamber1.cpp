
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
    Settings(shared_ptr<Device>& device) : m_device(device) { }
    weak_ptr<Device> getDevice() {
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
    shared_ptr<Device> device = make_shared<Device>();
    Settings settings(device);
    weak_ptr<Device> myDevice = settings.getDevice();
    if (!myDevice.expired()) {
        myDevice.lock()->report();
    } else {
        cout << "ptr expired" << endl;
    }
    
    return 0;
}