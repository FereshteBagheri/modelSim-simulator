#include "Circuit.h"
#include "ModuleManager.h"
#include "Scope.h"
#include "ModuleDefinition.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Scope globalScope;

void printWires(const Scope& scope) {
    using namespace std;
    
    cout << "Current wire values:" << endl;

    for (const auto& [id, wire] : scope.getWires()) {
        auto wireValue = wire->evaluate();
        if (wireValue.has_value()) {
            cout << "Wire " << id << ": " << wireValue.value() << endl;
        } else {
            cout << "Wire " << id << ": (undefined)" << endl;
        }
    }
}

void handleAddNewModule(istringstream& iss) {

    string moduleName;
    int numInputs;
    iss >> moduleName >> numInputs;

    ModuleDefinition* moduleDef = new ModuleDefinition(moduleName, numInputs, iss);

    if (Scope::validateModuleDefinition(moduleName, moduleDef)) {
        delete moduleDef;
        return;
    }

    Scope::addModuleName(moduleName, moduleDef);
}

void handleAddComponent(istringstream& iss, Scope& scope) {
    string componentType, componentId, outputId;
    vector<string> passedIds;
    
    iss >> componentType >> componentId;
    
    if (scope.getComponent(componentId) != nullptr) {
        cerr << "duplicate ID" << endl;
        return;
    }

    string passedId;
    while (iss >> passedId) {
        passedIds.push_back(passedId);
    }

    if ((componentType == "not" && passedIds.size() != 2) || (componentType != "not" && passedIds.size() < 3)) {
    cerr << "inputs incompatible" << endl;
    return;
    }
    
    outputId = passedIds.back();
    passedIds.pop_back();

    vector<Wire*> inputWires;
    for (const auto& id : passedIds) {
        Wire* inputWire = scope.getWire(id);
        if (!inputWire) {
            inputWire = new Wire(id);
            scope.addWire(id, inputWire);
        }
        inputWires.push_back(inputWire);
    }

    Wire* outputWire = scope.getWire(outputId);
    if (!outputWire) {
        outputWire = new Wire(outputId);
        scope.addWire(outputId, outputWire);
    }

    Component* component = nullptr;

    if (componentType == "and") {
        component = new AndGate(componentId, inputWires, outputWire);
    } else if (componentType == "or") {
        component = new OrGate(componentId, inputWires, outputWire);
    } else if (componentType == "xor") {
        component = new XorGate(componentId, inputWires, outputWire);
    } else if (componentType == "nand") {
        component = new NandGate(componentId, inputWires, outputWire);
    } else if (componentType == "nor") {
        component = new NorGate(componentId, inputWires, outputWire);
    } else if (componentType == "not") {
        component = new NotGate(componentId, inputWires[0], outputWire);
    } else {
        cerr << "Unknown gate type" << endl;
        return;
    }

    scope.addComponent(componentId, component);

    cout << "Added " << componentType << " gate with ID " << componentId << endl;

}


// void handleNewModule(istringstream& iss, Circuit& circuit) {
//     string moduleId;
//     int numInputs;
//     iss >> moduleId >> numInputs;

//     if (moduleManager.getBlueprint(moduleId)) {
//         cerr << "Module name already exists: " << moduleId << endl;
//         return;
//     }

    
//     moduleManager.handleModuleDefinition(moduleId, numInputs, circuit, cin);

//     cout << "Created new module blueprint with ID: " << moduleId << endl;
// }

// void handleInstantiateModule(istringstream& iss, Circuit& circuit) {
//     string moduleId, instanceId;
//     vector<Wire*> inputWires;
//     string wireId;

//     iss >> moduleId >> instanceId;

//     Module* blueprint = moduleManager.getBlueprint(moduleId);
//     if (!blueprint) {
//         cerr << "Module blueprint not found: " << moduleId << endl;
//         return;
//     }

//     while (iss >> wireId) {
//         Wire* wire = circuit.getWireById(wireId);
//         if (!wire) {
//             cerr << "Wire ID not found: " << wireId << endl;
//             return;
//         }
//         inputWires.push_back(wire);
//     }

//     if (inputWires.size() != blueprint->getNumInputs() + 1) {
//         cerr << "Number of wires provided does not match the module inputs" << endl;
//         return;
//     }

//     Wire* outputWire = inputWires.back();
//     inputWires.pop_back();

//     Module* instance = moduleManager.instantiateModule(moduleId, instanceId, inputWires, outputWire, circuit);
//     circuit.addComponent(instanceId, instance);

//     cout << "Instantiated module with ID: " << instanceId << endl;
//     printWires(circuit);
// }


void handlePrint(istringstream& iss, Scope& scope) {
    string id;
    iss >> id;

    Component* component = scope.getComponent(id);

    if (!component) {
        cerr << "Invalid ID" << endl;
        return;
    }

    auto outputValue = component->evaluate();
    if (outputValue.has_value()) {
        cout << (outputValue.value() ? "1" : "0") << endl;
    } else {
        cout << "z" << endl;
    }
}


