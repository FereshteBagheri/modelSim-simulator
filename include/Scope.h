#ifndef SCOPE_H
#define SCOPE_H

#include "Wire.h"
#include "Component.h"
#include "ModuleDefinition.h"

#include <map>
#include <string>
#include <set>


class Scope {
public:
    
    Scope();

    void addWire(const string& id, Wire* wire);

    Wire* getWire(const string& id) const;
    map<string, Wire*> getWires() const;

    void addComponent(const string& id, Component* component);

    Component* getComponent(const string& id) const;

    static void addModuleName(const string& name, const ModuleDefinition* definition);
    static const ModuleDefinition* getModuleDefinition(const string& name);
  
    bool isBasicGate(const string& type) const;


private:
    map<string, Wire*> wires;             
    map<string, Component*> components;   

    static map<string, const ModuleDefinition*> moduleDefinitions; 
    const vector<string> basicGateTypes = {"and", "or", "nand", "nor", "xor", "not"};
};

#endif 
