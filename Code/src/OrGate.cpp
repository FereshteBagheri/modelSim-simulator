#include "OrGate.h"

OrGate::OrGate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Gate(id, inputs, output) {}

optional<bool> OrGate::evaluate() {
    bool hasZ = false;
    bool result = false;

    for (Wire* input : inputWires) {
        optional<bool> inputVal = input->evaluate();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (inputVal.value()) {
            result = true;
            break;
        }
    }

    if (!result && hasZ) {
        return nullopt;  
    } else {
        return result;
    }
}
