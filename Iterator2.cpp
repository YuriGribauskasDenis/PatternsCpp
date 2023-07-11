#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


template <typename T, typename U>
class Iterator
{
public:
    typedef typename vector<T>::iterator iterType;
    
    Iterator(U* p_data, bool reverse = false) : m_p_data(p_data) {
        m_it = m_p_data->m_data.begin();
    }
    
    void first() {
        m_it = m_p_data->m_data.begin();
    }
    
    void next() {
        m_it++;
    }
    
    bool isDone() {
        return (m_it == m_p_data->m_data.end());
    }
    
    iterType current() {
        return m_it;
    }

private:
    U* m_p_data;
    iterType m_it;
};

template <class T>
class Container
{
public:
    void add(T a) {
        m_data.push_back(a);
    }
    
    shared_ptr<Iterator<T, Container>> createIterator() {
        return make_shared<Iterator<T, Container>>(this);
    }
private:
    vector<T> m_data;
    friend class Iterator<T, Container>;
};

class Data
{
public:
    Data(int a = 0) : m_data(a) {}
    
    void setData(int a) {
        m_data = a;
    }
    
    int data() {
        return m_data;
    }

private:
    int m_data;
};

void clientCode() {
    cout << "Iterator with int" << endl;
    Container<int> cont;
    
    for (int i = 0; i < 3; i++) {
        cont.add(i);
    }
    
    shared_ptr<Iterator<int, Container<int>>> it = cont.createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        cout << *it->current() << endl;
    }
    cout << endl;
    
    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.add(a);
    cont2.add(b);
    cont2.add(c);
    
    cout << "Iterator with custom Class" << endl;
    shared_ptr<Iterator<Data, Container<Data>>> it2 = cont2.createIterator();
    for (it2->first(); !it2->isDone(); it2->next()) {
        cout << it2->current()->data() << endl;
    }
}

int main() {
    
    clientCode();
    
    
    
    return 0;
}