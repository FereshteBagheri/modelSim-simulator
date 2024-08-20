#include "Gate.h"

Gate::Gate(const string& id, const vector<Wire*>& inputs, Wire* output)
    : Component(id), inputWires(inputs), outputWire(output) {
    if (outputWire) {
        outputWire->setInputComponent(this);
    }
}

Wire* Gate::getOutputWire() const {
    return outputWire;
}
