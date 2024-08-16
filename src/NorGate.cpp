#include "NorGate.h"

NorGate::NorGate(const string& id, const vector<Wire*>& inputs)
    : Gate(id, inputs) {}

void NorGate::evaluate() {
    bool result = false;
    bool hasZ = false;

    for (Wire* input : inputWires) {
        auto inputVal = input->getOutput();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (inputVal.value()) {
            result = true;
            break;
        }
    }

    if (hasZ) {
        this->outputWire->setValue(nullopt);
    } else {
        this->outputWire->setValue(!result);
    }

    this->outputWire->evaluate();
}
