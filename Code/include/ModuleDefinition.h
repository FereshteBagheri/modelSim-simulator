#ifndef MODULEDEFINITION_H
#define MODULEDEFINITION_H

#include <string>
#include <vector>
#include <istream>

using namespace std;

class ModuleDefinition {
public:
    ModuleDefinition(const string& name, int numInputs, istream& commandStream);

    string getName() const;
    int getNumInputs() const;
    vector<string> getCommands() const;

private:
    string name;
    int numInputs;
    vector<string> commands;
};

#endif 
