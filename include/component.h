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
    Component(const string& id);
    Component(const string& id, optional<bool> output);

    virtual void evaluate() = 0;
    virtual void addInput(Component* input) = 0;

    optional<bool> getOutput() const;
    const string& getId() const;
    
};

#endif
