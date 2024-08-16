#include "Component.h"
#include <iostream>

Component::Component(const string& id) : id(id) {}

void Component::addConnectedComponent(Component* comp) {
    connectedComponents.push_back(comp);
}

void Component::notifyConnectedComponents() {
    
    for (Component* comp : connectedComponents) {
        comp->evaluate();
    }
}

optional<bool> Component::getOutput() const {
    return output;
}

const string& Component::getId() const {
    return id;
}
