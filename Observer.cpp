
#include <iostream>
#include <list>
#include <string>

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
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};

class Subject : public ISubject {
public:
    virtual ~Subject() {
        cout << "Goodbye, I was the Subject." << endl;
    }
    virtual void attach(IObserver* observer) override {
        m_listObserver.push_back(observer);
    }
    virtual void detach(IObserver* observer) override {
        m_listObserver.remove(observer);
    }
    virtual void notify() override {
        list<IObserver*>::iterator iterator = m_listObserver.begin();
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
    list<IObserver*> m_listObserver;
    string m_message;
};

class Observer : public IObserver
{
public:
    Observer(Subject& subject) : m_subject(subject) {
        m_subject.attach(this);
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
        m_subject.detach(this);
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
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;
    
    subject->createMessage("Hello World! :D");
    observer3->removeMeFromTheList();
    
    subject->createMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);
    
    observer2->removeMeFromTheList();
    observer5 = new Observer(*subject);
    
    subject->createMessage("My new car is great! ;)");
    observer5->removeMeFromTheList();
    
    observer4->removeMeFromTheList();
    observer1->removeMeFromTheList();
    
    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    clientCode();
    
    
    return 0;
}