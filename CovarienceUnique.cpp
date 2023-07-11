
#include <iostream>
#include <memory>

using namespace std;

class Clonable
{
public:
    unique_ptr<Clonable> Clone() const {
        return unique_ptr<Clonable>(this->underHoodClone());
    }
    virtual void sound() const {
        cout << "What am I?" << endl;
    }
private:
    virtual Clonable* underHoodClone() const = 0;
};

class Frog : public Clonable
{
public:
    unique_ptr<Frog> Clone() const {
        return unique_ptr<Frog>(this->underHoodClone());
    }
    virtual void sound() const override {
        cout << "Kwewet" << endl;
    }
private:
    virtual Frog* underHoodClone() const override {
        return new Frog(*this);
    }
};

class Sheep : public Clonable
{
public:
    unique_ptr<Sheep> Clone() const {
        return unique_ptr<Sheep>(this->underHoodClone());
    }
    virtual void sound() const override {
        cout << "Beeeeee" << endl;
    }
private:
    virtual Sheep* underHoodClone() const override {
        return new Sheep(*this);
    }
};

int main()
{
    unique_ptr<Frog> c = make_unique<Frog>();
    c->sound();
    unique_ptr<Frog> c2 = c->Clone();
    c2->sound();
    
    // Clonable* p = c.get();
    Clonable* p = &*c;
    p->sound();
    unique_ptr<Clonable> pp = p->Clone();
    pp->sound();


    return 0;
}