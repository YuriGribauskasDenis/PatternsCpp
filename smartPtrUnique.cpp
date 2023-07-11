
#include <iostream>
#include <memory>


class T
{
public:
    T() = delete;
    T(int ind) : m_id{ind} {}
    const int& GetId() const { return m_id; }
    void SetId(int newId) { m_id = newId; }
    void report() const {
        std::cout << "Operationsl" << std::endl;
        std::cout << "id : " << m_id << std::endl;
    }
private:
    int m_id;
};

void check_ptr(const T* smth) {
    if (smth!=nullptr) {
        smth->report();
    } else {
        std::cout << "ptr expired" << std::endl;
    }
}

int main() {
    std::unique_ptr<T> upt1 = std::make_unique<T>(12);
    check_ptr(upt1.get());
    {
        std::unique_ptr<T>& upt2 = upt1;
        //upt2->report();
        check_ptr(upt2.get());
    }
    //check_ptr(upt2.get());
    
    
    
    return 0;
}