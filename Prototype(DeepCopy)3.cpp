
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

enum Type {
    MARINETYPE_0 = 0,
    MARINETYPE_1 = 1,
    MARINETYPE_2 = 2
};

class ClonableSpaceMarine
{
public:
    ClonableSpaceMarine() {}
    ClonableSpaceMarine(string typeName)
        : m_typeName(typeName) { }
    virtual ~ClonableSpaceMarine() {}
    shared_ptr<ClonableSpaceMarine> Clone() const {
        return shared_ptr<ClonableSpaceMarine>(this->underHoodClone());
    }
    void SetTypeField(float typeHealth) {
        m_typeHealth = typeHealth;
        cout << "Call SetTypeField from " << m_typeName <<
        " with health : " << m_typeHealth << endl;
    }
    virtual void SetHealthBoost(float hBoost) = 0;
    virtual const float& GetHealthBoost() const = 0;
private:
    virtual ClonableSpaceMarine* underHoodClone() const = 0;
    string m_typeName;
    float m_typeHealth;
};

class Marauder : public ClonableSpaceMarine
{
public:
    Marauder(string typeName, float hBoost)
        : ClonableSpaceMarine(typeName), m_healthBoostMortaire(hBoost) { }
    shared_ptr<Marauder> Clone() const {
        return shared_ptr<Marauder>(this->underHoodClone());
    }
    virtual void SetHealthBoost(float hBoost) override {
        m_healthBoostMortaire = hBoost;
    }
    virtual const float& GetHealthBoost() const override {
        return m_healthBoostMortaire;
    }
private:
    virtual Marauder* underHoodClone() const override {
        return new Marauder(*this);
    }
    float m_healthBoostMortaire;
};

class Ghost : public ClonableSpaceMarine
{
public:
    Ghost(string typeName, float hBoost)
        : ClonableSpaceMarine(typeName), m_healthBoostSniper(hBoost) { }
    shared_ptr<Ghost> Clone() const {
        return shared_ptr<Ghost>(this->underHoodClone());
    }
    virtual void SetHealthBoost(float hBoost) override {
        m_healthBoostSniper = hBoost;
    }
    virtual const float& GetHealthBoost() const override {
        return m_healthBoostSniper;
    }
private:
    virtual Ghost* underHoodClone() const override {
        return new Ghost(*this);
    }
    float m_healthBoostSniper;
};

class Marine : public ClonableSpaceMarine
{
public:
    Marine(string typeName, float hBoost)
        : ClonableSpaceMarine(typeName), m_healthBoostAssault(hBoost) { }
    shared_ptr<Marine> Clone() const {
        return shared_ptr<Marine>(this->underHoodClone());
    }
    virtual void SetHealthBoost(float hBoost) override {
        m_healthBoostAssault = hBoost;
    }
    virtual const float& GetHealthBoost() const override {
        return m_healthBoostAssault;
    }
private:
    virtual Marine* underHoodClone() const override {
        return new Marine(*this);
    }
    float m_healthBoostAssault;
};


class MarineFactory {
public:
    MarineFactory() {
        m_marineTypes.reserve(3);
        m_marineTypes.emplace_back(make_unique<Ghost>("MARINETYPE_0 ", 50.f));
        m_marineTypes.emplace_back(make_unique<Marauder>("MARINETYPE_1 ", 60.f));
        m_marineTypes.emplace_back(make_unique<Marine>("MARINETYPE_2 ", 70.f));
    }
    ~MarineFactory() { }

    shared_ptr<ClonableSpaceMarine> CreateSpaceMarine(Type type) {
        return m_marineTypes[type]->Clone();
    }
 private:
    vector<unique_ptr<ClonableSpaceMarine>> m_marineTypes;
};

void Client(MarineFactory& marineFactory) {
    cout << "Blastin' time!" << endl;

    shared_ptr<ClonableSpaceMarine> clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_0);
    clone->SetTypeField(110);
    
    cout << endl;
    
    cout << "You called down the thunder..." << endl;
    
    clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_1);
    clone->SetTypeField(80);
    
    cout << endl;
    
    cout << "You wanna piece of me, boy?" << endl;
    
    clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_2);
    clone->SetTypeField(90);
}

int main() {
  unique_ptr<MarineFactory> marineFactory = make_unique<MarineFactory>();
  Client(*marineFactory);

  return 0;
}