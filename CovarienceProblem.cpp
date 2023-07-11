
#include <iostream>
#include <memory>

using namespace std;

class Clonable
{
public:
    shared_ptr<Clonable> Clone() const {
        return shared_ptr<Clonable>(this->underHoodClone());
    }
private:
    virtual Clonable* underHoodClone() const = 0;
};

class Frog : public Clonable
{
public:
    shared_ptr<Frog> Clone() const {
        return shared_ptr<Frog>(this->underHoodClone());
    }
private:
    virtual Frog* underHoodClone() const override {
        return new Frog(*this);
    }
};

class Sheep : public Clonable
{
public:
    shared_ptr<Sheep> Clone() const {
        return shared_ptr<Sheep>(this->underHoodClone());
    }
private:
    virtual Sheep* underHoodClone() const override {
        return new Sheep(*this);
    }
};

void checkCountCopyArg(shared_ptr<Clonable> c) {
    cout << c.use_count() << endl;
}
void checkCountRefArg(const shared_ptr<Clonable>& c) {
    cout << c.use_count() << endl;
}

int main()
{
    shared_ptr<Frog> c = make_shared<Frog>();
    cout << c.use_count() << endl;
    checkCountCopyArg(c);
    checkCountRefArg(c);
    shared_ptr<Frog> c2 = c->Clone();
    checkCountRefArg(c);
    checkCountRefArg(c2);
    
    // Clonable* p = c.get();
    Clonable* p = &*c;
    checkCountRefArg(c);
    shared_ptr<Clonable> pp = p->Clone();
    checkCountRefArg(pp);


    return 0;
}