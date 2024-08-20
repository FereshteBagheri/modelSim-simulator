#include "Component.h"

Component::Component(const string& id)
    : id(id) {
        
    }

const string& Component::getId() const {
    return id;
}
