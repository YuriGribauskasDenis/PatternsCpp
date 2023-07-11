
#include <iostream>
#include <list>
#include <string>
#include <memory>

using namespace std;
  
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
        m_listObserver.push_back(observer);
    }
    virtual void detach(shared_ptr<IObserver> observer) override {
        m_listObserver.remove(observer);
    }
    virtual void notify() override {
        list<shared_ptr<IObserver>>::iterator iterator = m_listObserver.begin();
        howManyObserver();
    while (iterator != m_listObserver.end()) {
        (*iterator)->update(m_message);
        ++iterator;
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
    list<shared_ptr<IObserver>> m_listObserver;
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