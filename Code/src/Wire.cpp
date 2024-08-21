#include "Wire.h"

Wire::Wire(const string& id)
    : Component(id), inputComponent(nullptr), value(nullopt) {}

void Wire::setInputComponent(Component* input) {
    inputComponent = input;
}

void Wire::setValue(optional<bool> newValue) {
    value = newValue;
}

optional<bool> Wire::evaluate() {
    
    if (inputComponent) {
        return inputComponent->evaluate();  
    }
    return value;  
}
