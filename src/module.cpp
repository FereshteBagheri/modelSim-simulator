#include "Module.h"

#include <iostream>

Module::Module(const string& id, const ModuleDefinition& def, const vector<Wire*>& inputWires, Wire* outputWire, Scope& parentScope)
    : Component(id), scope(), output(outputWire) {

    if (inputWires.size() != def.getNumInputs()) {
        cerr << "incompatible inputs" << endl;
        return;
    }

    for (int i = 0; i < def.getNumInputs(); i++) {
        string inputName = "in" + to_string(i);
        Wire* inputWire = inputWires[i];
        scope.addWire(inputName, inputWire);
    }
    scope.addWire("out", output);

    CommandHandler handler(scope);
    for (const auto& command : def.getCommands()) {
        handler.processCommand(command);  
    }
}

optional<bool> Module::evaluate() {
    return output->evaluate();
}

Wire* Module::getOutputWire() const {
    return output;
}
