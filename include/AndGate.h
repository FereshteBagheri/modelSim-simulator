#ifndef AND_GATE_H
#define AND_GATE_H

#include "Gate.h"

class AndGate : public Gate {
public:
    // Constructor using the Gate constructor
    AndGate(const string& id, const vector<Wire*>& inputs);

    // Override the evaluate method to perform AND logic
    void evaluate() override;
};

#endif // AND_GATE_H
