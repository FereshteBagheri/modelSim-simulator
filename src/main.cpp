#include "Circuit.h"
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
    
}

void processCommand(const string& command, Circuit& circuit) {
    istringstream iss(command);
    string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        
    } else if (cmdType == "instantiate_module") {
        
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