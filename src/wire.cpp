#include "Wire.h"
#include <iostream>


Wire::Wire(const string& id)
    : Component(id), inputComponent(nullptr) {}

Wire::Wire(const string& id, Component* input)
    : Component(id), inputComponent(input) {}

void Wire::connectInput(Component* input) {
    inputComponent = input;
}

void Wire::setValue(optional<bool> value) {
    if(inputComponent){
        cout << "can not put value on output."<<endl;
    }else{
    output = value;
    notifyConnectedComponents();
    }
    
}

void Wire::evaluate() {
    if (inputComponent) {
        output = inputComponent->getOutput();
        notifyConnectedComponents();
    }
}
