#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <optional>
#include <string>

using namespace std;

class Component {
protected:
    string id;
    optional<bool> output;
    

public:
vector<Component*> connectedComponents;
    Component(const string& id);

    virtual void evaluate() = 0;

    void addConnectedComponent(Component* comp);
    void notifyConnectedComponents();

    optional<bool> getOutput() const;
    const string& getId() const;
};

#endif 
