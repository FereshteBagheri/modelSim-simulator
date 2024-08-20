#ifndef XOR_GATE_H
#define XOR_GATE_H

#include "Gate.h"

class XorGate : public Gate {
public:
    XorGate(const string& id, const vector<Wire*>& inputs);
    optional<bool> evaluate() override;
};

#endif 
