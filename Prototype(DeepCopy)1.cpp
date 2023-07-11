
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

enum Type {
    // Because Space Marine is never a Zero
    MARINETYPE_1 = 1,
    MARINETYPE_2,
    MARINETYPE_3
};

class ClonableSpaceMarine
{
public:
    ClonableSpaceMarine() {}
    ClonableSpaceMarine(string typeName)
        : m_typeName(typeName) { }
    virtual ~ClonableSpaceMarine() {}
    virtual ClonableSpaceMarine* Clone() const = 0;
    virtual void SetTypeField(float typeField) {
        m_typeField = typeField;
        cout << "Call SetTypeField from " << m_typeName <<
        " with field : " << m_typeField << endl;
    }
private:
    string m_typeName;
    float m_typeField;
};

class Marauder : public ClonableSpaceMarine
{
public:
    Marauder(string typeName, float typeField)
        : ClonableSpaceMarine(typeName), m_typeFieldMortaire(typeField) { }
    virtual Marauder *Clone() const override {
        return new Marauder(*this);
    }
private:
    float m_typeFieldMortaire;
};

class Ghost : public ClonableSpaceMarine
{
public:
    Ghost(string typeName, float typeField)
        : ClonableSpaceMarine(typeName), m_typeFieldSniper(typeField) { }
    virtual Ghost *Clone() const override {
        return new Ghost(*this);
    }
private:
    float m_typeFieldSniper;
};

class Marine : public ClonableSpaceMarine
{
public:
    Marine(string typeName, float typeField)
        : ClonableSpaceMarine(typeName), m_typeFieldAssault(typeField) { }
    virtual Marine *Clone() const override {
        return new Marine(*this);
    }
private:
    float m_typeFieldAssault;
};


class MarineFactory {
public:
    MarineFactory() {
        m_marineTypes[Type::MARINETYPE_1] = new Ghost("MARINETYPE_1 ", 50.f);
        m_marineTypes[Type::MARINETYPE_2] = new Marauder("MARINETYPE_2 ", 60.f);
        m_marineTypes[Type::MARINETYPE_3] = new Marauder("MARINETYPE_3 ", 70.f);
    }

    ~MarineFactory() {
        delete m_marineTypes[Type::MARINETYPE_1];
        delete m_marineTypes[Type::MARINETYPE_2];
        delete m_marineTypes[Type::MARINETYPE_3];
    }

    ClonableSpaceMarine* CreateSpaceMarine(Type type) {
        return m_marineTypes[type]->Clone();
    }
 private:
    unordered_map<Type, ClonableSpaceMarine*, std::hash<int>> m_marineTypes;
};

void Client(MarineFactory& marineFactory) {
    cout << "Blastin' time!" << endl;

    ClonableSpaceMarine *clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_1);
    clone->SetTypeField(110);
    delete clone;
    
    cout << endl;
    
    cout << "You called down the thunder..." << endl;
    
    clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_2);
    clone->SetTypeField(90);
    delete clone;
    
    cout << endl;
    
    cout << "You wanna piece of me, boy?" << endl;
    
    clone = marineFactory.CreateSpaceMarine(Type::MARINETYPE_3);
    clone->SetTypeField(90);
    delete clone;
}

int main() {
  MarineFactory* marineFactory = new MarineFactory();
  Client(*marineFactory);
  delete marineFactory;

  return 0;
}