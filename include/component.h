#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>

using namespace std;

class Component {
protected:
    int componentId;
    vector<bool> inputs;
    bool output;

public:
    Component(int id, const vector<bool>& inputs, bool output);
    virtual bool evaluate() = 0;
    bool getOutput() const;
};

#endif // COMPONENT_H
