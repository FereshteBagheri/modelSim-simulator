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
        this->outputWire->setValue(nullopt);  // Set output to undefined if no input is true and one is undefined
    } else {
        this->outputWire->setValue(result);  // Set output to true if any input is true, else false
    }

    this->outputWire->evaluate();  // Propagate the result through the circuit
}
