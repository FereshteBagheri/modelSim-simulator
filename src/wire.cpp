#include "Wire.h"

Wire::Wire(const string& id)
    : Component(id), inputWire(nullptr), value(nullopt) {}

void Wire::setInputWire(Wire* input) {
    inputWire = input;
}

void Wire::setValue(optional<bool> newValue) {
    value = newValue;
}

optional<bool> Wire::evaluate() {
    if (inputWire) {
        return inputWire->evaluate();  
    }
    return value;  
}
