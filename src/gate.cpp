#include "Gate.h"

Gate::Gate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Component(id, nullopt), inputWires(inputs), outputWire(output) {}

void Gate::connectInput(Wire* input) {
    inputWires.push_back(input);
}

void Gate::connectInputs(const vector<Wire*>& inputs) {
    inputWires.insert(inputWires.end(), inputs.begin(), inputs.end());
}

Wire* Gate::getOutputWire() const {
    return outputWire;
}
