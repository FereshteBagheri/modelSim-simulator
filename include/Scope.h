#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include <set>
#include "Wire.h"
#include "Component.h"
#include "ModuleDefinition.h"

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
    static bool validateModuleDefinition(const string& name, const ModuleDefinition* definition);


private:
    map<string, Wire*> wires;             
    map<string, Component*> components;   

    static map<string, const ModuleDefinition*> moduleDefinitions;     
};

#endif 
