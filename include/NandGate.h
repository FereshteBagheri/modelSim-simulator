#ifndef NAND_GATE_H
#define NAND_GATE_H

#include "Gate.h"

class NandGate : public Gate {
public:
    NandGate(const string& id, const vector<Wire*>& inputs);
    optional<bool> evaluate() override;
};

#endif 
