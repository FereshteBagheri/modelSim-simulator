#include "OrGate.h"

OrGate::OrGate(const string& id, const vector<Wire*>& inputs)
    : Gate(id, inputs) {}

void OrGate::evaluate() {
    bool hasZ = false;
    bool result = false;

    for (Wire* input : inputWires) {
        auto inputVal = input->getOutput();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (inputVal.value()) {
            result = true;
            break;
        }
    }

    if (!result && hasZ) {
        this->outputWire->setValue(nullopt);  
    } else {
        this->outputWire->setValue(result);  
    }

    this->outputWire->evaluate();  
}
