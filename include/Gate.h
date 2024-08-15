#ifndef GATE_H
#define GATE_H

#include "component.h"
#include <string>

using namespace std;

class Gate : public Component {
private:
    string gateType;

public:
    Gate(const string& type, int id, const vector<bool>& inputs, bool output);
    bool evaluate() override;
};

#endif // GATE_H
