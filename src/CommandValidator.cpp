#include "CommandValidator.h"
#include "CommandHandler.h"
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

    bool isBasicGate = scope.isBasicGate(componentType);

    if ( isBasicGate && ((componentType == "not" && size != 2) || (componentType != "not" && size < 3))) {
        cerr << ErrorMessages::INPUTS_INCOMPATIBLE << endl;
        return false;
    }


    bool isModule = Scope::getModuleDefinition(componentType) != nullptr;

    if (!isBasicGate && !isModule) {
        cerr << ErrorMessages::GATE_MODULE_NOT_FOUND << endl;
        return false;
    }

    return true;
}

bool CommandValidator::validatePrint(Scope& scope, const string& id) {

    if (!scope.getComponent(id)) {
        cerr << ErrorMessages::ID_NOT_FOUND << endl;
        return false;
    }
    return true;
}

bool CommandValidator::validateConnect(Scope& scope, const string& inputWireId, const string& outputWireId) {
    Wire* inputWire = scope.getWire(inputWireId);
    Wire* outputWire = scope.getWire(outputWireId);

    if (!inputWire || !outputWire) {
        cerr << ErrorMessages::ID_NOT_FOUND << endl;
        return false;
    }

    if (inputWireId == outputWireId) {
        cerr << ErrorMessages::INVALID_CONNECTION << endl;
        return false;
    }
    return true;
}

bool CommandValidator::validatePut(Scope& scope, const string& wireId, int value) {

    if (!scope.getWire(wireId)) {
        cerr << ErrorMessages::ID_NOT_FOUND << endl;
        return false;
    }

    if (value != 0 && value != 1) {
        cerr << ErrorMessages::VALUE_NOT_VALID << endl;
        return false;
    }
    return true;
}
