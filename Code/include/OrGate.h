#ifndef OR_GATE_H
#define OR_GATE_H

#include "Gate.h"

class OrGate : public Gate {
public:
    OrGate(const string& id, const vector<Wire*>& inputs, Wire* output);

    optional<bool> evaluate() override;
};

#endif
