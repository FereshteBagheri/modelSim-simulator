#include "Module.h"
#include <iostream>


Module::Module(const string& id, int numInputs)
    : Component(id), output(nullptr), numInputs(numInputs) {
    for (int i = 0; i < numInputs; i++) {
        string inputId = "in" + to_string(i);
        inputs.push_back(new Wire(inputId));
        wires[inputId] = inputs.back();
    }
    output = new Wire("out");
    wires["out"] = output;


}


Module::Module(const string& id, const Module* blueprint, const vector<Wire*>& inputWires, Wire* outputWire)
    : Component(id) {
        cout << "in the constructor" << endl;
    components = blueprint->components;
    
    cout << "found components" << endl;
    wires = blueprint->wires;
    cout << "found wires" << endl;

    setupConnections(inputWires, outputWire);
    cout << "after setup" << endl;
}



void Module::addComponent(const string& id, Component* component) {
   
    if (components.find(id) != components.end()) {
        cerr << "Component ID duplicate: " << id << endl;
        return;
    }

    
    components[id] = component;
         
    cout << "Current components in the module before adding new component:" << endl;
    for (const auto& entry : components) {
        cout << "Component ID: " << entry.first << endl;
    }
}



void Module::addWire(const string& id, Wire* wire) {
    if (wires.find(id) != wires.end()) {
        cerr << "Wire ID duplicate" << endl;
        return;
    }
    wires[id] = wire;
}


void Module::connectInternal(const string& fromId, const string& toId) {
    if (wires.find(fromId) == wires.end() || wires.find(toId) == wires.end()) {
        cerr << "Wire not found in module" << endl;
        return;
    }
    wires[toId]->setInputComponent(wires[fromId]);
}


void Module::setupConnections(const vector<Wire*>& inputWires, Wire* outputWire) {
    
    for (size_t i = 0; i < inputs.size(); i++) {

        
        
        inputs[i]->setInputComponent(inputWires[i]);
    }
    outputWire->setInputComponent(output);
}


optional<bool> Module::evaluate() {
    return output->evaluate();
}


Wire* Module::getInput(int index) const {
    if (index < 0 || index >= inputs.size()) {
        return nullptr;
    }
    return inputs[index];
}


Wire* Module::getOutput() const {
    return output;
}

int Module::getNumInputs() const {
    return numInputs;
}


Wire* Module::getInternalWire(const string& id) const {
    auto it = wires.find(id);
    if (it != wires.end()) {
        return it->second;
    }
    return nullptr;
}
