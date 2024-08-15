#ifndef GATE_H
#define GATE_H

#include "Component.h"
#include <vector>

using namespace std;

class Gate : public Component {
protected:
    vector<Component*> inputComponents;

public:
    Gate(const string& id, const vector<Component*>& inputs);
    void connectInput(Component* input);
    void connectInputs(const vector<Component*>& inputs);
    virtual void evaluate() override = 0;
};

#endif 
