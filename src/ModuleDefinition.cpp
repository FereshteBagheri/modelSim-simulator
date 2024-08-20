#include "ModuleDefinition.h"
#include <sstream>
#include <iostream>

ModuleDefinition::ModuleDefinition(const string& name, int numInputs, istream& commandStream)
    : name(name), numInputs(numInputs) {
    string line;
    while (getline(commandStream, line)) {
        if (line.empty()) continue;
        if (line == "end_module") break;
        commands.push_back(line);
    }
}

string ModuleDefinition::getName() const {
    return name;
}

int ModuleDefinition::getNumInputs() const {
    return numInputs;
}

vector<string> ModuleDefinition::getCommands() const {
    return commands;
}

bool ModuleDefinition::validate() const {

    if (Scope::getModuleDefinition(name) != nullptr) {
        cerr << "This module already exists: " << name << endl;
        return false;
    }
    
    return true;
}

