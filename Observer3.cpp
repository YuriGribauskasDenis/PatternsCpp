
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename, typename>
class Iterator;

template <typename T>
class RandomizedSet
{
public:
    RandomizedSet() {}

    bool insert(T val) {
        bool res = !(bool)m_elemMap.count(val);
        if (res) {
            m_elemMap[val] = m_elemList.size();
            m_elemList.push_back(val);
        }
        return res;
    }

    bool remove(T val) {
        bool res = (bool)m_elemMap.count(val);
        if (res) {
            //swap mechanics
            int idx = m_elemMap[val];
            T lastVal = m_elemList.back();
            m_elemList[idx] = lastVal;
            m_elemList.pop_back();
            m_elemMap[lastVal] = idx;
            m_elemMap.erase(val);
        }
        return res;
    }

    T getRandom() const {
        srand((unsigned)time(NULL));
        int idx = (rand() % m_elemList.size());
        return m_elemList[idx];
    }

    auto size() const {
        return m_elemList.size();
    }

    void printV() const {
        for (const auto& el : m_elemList) {
            cout << el << " ";
        }
        cout << endl;
    }
    
    shared_ptr<Iterator<T, RandomizedSet>> createIterator() {
        return make_shared<Iterator<T, RandomizedSet>>(this);
    }  
private:
    vector<T> m_elemList;
    // unordered_map<T, unsigned int> m_elemMap; // element, index
    unordered_map<T, decltype(m_elemList.size())> m_elemMap; // element, index
    friend class Iterator<T, RandomizedSet>;
};

template <typename T, typename U>
class Iterator
{
public:
    typedef typename vector<T>::iterator iterType;
    
    Iterator(U* p_data) : m_p_data(p_data) {
        m_it = m_p_data->m_elemList.begin();
    }
    
    void first() {
        m_it = m_p_data->m_elemList.begin();
    }
    
    void next() {
        m_it++;
    }
    
    bool isDone() {
        return (m_it == m_p_data->m_elemList.end());
    }
    
    iterType current() {
        return m_it;
    }

private:
    U* m_p_data;
    iterType m_it;
};

class IObserver
{
public:
    virtual ~IObserver(){};
    virtual void update(const string& messageFromSubject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject(){};
    virtual void attach(shared_ptr<IObserver> observer) = 0;
    virtual void detach(shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

class Subject : public ISubject {
public:
    virtual ~Subject() {
        cout << "Goodbye, I was the Subject." << endl;
    }
    virtual void attach(shared_ptr<IObserver> observer) override {
        m_listObserver.insert(observer);
    }
    virtual void detach(shared_ptr<IObserver> observer) override {
        m_listObserver.remove(observer);
    }
    virtual void notify() override {
        shared_ptr<Iterator<shared_ptr<IObserver>, RandomizedSet<shared_ptr<IObserver>>>> it = m_listObserver.createIterator();
        howManyObserver();
        for (it->first(); !it->isDone(); it->next()) {
                // auto el = *it->current();
                // el->update(m_message);
                (*it->current())->update(m_message);
            }
    }
    void createMessage(string message = "Empty") {
        m_message = message;
        notify();
    }
    void howManyObserver() {
        cout << "There are " << m_listObserver.size() << " observers in the list." << endl;
    }
    void someBusinessLogic() {
        m_message = "change message message";
        notify();
        cout << "I'm about to do some thing important" << endl;
    }
private:
    RandomizedSet<shared_ptr<IObserver>> m_listObserver;
    string m_message;
};

class Observer : public IObserver
{
public:
    Observer(Subject& subject) : m_subject(subject) {
        m_subject.attach(make_shared<Observer>(*this));
        cout << "Hi, I'm the Observer \"" << ++Observer::m_staticNumber << "\"." << endl;
        m_number = Observer::m_staticNumber;
    }
    virtual ~Observer() {
        cout << "Goodbye, I was the Observer \"" << m_number << "\"." << endl;
    }
    virtual void update(const string& messageFromSubject) override {
        m_messageFromSubject = messageFromSubject;
        printInfo();
    }
    void removeMeFromTheList() {
        m_subject.detach(make_shared<Observer>(*this));
        cout << "Observer \"" << m_number << "\" removed from the list." << endl;
    }
    void printInfo() {
        cout << "Observer \"" << m_number << "\": a new message is available --> " << m_messageFromSubject << endl;
    }
private:
    string m_messageFromSubject;
    Subject& m_subject;
    static int m_staticNumber;
    int m_number;
};

int Observer::m_staticNumber = 0;

void clientCode() {
    shared_ptr<Subject> subject = make_shared<Subject>();
    shared_ptr<Observer> observer1 = make_shared<Observer>(*subject);
    shared_ptr<Observer> observer2 = make_shared<Observer>(*subject);
    shared_ptr<Observer> observer3 = make_shared<Observer>(*subject);
    shared_ptr<Observer> observer4;
    shared_ptr<Observer> observer5;
    
    subject->createMessage("Hello World! :D");
    observer3->removeMeFromTheList();
    
    subject->createMessage("The weather is hot today! :p");
    observer4 = make_shared<Observer>(*subject);
    
    observer2->removeMeFromTheList();
    observer5 = make_shared<Observer>(*subject);
    
    subject->createMessage("My new car is great! ;)");
    observer5->removeMeFromTheList();
    
    observer4->removeMeFromTheList();
    observer1->removeMeFromTheList();
}

int main()
{
    clientCode();
    
    
    return 0;
}