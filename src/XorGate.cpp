#include "XorGate.h"

XorGate::XorGate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Gate(id, inputs, output) {}

optional<bool> XorGate::evaluate() {
    bool result = false;
    bool hasZ = false;

    for (Wire* input : inputWires) {
        auto inputVal = input->evaluate();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else {
            result ^= inputVal.value();
        }
    }

    if (hasZ) {
        return nullopt;
    } else {
        return result;
    }
}
