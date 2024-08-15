#include "Wire.h"


Wire::Wire(const string& id)
    : Component(id), inputComponent(nullptr) {}

Wire::Wire(const string& id, Component* input)
    : Component(id), inputComponent(input) {}

void Wire::connectInput(Component* input) {
    inputComponent = input;
    input->addConnectedComponent(this);
}

void Wire::setValue(optional<bool> value) {
    this->output = value;
    notifyConnectedComponents();
}

void Wire::evaluate() {
    if (inputComponent) {
        output = inputComponent->getOutput();
        notifyConnectedComponents();
    }
}
