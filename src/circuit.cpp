#include "Circuit.h"

Component* Circuit::getComponentById(const string& id) const {
    auto it = components.find(id);
    if (it != components.end()) {
        return it->second;
    }
    return nullptr;
}

void Circuit::addComponent(const string& id, Component* component) {
    components[id] = component;
}

const unordered_map<string, Component*>& Circuit::getComponents() const {
    return components;
}
