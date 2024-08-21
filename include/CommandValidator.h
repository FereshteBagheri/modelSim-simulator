#ifndef COMMANDVALIDATOR_H
#define COMMANDVALIDATOR_H

#include <string>
#include <sstream>
#include "Scope.h"
#include "ErrorMessages.h"

class CommandValidator {
public:
    bool validateNewModule(Scope& scope, const string& moduleName, ModuleDefinition* moduleDef);
    bool validateAddComponent(Scope& scope, const string& componentType, const string& componentId, int size);
    bool validatePrint(Scope& scope, const string& id);
    bool validateConnect(Scope& scope, const string& inputWireId, const string& outputWireId);
    bool validatePut(Scope& scope, const string& wireId, int value);
};  

#endif 
