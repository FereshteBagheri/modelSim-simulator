#include "AndGate.h"

AndGate::AndGate(const string& id, const vector<Component*>& inputs)
    : Gate(id, inputs) {}

void AndGate::evaluate() {
    bool hasZ = false;
    bool result = true;

    for (Component* input : inputComponents) {
        auto inputVal = input->getOutput();

         if (!inputVal.has_value()) {
            hasZ = true;
        } else if(!inputVal.value()){
            result = false;
            break;
        }
    }

    if (result && hasZ) {
        this->output = nullopt;
    } else {
        this->output = result;
    }

    this->notifyConnectedComponents();
}
