
#include <iostream>
#include <memory>

using namespace std;

class Pilot
{
public:
    Pilot() {cout << "P+" << endl;}
    ~Pilot() {cout << "P-" << endl;}
    void SetCopilot(const weak_ptr<Pilot>& other) {
        copilot = other;
    }
private:
    weak_ptr<Pilot> copilot;
};

int main()
{
    shared_ptr<Pilot> Tom = make_shared<Pilot>();
    shared_ptr<Pilot> Cruse = make_shared<Pilot>();
    
    //circular dependencies i.e. memory leaks
    Tom->SetCopilot(Cruse);
    Cruse->SetCopilot(Tom);

    return 0;
}