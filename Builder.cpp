
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Bradley
{
public:
    vector<string> m_parts;
    void ListParts() const {
        cout << "Part List:" << endl;
        for (const auto& part : m_parts) {
            cout << part << " ";
        }
        cout << endl;
    }
private:
};

class AbstractMovingBuilder
{
public:
    virtual void ProduceChassee() const = 0;
    virtual void ProduceWheels() const = 0;
    virtual void ProduceTransmission() const = 0;
};
class AbstractBodyBuilder
{
public:
    virtual void ProduceBody() const = 0;
    virtual void ProduceMedBlock() const = 0;
    virtual void ProduceRadioBlock() const = 0;
    virtual void ProduceInfBlock() const = 0;
};
class AbstracTurrettBuilder
{
public:
    virtual void ProduceTurret() const = 0;
    virtual void ProduceAT() const = 0;
    virtual void ProduceGun() const = 0;
    virtual void ProduceMG() const = 0;
};

class BradleyBuilder : public AbstractMovingBuilder, AbstractBodyBuilder, AbstracTurrettBuilder
{
public:
    BradleyBuilder() {
        Init();
    }
    ~BradleyBuilder() {
        delete m_bradley;
    }
    virtual void ProduceChassee() const override {
        m_bradley->m_parts.push_back("Chassee");
    }
    virtual void ProduceWheels() const override {
        m_bradley->m_parts.push_back("Wheels");
    }
    virtual void ProduceTransmission() const override {
        m_bradley->m_parts.push_back("Transmission");
    }
    virtual void ProduceBody() const override {
        m_bradley->m_parts.push_back("Body");
    }
    
    virtual void ProduceMedBlock() const override {
        m_bradley->m_parts.push_back("MedBlock");
    }
    virtual void ProduceRadioBlock() const override {
        m_bradley->m_parts.push_back("RadioBlock");
    }
    virtual void ProduceInfBlock() const override {
        m_bradley->m_parts.push_back("InfBlock");
    }
    
    virtual void ProduceTurret() const override {
        m_bradley->m_parts.push_back("Turret");
    }

    virtual void ProduceAT() const override {
        m_bradley->m_parts.push_back("AT");
    }
    virtual void ProduceGun() const override {
        m_bradley->m_parts.push_back("Gun");
    }
    virtual void ProduceMG() const override {
        m_bradley->m_parts.push_back("MG");
    }
    Bradley* GetBradely() {
        Bradley* result = m_bradley;
        Init();
        return result;
    }
private:
    Bradley* m_bradley;
    void Init() {
        m_bradley = new Bradley();
    }
};

class Director
{
public:
    void setBuilder(BradleyBuilder* bradleyBuilder){
        mp_bradleyBuilder = bradleyBuilder;
    }
    void BuildMedBradley() {
        mp_bradleyBuilder->ProduceChassee();
        mp_bradleyBuilder->ProduceBody();
        mp_bradleyBuilder->ProduceMedBlock();
        mp_bradleyBuilder->ProduceMG();
    }
    void BuildScoutBradley() {
        mp_bradleyBuilder->ProduceChassee();
        mp_bradleyBuilder->ProduceBody();
        mp_bradleyBuilder->ProduceRadioBlock();
        mp_bradleyBuilder->ProduceTurret();
        mp_bradleyBuilder->ProduceGun();
        mp_bradleyBuilder->ProduceMG();
    }
    void BuildInfBradley() {
        mp_bradleyBuilder->ProduceChassee();
        mp_bradleyBuilder->ProduceBody();
        mp_bradleyBuilder->ProduceInfBlock();
        mp_bradleyBuilder->ProduceTurret();
        mp_bradleyBuilder->ProduceGun();
        mp_bradleyBuilder->ProduceAT();
        mp_bradleyBuilder->ProduceMG();
    }
private:
    BradleyBuilder* mp_bradleyBuilder;
};

void ClientCode(Director& director) {
    BradleyBuilder* bradleyBuilder = new BradleyBuilder();
    director.setBuilder(bradleyBuilder);
    
    cout << "Med base product:" << endl; 
    director.BuildMedBradley();
    
    Bradley* b = bradleyBuilder->GetBradely();
    b->ListParts();
    delete b;

    cout << endl; 
    
    cout << "Scout base product:" << endl; 
    director.BuildScoutBradley();

    b = bradleyBuilder->GetBradely();
    b->ListParts();
    delete b;

    cout << endl; 

    cout << "Custom product, no director:" << endl; 
    bradleyBuilder->ProduceWheels();
    bradleyBuilder->ProduceBody();
    bradleyBuilder->ProduceInfBlock();
    bradleyBuilder->ProduceTurret();
    bradleyBuilder->ProduceGun();
    b = bradleyBuilder->GetBradely();
    b->ListParts();
    delete b;

    delete bradleyBuilder;
    bradleyBuilder = nullptr;
}

int main()
{
    Director* director = new Director();
    ClientCode(*director);
    delete director;

    return 0;
}