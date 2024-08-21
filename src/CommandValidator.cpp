#include "CommandValidator.h"
#include <iostream>

bool CommandValidator::validateNewModule(Scope& scope, const string& moduleName) {
    
    if (scope.getModuleDefinition(moduleName)) {
        cerr << ErrorMessages::MODULE_EXISTS << endl;
        return false;
    }
    
    return true;
}
