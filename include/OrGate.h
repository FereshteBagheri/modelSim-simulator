#ifndef OR_GATE_H
#define OR_GATE_H

#include "Gate.h"

class OrGate : public Gate {
public:
    OrGate(const string& id, const vector<Component*>& inputs);

    void evaluate() override;
};

#endif // OR_GATE_H
