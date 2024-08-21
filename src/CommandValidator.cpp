#include "CommandValidator.h"
#include <iostream>

bool CommandValidator::validateNewModule(Scope& scope, const string& moduleName) {
    
    if (scope.getModuleDefinition(moduleName)) {
        cerr << ErrorMessages::MODULE_EXISTS << endl;
        return false;
    }

    return true;
}

bool CommandValidator::validateAddComponent(Scope& scope, const string& componentType, const string& componentId, int size) {

    if (scope.getComponent(componentId) != nullptr) {
        cerr << ErrorMessages::DUPLICATE_ID << endl;
        return false;
    }

    if ((componentType == "not" && size != 2) || (componentType != "not" && size < 3)) {
        cerr << ErrorMessages::INPUTS_INCOMPATIBLE << endl;
        return false;
    }

    bool isBasicGate = scope.isBasicGate(componentType);
    bool isModule = Scope::getModuleDefinition(componentType) != nullptr;

    if (!isBasicGate && !isModule) {
        cerr << ErrorMessages::GATE_MODULE_NOT_FOUND << endl;
        return false;
    }

    return true;
}

bool CommandValidator::validatePrint(Scope& scope, const string& id) {

    if (!scope.getComponent(id)) {
        cerr << ErrorMessages::INVALID_ID << endl;
        return false;
    }
    return true;
}
