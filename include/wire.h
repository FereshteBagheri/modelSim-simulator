#ifndef WIRE_H
#define WIRE_H

#include "Component.h"
#include <optional>

using namespace std;

class Wire : public Component {
private:
    Wire* inputWire;

    optional<bool> value;

public:
    Wire(const string& id);

    void setInputWire(Wire* input);

    void setValue(optional<bool> value);

    optional<bool> evaluate() override;
};

#endif 
