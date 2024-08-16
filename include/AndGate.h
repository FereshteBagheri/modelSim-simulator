#ifndef AND_GATE_H
#define AND_GATE_H

#include "Gate.h"

class AndGate : public Gate {
public:
    
    AndGate(const string& id, const vector<Wire*>& inputs);

    
    void evaluate() override;
};

#endif 
