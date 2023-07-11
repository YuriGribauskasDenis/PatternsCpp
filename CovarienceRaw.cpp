
#include <iostream>

using namespace std;

class Clonable
{
public:
    virtual Clonable* Clone() const = 0;
    virtual void sound() const {
        cout << "What am I?" << endl;
    }
};

class Frog : public Clonable
{
public:
    virtual Frog* Clone() const override {
        return new Frog(*this);
    }
    virtual void sound() const override {
        cout << "Kwewet" << endl;
    }
};

class Sheep : public Clonable
{
public:
    virtual Sheep* Clone() const override {
        return new Sheep(*this);
    }
    virtual void sound() const override {
        cout << "Beeeee" << endl;
    }
};

int main()
{
    Frog* c = new Frog();
    c->sound();
    Frog* c2 = c->Clone();
    c2->sound();
    
    Clonable* p = c;
    p->sound();
    Clonable* pp = p->Clone();
    pp->sound();
    
    delete c;
    delete c2;
    delete pp;

    return 0;
}