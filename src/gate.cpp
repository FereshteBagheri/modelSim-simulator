#include "Gate.h"

Gate::Gate(const string& id, const vector<Component*>& inputs)
    : Component(id), inputComponents(inputs) {
    for (Component* input : inputs) {
        input->addConnectedComponent(this);
    }
}

void Gate::connectInput(Component* input) {
    inputComponents.push_back(input);
    input->addConnectedComponent(this);
}

void Gate::connectInputs(const vector<Component*>& inputs) {
    for (Component* input : inputs) {
        connectInput(input);
    }
}
