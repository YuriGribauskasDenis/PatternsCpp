
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class TerranSatelite
{
public:
    virtual ~TerranSatelite() = default;
    virtual string report() const {
        return "Functioning well";
    }
};

class ZergSatelite
{
public:
    virtual string report() const = 0;
};

class ZergNavySatelite : public ZergSatelite
{
public:
    virtual string report() const override {
        return "Cvvcem\"Gctvj";
    }
};

class ZergTransmitionSatelite : public ZergSatelite
{
public:
    virtual string report() const override {
        return "Mknn\"Cnn\"Jwocp";
    }
};

class TerranIntersectionSatelite : public TerranSatelite
{
public:
    TerranIntersectionSatelite() : m_decypherTarget(nullptr) {}
    void setTarget(shared_ptr<ZergSatelite> target) {
        m_decypherTarget = target;
    }
    // void setTarget(ZergSatelite* target) {
    //     m_decypherTarget = shared_ptr<ZergSatelite>(target);
    // }
    virtual string report() const override {
        string msg = m_decypherTarget->report();
        decypher(msg);
        return msg;
    }
private:
    void decypher(string& str) const {
        for (int i = 0; i < str.length(); i++) {
            str[i] = str[i] - 'a' - 2 + 'a';
        }
    }
    shared_ptr<ZergSatelite> m_decypherTarget;
};

void ClientCode(const TerranSatelite& worker) {
  cout << worker.report() << endl;
}

int main()
{
    // TerranSatelite ts;
    // cout << ts.report() << endl;

    shared_ptr<TerranSatelite> workstation = make_shared<TerranSatelite>();
    ClientCode(*workstation);
    cout << endl;
    
    shared_ptr<ZergSatelite> target = make_shared<ZergNavySatelite>();
    cout << target->report() << endl;
    shared_ptr<TerranIntersectionSatelite> spySatelite = make_shared<TerranIntersectionSatelite>();
    spySatelite->setTarget(target);
    // spySatelite->setTarget(&*target);
    ClientCode(*spySatelite);
    cout << endl;
    
    target = make_shared<ZergTransmitionSatelite>();
    cout << target->report() << endl;
    spySatelite->setTarget(target);
    // spySatelite->setTarget(&*target);
    ClientCode(*spySatelite);

    return 0;
}