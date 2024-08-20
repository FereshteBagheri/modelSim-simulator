#include "NandGate.h"

NandGate::NandGate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Gate(id, inputs, output) {}

optional<bool> NandGate::evaluate() {
    bool hasZ = false;
    bool result = true;

    for (Wire* input : inputWires) {
        auto inputVal = input->evaluate();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (!inputVal.value()) {
            result = false;
            break;
        }
    }

    if (result && hasZ) {
        return nullopt;
    } else {
        return !result;
    }
}