void handleConnect(istringstream& iss, Scope& scope) {
    string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Wire* inputWire = scope.getWire(inputWireId);
    Wire* outputWire = scope.getWire(outputWireId);

    if (!inputWire || !outputWire) {
        std::cerr << "ID not found" << std::endl;
        return;
    }

    if (inputWireId == outputWireId) {
        std::cerr << "Invalid connection" << std::endl;
        return;
    }

    outputWire->setInputComponent(inputWire);

    std::cout << "Connected " << inputWireId << " to " << outputWireId << std::endl;
    printWires(scope);
}


void handlePut(istringstream& iss, Scope& scope) {
    string wireId;
    int value;
    iss >> wireId >> value;

    Wire* wire = scope.getWire(wireId);
    
    if (!wire) {
        std::cerr << "ID not found" << std::endl;
        return;
    }

    if (value != 0 && value != 1) {
        std::cerr << "Value not valid" << std::endl;
        return;
    }

    wire->setValue(value);
    // printWires(scope);
}

// void handleAddGate(istringstream& iss, Circuit& circuit) {
//     string gateType, gateId, outputId;
//     vector<string> inputIds;

//     iss >> gateType >> gateId;

    
//     if (circuit.getComponentById(gateId)) {
//         cerr << "ID duplicate" << endl;
//         return;
//     }

    
//     string inputId;
//     while (iss >> inputId) {
//         inputIds.push_back(inputId);
//     }

    
//     outputId = inputIds.back();
//     inputIds.pop_back();

    
//     vector<Wire*> inputWires;
//     for (const auto& id : inputIds) {
//         Wire* inputWire = circuit.getWireById(id);
//         if (!inputWire) {
//             inputWire = new Wire(id);
//             circuit.addWire(id, inputWire);
//         }
//         inputWires.push_back(inputWire);
//     }

//     Wire* outputWire = circuit.getWireById(outputId);
//     if (!outputWire) {
//         outputWire = new Wire(outputId);
//         circuit.addWire(outputId, outputWire);
//     }

//     Gate* gate = nullptr;

    
//     if (gateType == "and") {
//         gate = new AndGate(gateId, inputWires, outputWire);
//     } else if (gateType == "or") {
//         gate = new OrGate(gateId, inputWires, outputWire);
//     } else if (gateType == "xor") {
//         gate = new XorGate(gateId, inputWires, outputWire);
//     } else if (gateType == "nand") {
//         gate = new NandGate(gateId, inputWires, outputWire);
//     } else if (gateType == "nor") {
//         gate = new NorGate(gateId, inputWires, outputWire);
//     } else if (gateType == "not") {
//         if (inputIds.size() != 1) {
//             cerr << "inputs incompatible for NOT gate" << endl;
//             return;
//         }
//         gate = new NotGate(gateId, inputWires[0], outputWire);
//     } else {
//         cout << "check module" << endl;
        
//         Module* blueprint = moduleManager.getBlueprint(gateType);
//         cout << "check blueprint" << endl;

//         if (blueprint) {
//             cout << "found blueprint" << endl;
            
//             if (inputWires.size() != blueprint->getNumInputs()) {
//                 cerr << "Number of wires provided does not match the module inputs" << endl;
//                 return;
//             }
//             cout << "input num corret" << endl;
//             Module* instance = moduleManager.instantiateModule(gateType, gateId, inputWires, outputWire, circuit);
//             cout << "finding the instance" << endl;
//             if (instance) {
//                 circuit.addComponent(gateId, instance);
//                 cout << "Instantiated module with ID " << gateId << endl;
//                 printWires(circuit);
//                 return;
//             } else {
//                 cerr << "Failed to instantiate module: " << gateType << endl;
//                 return;
//             }
//         } else {
//             cerr << "Gate/module not found: " << gateType << endl;
//             return;
//         }
//     }

    
//     if (gate) {
//         circuit.addComponent(gateId, gate);
//         cout << "Added " << gateType << " gate with ID " << gateId << endl;
//         printWires(circuit);
//     }
// }



void processCommand(const string& command, Circuit& circuit) {
    istringstream iss(command);
    string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        // handleNewModule(iss, circuit);
    } else if (cmdType == "instantiate_module") {
        // handleInstantiateModule(iss, circuit);
    } else if (cmdType == "add") {
        handleAddComponent(iss, globalScope);
    } else if (cmdType == "connect") {
        handleConnect(iss, globalScope);
    } else if (cmdType == "put") {
        handlePut(iss, globalScope);
    } else if (cmdType == "print") {
        handlePrint(iss, globalScope);
    } else {
        cerr << "Invalid command: " << cmdType << endl;
    }
}

int main() {
    Circuit circuit;
    string command;

    while (getline(cin, command)) {
        if (command.empty()) continue;
        processCommand(command, circuit);
    }

    return 0;
}