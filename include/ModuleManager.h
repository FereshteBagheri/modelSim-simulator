#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Module.h"
#include "Circuit.h"

class ModuleManager {
private:
    std::map<std::string, Module*> blueprints;

public:
    // Adds a blueprint to the manager
    void addBlueprint(const std::string& moduleId, Module* module) {
        blueprints[moduleId] = module;
    }

    // Gets a blueprint by module ID
    Module* getBlueprint(const std::string& moduleId) const {
        auto it = blueprints.find(moduleId);
        if (it != blueprints.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Instantiates a module based on its blueprint and adds it to the circuit
    Module* instantiateModule(const std::string& moduleId, const std::string& instanceId,
                              const std::vector<Wire*>& inputWires, Wire* outputWire, Circuit& circuit) const {
        cout << "first" << endl;
        Module* blueprint = getBlueprint(moduleId);
        cout << "get blueprint" << endl;
        if (!blueprint) {
            std::cerr << "Module blueprint not found: " << moduleId << std::endl;
            return nullptr;
        }

        Module* instantiatedModule = new Module(instanceId, blueprint, inputWires, outputWire);
        cout << "after instancing" << endl;

        // Add the instantiated module to the circuit's component map
        circuit.addComponent(instanceId, instantiatedModule);
        cout << "add to circuit" << endl;

        return instantiatedModule;
    }

    // Handles the definition of a new module blueprint
    void handleModuleDefinition(const std::string& moduleId, int numInputs, Circuit& circuit, std::istream& commandStream);
};

#endif // MODULE_MANAGER_H
