#include "component.h"

using namespace std;

Component::Component(int id, const vector<bool>& inputs, bool output)
    : componentId(id), inputs(inputs), output(output) {}

bool Component::getOutput() const {
    return output;
}
