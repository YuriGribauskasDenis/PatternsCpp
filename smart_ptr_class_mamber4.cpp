
#include <iostream>
#include <string>
#include <memory>

class Device
{
public:
    Device() = delete;
    Device(int ind) : m_id{ind} {}
    const int& GetId() const { return m_id; }
    void SetId(int newId) { m_id = newId; }
    Device* clone() const {
        return new Device(m_id);
    }
    void report() const {
        std::cout << "Operational" << std::endl;
        std::cout << "id : " << m_id << std::endl;
    }
private:
    int m_id;
};

class Settings
{
public:
    Settings() {}
    Settings( std::unique_ptr<Device> device ) : m_device{ std::move( device ) } { }
    Settings& operator=( const Settings& other ) {
        if ( &other != this ) {
            if ( other.m_device ) {
                m_device.reset( other.m_device->clone() );
            } else {
                m_device = nullptr;
            }
        }
        return *this;
    }
    Device* accessDevice() {
        return m_device.get();
    }
    const Device* getDevice() const {
        return m_device.get();
    }
    const Device* accessDeviceConst() {
        return m_device.get();
    }
    void report() const {
        std::cout << "Checking" << std::endl;
        m_device->report();
    }
private:
    std::unique_ptr<Device> m_device = nullptr;
};

void check_ptr(const Device* smth) {
    if (smth!=nullptr) {
        smth->report();
    } else {
        std::cout << "ptr expired" << std::endl;
    }
}

void doSomething(Device& smth){
    smth.report();
}

int main() {
    std::unique_ptr<Device> device(new Device(111));
    check_ptr(device.get());
    std::cout << "---------" << std::endl;
    Settings settings(std::move(device));
    check_ptr(settings.getDevice());
    settings.report();
    std::cout << "---------" << std::endl;
    Settings settings2{};
    settings2 = settings;
    check_ptr(settings2.getDevice());
    settings2.report();
    std::cout << "---------" << std::endl;
    settings2.accessDevice()->SetId(112);
    settings.report();
    settings2.report();
    
    
    return 0;
}