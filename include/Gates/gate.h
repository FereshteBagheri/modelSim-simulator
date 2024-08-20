#ifndef GATE_H
#define GATE_H

#include "Component.h"
#include "Wire.h"
#include <vector>

using namespace std;

class Gate : public Component {
protected:
    vector<Wire*> inputWires;
    Wire* outputWire;

public:
    Gate(const string& id, const vector<Wire*>& inputs, Wire* output);
    
    void connectInput(Wire* input);
    void connectInputs(const vector<Wire*>& inputs);
    
    Wire* getOutputWire() const;

    virtual optional<bool> evaluate() override = 0;
};

#endif 
