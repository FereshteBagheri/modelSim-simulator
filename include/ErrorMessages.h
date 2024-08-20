#ifndef ERRORMESSAGES_H
#define ERRORMESSAGES_H

#include <string>

using namespace std;

namespace ErrorMessages {
    const string MODULE_EXISTS = " this module already exists";
    const string DUPLICATE_ID = "duplicate ID";
    const string GATE_MODULE_NOT_FOUND = "gate/module not found";
    const string INPUTS_INCOMPATIBLE = "Inputs incompatible";
    const string INVALID_CONNECTION = "invalid connection";
    const string ID_NOT_FOUND = "ID not found";
    const string VALUE_NOT_VALID = "Value not valid";
    const string INVALID_ID = "invalid ID";
    const string SELF_CONNECTION = "Self connection is not allowed";
    const string INVALID_COMMAND = "Invalid command: ";
    const string MODULE_EMPTY = "Module definition is empty or missing 'end_module'";
} 

#endif 
