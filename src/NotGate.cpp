#include "NotGate.h"

NotGate::NotGate(const string& id, Wire* input)
    : Gate(id, {input}) {}

void NotGate::evaluate() {
    auto inputVal = inputWires[0]->getOutput();  

    if (!inputVal.has_value()) {
        this->outputWire->setValue(nullopt);  
    } else {
        this->outputWire->setValue(!inputVal.value());  
    }

    this->outputWire->evaluate();  
}
