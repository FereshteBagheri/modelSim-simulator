#include "XorGate.h"

XorGate::XorGate(const string& id, const vector<Wire*>& inputs)
    : Gate(id, inputs) {}

void XorGate::evaluate() {
    bool result = false;
    bool hasZ = false;

    for (Wire* input : inputWires) {
        auto inputVal = input->getOutput();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else {
            result ^= inputVal.value();
        }
    }

    if (hasZ) {
        this->outputWire->setValue(nullopt);
    } else {
        this->outputWire->setValue(result);
    }

    this->outputWire->evaluate();
}
