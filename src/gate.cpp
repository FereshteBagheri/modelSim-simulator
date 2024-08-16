#include "Gate.h"

Gate::Gate(const string& id, const vector<Wire*>& inputs)
    : Component(id), inputWires(inputs), outputWire(nullptr) {
    for (Wire* input : inputs) {
        input->addConnectedComponent(this);
    }
}

void Gate::connectInput(Wire* input) {
    inputWires.push_back(input);
    input->addConnectedComponent(this);
}

void Gate::connectInputs(const vector<Wire*>& inputs) {
    for (Wire* input : inputs) {
        connectInput(input);
    }
}

void Gate::setOutput(Wire* output) {
    outputWire = output;
    outputWire->evaluate();
}

Wire* Gate::getOutput() const {
    return outputWire;
}
