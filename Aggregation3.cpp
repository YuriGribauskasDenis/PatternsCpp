
#include <iostream>
#include <string>
#include <memory>

using namespace std;
 
class Student
{
public:  
    Student(string name, float id) : m_name(name), m_id(id) {}
    ~Student() { cout << "S-" << endl; }
    const string getName() const { return m_name; }
    const int getID() const { return m_id; }
private:
    string m_name;
    float m_id;
};

class Details
{
public:
    Details(int stdclass, string section, shared_ptr<Student> std)
        : mp_student{std},
          m_studentClass{stdclass},
          m_section{section}
    { }
    void detail() const
    {
        cout << "Student Class : " << m_studentClass << endl;
        cout << "Student Section : " << m_section << endl;
        cout << "Student Name : " << mp_student->getName()<< endl;
        cout << "Student ID : "<< mp_student->getID() << endl;
    }
private:
    shared_ptr<Student> mp_student;
    int m_studentClass;
    string m_section;
};

int main()
{
    shared_ptr<Student> s1 = nullptr;
    cout << s1.use_count() << endl;
    {
        s1 = make_shared<Student>("Khush", 1);
        cout << s1.use_count() << endl;
        unique_ptr<Details> d1 = make_unique<Details>(6, "A", s1);
        cout << s1.use_count() << endl;
        d1->detail();
    }
    cout << s1.use_count() << endl;


    return 0;
}