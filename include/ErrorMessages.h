#ifndef ERRORMESSAGES_H
#define ERRORMESSAGES_H

#include <string>

using namespace std;

namespace ErrorMessages {
    const string MODULE_EXISTS = "Module already exists";
    const string ID_DUPLICATE = "ID duplicate";
    const string GATE_MODULE_NOT_FOUND = "Gate/module not found";
    const string INPUTS_INCOMPATIBLE = "Inputs incompatible";
    const string CONNECTION_INVALID = "Connection invalid";
    const string ID_NOT_FOUND = "ID not found";
    const string VALUE_NOT_VALID = "Value not valid";
    const string INVALID_ID = "Invalid ID";
    const string SELF_CONNECTION = "Self connection is not allowed";

} 

#endif 
