#include "Circuit.h"

Component* Circuit::getComponentById(const std::string& id) const {
    auto it = components.find(id);
    if (it != components.end()) {
        return it->second;
    }
    return nullptr;
}

void Circuit::addComponent(const std::string& id, Component* component) {
    components[id] = component;
}

const std::unordered_map<std::string, Component*>& Circuit::getComponents() const {
    return components;
}
