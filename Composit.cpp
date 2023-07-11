
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <memory>

using namespace std;

class GraphicsUnit
{
public:
    GraphicsUnit() : m_parent(nullptr) {}
    virtual ~GraphicsUnit() {}
    void setParent(shared_ptr<GraphicsUnit> parent) {
        m_parent = parent;
    }
    shared_ptr<GraphicsUnit>& getParent() {
        return m_parent;
    }
    virtual void addComponent(const shared_ptr<GraphicsUnit>&) {}
    virtual void removeComponent(const shared_ptr<GraphicsUnit>&) {}
    virtual bool isGroup() const { return false; }
    virtual string render() const = 0;
private:
    shared_ptr<GraphicsUnit> m_parent;
};

class Cube : public GraphicsUnit
{
public:
    virtual string render() const override {
        return "Cube";
    }
};

class Sphere : public GraphicsUnit
{
public:
    virtual string render() const override {
        return "Sphere";
    }
};

class Group : public GraphicsUnit
{
public:
    virtual void addComponent(const shared_ptr<GraphicsUnit>& gUnit) override {
        m_children.push_back(gUnit);
    }
    virtual void removeComponent(const shared_ptr<GraphicsUnit>& gUnit) override {
        m_children.remove(gUnit);
        gUnit->setParent(nullptr);
    }
    virtual bool isGroup() const override { return true; }
    virtual string render() const override {
        string res;
        for (const auto& child : m_children) {
            res += child->render() + " ";
        }
        return "Group ( " + res + " )";
    }
private:
    list<shared_ptr<GraphicsUnit>> m_children;
};

void ClientCode(GraphicsUnit& gunt) {
    cout << "Rendered: " << gunt.render() << endl;
}

void ClientCode2(shared_ptr<GraphicsUnit> guntB, shared_ptr<GraphicsUnit> guntS) {
    if (guntB->isGroup()) {
        guntB->addComponent(guntS);
    }
    cout << "Rendered: " << guntB->render() << endl;
}

int main()
{
    shared_ptr<GraphicsUnit> simple = make_shared<Cube>();
    ClientCode(*simple);
    cout << endl;

    shared_ptr<GraphicsUnit> tree = make_shared<Group>();

    shared_ptr<GraphicsUnit> branch1 = make_shared<Group>();
    branch1->addComponent(make_shared<Cube>());
    branch1->addComponent(make_shared<Cube>());
    branch1->addComponent(make_shared<Sphere>());
    
    shared_ptr<GraphicsUnit> branch2 = make_shared<Group>();
    branch2->addComponent(make_shared<Sphere>());
    branch2->addComponent(make_shared<Cube>());

    tree->addComponent(make_shared<Sphere>());
    tree->addComponent(branch1);
    tree->addComponent(branch2);
    
    ClientCode(*tree);
    cout << endl;

    ClientCode2(tree, simple);
    cout << endl;
    
    ClientCode(*tree);

    return 0;
}