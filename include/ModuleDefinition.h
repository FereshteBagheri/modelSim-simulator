#ifndef MODULEDEFINITION_H
#define MODULEDEFINITION_H

#include <string>
#include <vector>
#include <istream>
#include "Scope.h"

using namespace std;

class ModuleDefinition {
public:
    ModuleDefinition(const string& name, int numInputs, istream& commandStream);

    string getName() const;
    int getNumInputs() const;
    vector<string> getCommands() const;

    bool validate() const;  

private:
    string name;
    int numInputs;
    vector<string> commands;
};

#endif 
