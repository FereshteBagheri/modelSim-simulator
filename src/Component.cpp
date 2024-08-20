#include "Component.h"

Component::Component(const string& id, optional<bool> output)
    : id(id), output(output) {}

optional<bool> Component::getOutput() const {
    return output;
}

const string& Component::getId() const {
    return id;
}
