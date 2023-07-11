
#include <iostream>
#include <memory>

using namespace std;

class B
{
public:
    virtual void report() const {
        cout << "Base online" << endl;
    }
};

class D : public B
{
public:
    virtual void report() const {
        cout << "Derived online" << endl;
    }
};

int main()
{
    // all equivalent
    // unique_ptr<B> p(new D);
    // unique_ptr<B> p = unique_ptr<D>(new D);
    unique_ptr<B> p = make_unique<D>();
    p->report();

    return 0;
}