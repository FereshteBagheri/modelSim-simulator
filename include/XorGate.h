#ifndef XOR_GATE_H
#define XOR_GATE_H

#include "Gate.h"

class XorGate : public Gate {
public:
    XorGate(const string& id, const vector<Wire*>& inputs);
    void evaluate() override;
};

#endif // XOR_GATE_H
