#include "NorGate.h"

NorGate::NorGate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Gate(id, inputs, output) {}

optional<bool> NorGate::evaluate() {
    bool result = true;
    bool hasZ = false;

    for (Wire* input : inputWires) {
        optional<bool> inputVal = input->evaluate();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (inputVal.value()) {
            result = false;
            break;
        }
    }

    if (result && hasZ) {
        return nullopt; // If there's any Z and result is still true, output is Z
    } else {
        return result;  // Return the result of NOR logic
    }
}
