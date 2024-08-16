#ifndef NOR_GATE_H
#define NOR_GATE_H

#include "Gate.h"

class NorGate : public Gate {
public:
    NorGate(const string& id, const vector<Wire*>& inputs);
    void evaluate() override;
};

#endif 
