#include "gate.h"

using namespace std;

Gate::Gate(const string& type, int id, const vector<bool>& inputs, bool output)
    : Component(id, inputs, output), gateType(type) {}

bool Gate::evaluate() {
    if (gateType == "and") {
        output = true;
        for (bool input : inputs) {
            output &= input;
        }
    } else if (gateType == "or") {
        output = false;
        for (bool input : inputs) {
            output |= input;
        }
    } else if (gateType == "not") {
        output = !inputs[0];
    } else if (gateType == "xor") {
        output = inputs[0] ^ inputs[1];
    } else if (gateType == "nand") {
        output = true;
        for (bool input : inputs) {
            output &= input;
        }
        output = !output;
    } else if (gateType == "nor") {
        output = false;
        for (bool input : inputs) {
            output |= input;
        }
        output = !output;
    }
    return output;
}
