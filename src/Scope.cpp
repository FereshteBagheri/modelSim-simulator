#include "Scope.h"
#include "ErrorMessages.h"

#include <iostream>
#include <algorithm>

map<string, const ModuleDefinition*> Scope::moduleDefinitions; 

Scope::Scope() {}

void Scope::addWire(const string& id, Wire* wire) {
    if (wires.find(id) != wires.end()) {
        return;
    }
    wires[id] = wire;
}

Wire* Scope::getWire(const string& id) const {
    auto it = wires.find(id);
    return (it != wires.end()) ? it->second : nullptr;
}

map<string, Wire*> Scope::getWires() const {
    return wires;
}

void Scope::addComponent(const string& id, Component* component) {
    components[id] = component;
}

Component* Scope::getComponent(const string& id) const {
    auto it = components.find(id);
    return (it != components.end()) ? it->second : nullptr;
}

void Scope::addModuleName(const string& name, const ModuleDefinition* definition) {
    if (moduleDefinitions.find(name) != moduleDefinitions.end()) {
        return;
    }
    moduleDefinitions[name] = definition;
}


const ModuleDefinition* Scope::getModuleDefinition(const string& name) {
    auto it = moduleDefinitions.find(name);
    if (it != moduleDefinitions.end()) {
        return it->second;
    }
    return nullptr;
}

bool Scope::isBasicGate(const string& type) const {
    return find(basicGateTypes.begin(), basicGateTypes.end(), type) != basicGateTypes.end();
}
