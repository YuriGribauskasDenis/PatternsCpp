
#include <iostream>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include <memory>

using namespace std;

class SharedData
{
public:
    SharedData(const string &brand, const string &model, const string &color)
        : m_brand(brand), m_model(model), m_color(color)
    {
    }
    void report() const {
        cout << "[ " << m_brand << " , " << m_model << " , " << m_color << " ]" << endl;
    }
    string getBrand() const {
        return m_brand;
    }
    string getModel() const {
        return m_model;
    }
    string getColor() const {
        return m_color;
    }
private:
    string m_brand;
    string m_model;
    string m_color;
};

class UniqueData
{
public:
    UniqueData(const string &owner, const string &plates)
        : m_owner(owner), m_plates(plates)
    {
    }
    void report() const {
        cout << "[ " << m_owner << " , " << m_plates << " ]" << endl;
    }
private:
    string m_owner;
    string m_plates;
};

class Flyweight
{
public:
    Flyweight(const SharedData* sharedData) : mp_sharedData(new SharedData(*sharedData)) {}
    Flyweight(const Flyweight& other) : mp_sharedData(new SharedData(*other.mp_sharedData)) {}
    ~Flyweight() { delete mp_sharedData; }
    SharedData* getSharedData() const { return mp_sharedData; }
    void report(const UniqueData& uniqueData) const {
        cout << "Flyweight: Displaying shared" << endl;
        (*mp_sharedData).report();
        cout << "and unique" << endl;
        uniqueData.report();
    }
private:
    SharedData* mp_sharedData;
};

class FlyweightFactory
{
public:
    FlyweightFactory(initializer_list<SharedData> shareDatas) {
        for (const SharedData& element : shareDatas)
        {
            m_flyweights.insert(make_pair<string, Flyweight>(GetKey(element), Flyweight(&element)));
        }
    }
    Flyweight GetFlyweight(const SharedData& sharedData) {
        string key = GetKey(sharedData);
        if (m_flyweights.find(key) == m_flyweights.end()) {
            cout << "FlyweightFactory: Can't find a flyweight, creating new one." << endl;
            m_flyweights.insert(make_pair(key, Flyweight(&sharedData)));
        } else {
            cout << "FlyweightFactory: Reusing existing flyweight." << endl;
        }
        return m_flyweights.at(key);
    }
    void ListFlyweights() const {
        size_t count = m_flyweights.size();
        cout << "FlyweightFactory: I have " << count << " flyweights:" << endl;
        for (pair<string, Flyweight> pair : m_flyweights) {
            cout << pair.first << endl;
        }
    }
private:
    unordered_map<string, Flyweight> m_flyweights;
    string GetKey(const SharedData& obj) const {
        return obj.getBrand() + "_" + obj.getModel() + "_" + obj.getColor();
    }
};

void AddCarToPoliceDatabase(
    FlyweightFactory& ff, const string& plates, const string& owner,
    const string& brand, const string& model, const string& color)
{
    cout << endl << "Client: Adding a car to database." << endl;
    const Flyweight& flyweight = ff.GetFlyweight({brand, model, color});
    // The client code either stores or calculates extrinsic state and passes it
    // to the flyweight's methods.
    flyweight.report({owner, plates});
}

/**
 * The client code usually creates a bunch of pre-populated flyweights in the
 * initialization stage of the application.
 */

int main()
{
    FlyweightFactory* factory = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    factory->ListFlyweights();

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");
    factory->ListFlyweights();
    delete factory;

    return 0;
}