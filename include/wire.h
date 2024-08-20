#ifndef WIRE_H
#define WIRE_H

#include "Component.h"

#include <optional>

using namespace std;

class Wire : public Component {
private:
    Component* inputComponent;

    optional<bool> value;

public:
    Wire(const string& id);

    void setInputComponent(Component* input);

    void setValue(optional<bool> value);

    optional<bool> evaluate() override;
};

#endif 
