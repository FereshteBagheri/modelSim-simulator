#ifndef MODULE_H
#define MODULE_H

#include "Component.h"
#include "Scope.h"
#include "ModuleDefinition.h"
#include "CommandHandler.h"

#include <string>
#include <vector>

class Module : public Component {
public:
    Module(const string& id, const ModuleDefinition& def, const vector<Wire*>& inputWires, Wire* outputWire);

    optional<bool> evaluate() override;
    Wire* getOutputWire() const;

private:
    Wire* output;
    Scope scope; 
};

#endif 
