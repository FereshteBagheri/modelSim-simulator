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
    
    std::unordered_map<std::string, Wire*> wires;
    std::unordered_map<std::string, Component*> components;

public:
    
    Wire* getWireById(const std::string& id) const;
    Component* getComponentById(const std::string& id) const;

    
    void addWire(const std::string& id, Wire* wire);
    void addComponent(const std::string& id, Component* component);

    
    const std::unordered_map<std::string, Wire*>& getWires() const;
    const std::unordered_map<std::string, Component*>& getComponents() const;
};

#endif 
