#ifndef COMMANDVALIDATOR_H
#define COMMANDVALIDATOR_H

#include <string>
#include <sstream>
#include "Scope.h"
#include "ErrorMessages.h"

class CommandValidator {
public:
    bool validateNewModule(Scope& scope, const string& moduleName);
};

#endif 
