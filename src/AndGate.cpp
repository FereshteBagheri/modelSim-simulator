#include "AndGate.h"

AndGate::AndGate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Gate(id, inputs, output) {}

optional<bool> AndGate::evaluate() {
    bool hasZ = false;   
    bool result = true;  

    for (Wire* input : inputWires) {
        optional<bool> inputVal = input->evaluate();

        if (!inputVal.has_value()) {
            hasZ = true;
        } else if (!inputVal.value()) {
            result = false;
            break;
        }
    }

    optional<bool> finalResult;
    if (result && hasZ) {
        return nullopt;
    } else {
        return result;
    }  
}
