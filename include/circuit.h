#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <unordered_map>
#include <string>
#include "Component.h"
#include "Wire.h"
#include "Gate.h"
#include "AndGate.h"
#include "OrGate.h"

class Circuit {
private:
    std::unordered_map<std::string, Component*> components;

public:
    Component* getComponentById(const std::string& id) const;
    void addComponent(const std::string& id, Component* component);
    const std::unordered_map<std::string, Component*>& getComponents() const;
};

#endif // CIRCUIT_H
