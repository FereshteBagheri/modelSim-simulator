#include "Circuit.h"


Wire* Circuit::getWireById(const string& id) const {
    auto it = wires.find(id);
    if (it != wires.end()) {
        return it->second;
    }
    return nullptr;
}


Component* Circuit::getComponentById(const string& id) const {
    auto it = components.find(id);
    if (it != components.end()) {
        return it->second;
    }
    return nullptr;
}


void Circuit::addWire(const string& id, Wire* wire) {
    wires[id] = wire;
}


void Circuit::addComponent(const string& id, Component* component) {
    components[id] = component;
}


const unordered_map<string, Wire*>& Circuit::getWires() const {
    return wires;
}


const unordered_map<string, Component*>& Circuit::getComponents() const {
    return components;
}
