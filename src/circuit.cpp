#include "Circuit.h"


Wire* Circuit::getWireById(const std::string& id) const {
    auto it = wires.find(id);
    if (it != wires.end()) {
        return it->second;
    }
    return nullptr;
}


Component* Circuit::getComponentById(const std::string& id) const {
    auto it = components.find(id);
    if (it != components.end()) {
        return it->second;
    }
    return nullptr;
}


void Circuit::addWire(const std::string& id, Wire* wire) {
    wires[id] = wire;
}


void Circuit::addComponent(const std::string& id, Component* component) {
    components[id] = component;
}


const std::unordered_map<std::string, Wire*>& Circuit::getWires() const {
    return wires;
}


const std::unordered_map<std::string, Component*>& Circuit::getComponents() const {
    return components;
}
