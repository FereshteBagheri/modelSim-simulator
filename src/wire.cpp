#include "wire.h"
#include <iostream>

using namespace std;

Wire::Wire(const string& id) : wireId(id), inputWirePtr(nullptr), value(nullopt) {
    if (!addWire(this)) {
        cout <<"duplicate ID";
    }
}

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

optional<bool> Wire::getOutput() {
    return calculateOutput();
}

Wire* Wire::getWireById(const string& id) {
    auto it = wireMap.find(id);
    return (it != wireMap.end()) ? it->second : nullptr;
}

bool Wire::addWire(Wire* wire) {
    auto result = wireMap.emplace(wire->wireId, wire);
    return result.second;
}
