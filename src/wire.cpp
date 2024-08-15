#include "wire.h"

using namespace std;

Wire::Wire(string id) : wireId(id), inputWirePtr(nullptr), value(nullopt) {}

void Wire::connectInput(Wire* input) {
    inputWirePtr = input;
}

void Wire::setValue(bool newValue) {
    value = newValue;
}

optional<bool> Wire::calculateOutput() {
    if (inputWirePtr) {
        return inputWirePtr->calculateOutput();
    }
    return value;
}

optional<bool> Wire::getOutput(){
    return calculateOutput();
}
