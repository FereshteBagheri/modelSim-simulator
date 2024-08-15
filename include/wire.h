#ifndef WIRE_H
#define WIRE_H

#include "Component.h"
#include <optional>

using namespace std;

class Wire : public Component {
private:
    Component* inputComponent;

public:
    Wire(const string& id);

    Wire(const string& id, Component* input);

    void connectInput(Component* input);

    void setValue(optional<bool> value);

    void evaluate() override;
};

#endif 
