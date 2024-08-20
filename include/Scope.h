#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include <set>
#include "Wire.h"
#include "Component.h"

class Scope {
public:
    
    Scope();

    void addWire(const string& id, Wire* wire);

    Wire* getWire(const string& id) const;

    void addComponent(const string& id, Component* component);

    Component* getComponent(const string& id) const;

 // Static methods to manage global module names and definitions
    static void addModuleName(const string& name, ModuleDefinition* definition);
    static ModuleDefinition* getModuleDefinition(const string& name);


private:
    map<string, Wire*> wires;             
    map<string, Component*> components;   

    static map<string, ModuleDefinition*> moduleDefinitions;     
};

#endif 
