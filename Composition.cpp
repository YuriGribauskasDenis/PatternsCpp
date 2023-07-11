#include <iostream>
using namespace std;

class B
{
public:
    B() : m_data(0) { cout << "Bdef+" << endl; }
    B(int a) : m_data(a) { cout << "B+" << endl; }
    const int& getData() const { return m_data; }
private:
    int m_data;
};

class D
{
public:
    D(int a) : m_obj2(a), m_b(a) { cout << "D+" << endl; }
    void printData() {
        cout << "Data of class D object is " << m_b << endl;
        cout << "Data of class B object in class D is " << m_obj2.getData();
    }
private:
    int m_b;
    B m_obj2;
};

int main()
{
    D obj1(25);
    obj1.printData();
    
    
    return 0;
}