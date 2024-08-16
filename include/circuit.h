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

class Circuit {
private:
    unordered_map<string, Component*> components;

public:
    Component* getComponentById(const string& id) const;
    void addComponent(const string& id, Component* component);
    const unordered_map<string, Component*>& getComponents() const;
};

#endif // CIRCUIT_H
