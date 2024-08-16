#include "OrGate.h"

OrGate::OrGate(const string& id, const vector<Component*>& inputs)
    : Gate(id, inputs) {}

void OrGate::evaluate() {
    bool result = false;
    for (Component* input : inputComponents) {
        auto inputVal = input->getOutput();
        if (inputVal.has_value() && inputVal.value()) {
            result = true;
            break;
        }
    }
    this->output = result;
    this->notifyConnectedComponents();
}
