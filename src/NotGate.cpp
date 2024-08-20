#include "NotGate.h"

NotGate::NotGate(const string& id, Wire* input, Wire* output)
    : Gate(id, {input}, output) {}

optional<bool> NotGate::evaluate() {
    optional<bool> inputVal = inputWires[0]->evaluate();  

    if (inputVal.has_value()) {
        return !inputVal.value();  
    }

    return nullopt;  
}
