#include "Module.h"
#include <iostream>

// Blueprint Constructor
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

// Circuit Instantiation Constructor
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


// Add a component (gate/module) to the module
void Module::addComponent(const string& id, Component* component) {
   
    if (components.find(id) != components.end()) {
        cerr << "Component ID duplicate: " << id << endl;
        return;
    }

    // Add the new component to the module
    components[id] = component;
         // Print the current components of the module
    cout << "Current components in the module before adding new component:" << endl;
    for (const auto& entry : components) {
        cout << "Component ID: " << entry.first << endl;
    }
}


// Add a wire to the module
void Module::addWire(const string& id, Wire* wire) {
    if (wires.find(id) != wires.end()) {
        cerr << "Wire ID duplicate" << endl;
        return;
    }
    wires[id] = wire;
}

// Connect internal wires (during blueprint creation)
void Module::connectInternal(const string& fromId, const string& toId) {
    if (wires.find(fromId) == wires.end() || wires.find(toId) == wires.end()) {
        cerr << "Wire not found in module" << endl;
        return;
    }
    wires[toId]->setInputComponent(wires[fromId]);
}

// Internal function to set up connections in instantiated modules
void Module::setupConnections(const vector<Wire*>& inputWires, Wire* outputWire) {
    // Connect the provided input wires to the module's internal inputs
    for (size_t i = 0; i < inputs.size(); i++) {

        
        
        inputs[i]->setInputComponent(inputWires[i]);
    }
    outputWire->setInputComponent(output);
}

// Evaluate the module's output by recursively evaluating its components
optional<bool> Module::evaluate() {
    return output->evaluate();
}

// Get an input wire by index
Wire* Module::getInput(int index) const {
    if (index < 0 || index >= inputs.size()) {
        return nullptr;
    }
    return inputs[index];
}

// Get the output wire
Wire* Module::getOutput() const {
    return output;
}

int Module::getNumInputs() const {
    return numInputs;
}

// Get internal wire by ID
Wire* Module::getInternalWire(const string& id) const {
    auto it = wires.find(id);
    if (it != wires.end()) {
        return it->second;
    }
    return nullptr;
}
