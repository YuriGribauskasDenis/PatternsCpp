
#include <iostream>
#include <string>
#include <memory>

using namespace std;
 
class Student
{
public:  
    Student(string name, float id) : m_name(name), m_id(id) {}
    const string getName() const { return m_name; }
    const int getID() const { return m_id; }
private:
    string m_name;
    float m_id;
};

class Details
{
public:
    Details(int stdclass, string section, unique_ptr<Student> std)
        : mp_student{move(std)},
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
    unique_ptr<Student> mp_student;
    int m_studentClass;
    string m_section;
};

int main()
{
    unique_ptr<Student> s1 = make_unique<Student>("Khush", 1);
    unique_ptr<Details> d1 = make_unique<Details>(6, "A", move(s1));
    d1->detail();



    return 0;
}