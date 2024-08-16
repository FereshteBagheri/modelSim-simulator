#include "AndGate.h"

AndGate::AndGate(const string& id, const vector<Wire*>& inputs)
    : Gate(id, inputs) {}

void AndGate::evaluate() {
    bool hasZ = false;   
    bool result = true;  

    for (Wire* input : inputWires) {
        auto inputVal = input->getOutput();

        if (!inputVal.has_value()) {
            hasZ = true;  
        } else if (!inputVal.value()) {
            result = false;  
            break;  
        }
    }

    if (result && hasZ) {
        this->outputWire->setValue(nullopt);  
    } else {
        this->outputWire->setValue(result);  
    }

    this->outputWire->evaluate();  
}
