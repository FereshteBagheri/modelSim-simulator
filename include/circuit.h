#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <unordered_map>
#include <string>
#include "Component.h"
#include "Wire.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NorGate.h"
#include "NandGate.h"
#include "NotGate.h"

class Circuit {
private:
    
    unordered_map<string, Wire*> wires;
    unordered_map<string, Component*> components;

public:
    
    Wire* getWireById(const string& id) const;
    Component* getComponentById(const string& id) const;

    
    void addWire(const string& id, Wire* wire);
    void addComponent(const string& id, Component* component);

    
    const unordered_map<string, Wire*>& getWires() const;
    const unordered_map<string, Component*>& getComponents() const;
};

#endif 
