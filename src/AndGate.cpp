#include "AndGate.h"

AndGate::AndGate(const string& id, const vector<Wire*>& inputs)
    : Gate(id, inputs) {}

void AndGate::evaluate() {
    bool hasZ = false;   // To check if any input is undefined
    bool result = true;  // To store the result of the AND operation

    for (Wire* input : inputWires) {
        auto inputVal = input->getOutput();

        if (!inputVal.has_value()) {
            hasZ = true;  // Mark as undefined if any input is undefined
        } else if (!inputVal.value()) {
            result = false;  // If any input is false, the result is false
            break;  // No need to continue checking
        }
    }

    if (result && hasZ) {
        this->outputWire->setValue(nullopt);  // Set output to undefined if all inputs are true but one is undefined
    } else {
        this->outputWire->setValue(result);  // Set output to the result of the AND operation
    }

    this->outputWire->evaluate();  // Propagate the result through the circuit
}
