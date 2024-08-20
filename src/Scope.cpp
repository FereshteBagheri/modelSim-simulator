#include "Scope.h"
#include <iostream>

Scope::Scope() {}

Scope::~Scope() {
    for (auto& pair : wires) {
        delete pair.second;
    }
    for (auto& pair : components) {
        delete pair.second;
    }
}

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


void Scope::addComponent(const string& id, Component* component) {
    if (components.find(id) != components.end()) {
        cerr << "duplicate ID" <<endl;
        return;
    }
    components[id] = component;
}


Component* Scope::getComponent(const string& id) const {
    auto it = components.find(id);
    return (it != components.end()) ? it->second : nullptr;
}

void Scope::addModuleName(const string& name, ModuleDefinition* definition) {
    if (moduleDefinitions.find(name) != moduleDefinitions.end()) {
        cerr << "this module already exists"<< endl;
        return;
    }
    moduleDefinitions[name] = definition;
}

// Static method to get a module definition by name
ModuleDefinition* Scope::getModuleDefinition(const string& name) {
    auto it = moduleDefinitions.find(name);
    if (it != moduleDefinitions.end()) {
        return it->second;
    }
    cerr << "gate/module not found" << endl;
    return nullptr;
}
