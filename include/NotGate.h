#ifndef NOT_GATE_H
#define NOT_GATE_H

#include "Gate.h"

class NotGate : public Gate {
public:
    NotGate(const string& id, Wire* input, Wire* output);

    optional<bool> evaluate() override;
};

#endif 
