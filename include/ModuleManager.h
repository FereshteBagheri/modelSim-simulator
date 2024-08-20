// #ifndef MODULE_MANAGER_H
// #define MODULE_MANAGER_H

// #include <string>
// #include <map>
// #include <vector>
// #include <iostream>
// #include "Module.h"
// #include "Circuit.h"

// class ModuleManager {
// private:
//     map<string, Module*> blueprints;

// public:
    
//     void addBlueprint(const string& moduleId, Module* module) {
//         blueprints[moduleId] = module;
//     }

    
//     Module* getBlueprint(const string& moduleId) const {
//         auto it = blueprints.find(moduleId);
//         if (it != blueprints.end()) {
//             return it->second;
//         }
//         return nullptr;
//     }

    
//     Module* instantiateModule(const string& moduleId, const string& instanceId,
//                               const vector<Wire*>& inputWires, Wire* outputWire, Circuit& circuit) const {
//         cout << "first" << endl;
//         Module* blueprint = getBlueprint(moduleId);
//         cout << "get blueprint" << endl;
//         if (!blueprint) {
//             cerr << "Module blueprint not found: " << moduleId << endl;
//             return nullptr;
//         }

//         Module* instantiatedModule = new Module(instanceId, blueprint, inputWires, outputWire);
//         cout << "after instancing" << endl;

        
//         circuit.addComponent(instanceId, instantiatedModule);
//         cout << "add to circuit" << endl;

//         return instantiatedModule;
//     }

    
//     void handleModuleDefinition(const string& moduleId, int numInputs, Circuit& circuit, istream& commandStream);
// };

// #endif 
