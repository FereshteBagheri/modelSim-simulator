#include "CommandHandler.h"
#include <iostream>
#include <sstream>

using namespace std;

CommandHandler::CommandHandler(Scope& scope) : scope(scope) {}

void CommandHandler::processCommand(const string& command) {
    istringstream iss(command);
    string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        handleAddNewModule(iss);
    }else if (cmdType == "add") {
        handleAddComponent(iss);
    } else if (cmdType == "connect") {
        handleConnect(iss);
    } else if (cmdType == "put") {
        handlePut(iss);
    } else if (cmdType == "print") {
        handlePrint(iss);
    } else {
        cerr << "Invalid command: " << cmdType << endl;
    }
}

void CommandHandler::handleAddNewModule(istringstream& iss) {
    string moduleName;
    int numInputs;
    iss >> moduleName >> numInputs;

    if (scope.getModuleDefinition(moduleName)) {
        cerr << "Module already exists" << endl;
        return;
    }

    
    ostringstream moduleDefStream;
    string line;

    
    while (getline(cin, line)) {
        if (line == "end_module") {
            break;
        }
        if (!line.empty()) {
            moduleDefStream << line << '\n'; 
        }
    }

    if (moduleDefStream.str().empty()) {
        cerr << "Module definition is empty or missing 'end_module'" << endl;
        return;
    }

    
    istringstream moduleDefInputStream(moduleDefStream.str());

    
    ModuleDefinition* moduleDef = new ModuleDefinition(moduleName, numInputs, moduleDefInputStream);
    scope.addModuleName(moduleName, moduleDef);
}


void CommandHandler::handleAddComponent(istringstream& iss) {
    string componentType, componentId, outputId;
    vector<string> passedIds;

    iss >> componentType >> componentId;

    bool isBasicGate = scope.isBasicGate(componentType);
    bool isModule = Scope::getModuleDefinition(componentType) ? true : false;

    if( !isBasicGate && !isModule){
        cerr << "gate/module not found" << endl;
        return;
    }

    if (scope.getComponent(componentId) != nullptr) {
        cerr << "Duplicate ID" << endl;
        return;
    }

    string passedId;
    while (iss >> passedId) {
        passedIds.push_back(passedId);
    }

    outputId = passedIds.back();
    passedIds.pop_back();

    vector<Wire*> inputWires = createOrRetrieveWires(passedIds);
    Wire* outputWire = createOrRetrieveWire(outputId);

    Component* component = nullptr;
    if (isBasicGate) {

        component = createBasicGate(componentType, componentId, inputWires, outputWire);
    } else{

        component = createModule(componentType, componentId, inputWires, outputWire);
    }
    
    scope.addComponent(componentId, component);

    cout << "Added " << componentType << " with ID " << componentId << endl;

}

vector<Wire*> CommandHandler::createOrRetrieveWires(const vector<string>& ids) {
    vector<Wire*> wires;
    for (const auto& id : ids) {
        Wire* wire = scope.getWire(id);
        if (!wire) {
            wire = new Wire(id);
            scope.addWire(id, wire);
        }
        wires.push_back(wire);
    }
    return wires;
}

Wire* CommandHandler::createOrRetrieveWire(const string& id) {
    Wire* wire = scope.getWire(id);
    if (!wire) {
        wire = new Wire(id);
        scope.addWire(id, wire);
    }
    return wire;
}

Component* CommandHandler::createBasicGate(const string& type, const string& id, const vector<Wire*>& inputWires, Wire* outputWire) {
    if ((type == "not" && inputWires.size() != 1) || (type != "not" && inputWires.size() < 2)) {
        cerr << "Inputs incompatible" << endl;
        return nullptr;
    }
    if (type == "and") {
        return new AndGate(id, inputWires, outputWire);
    } else if (type == "or") {
        return new OrGate(id, inputWires, outputWire);
    } else if (type == "xor") {
        return new XorGate(id, inputWires, outputWire);
    } else if (type == "nand") {
        return new NandGate(id, inputWires, outputWire);
    } else if (type == "nor") {
        return new NorGate(id, inputWires, outputWire);
    } else if (type == "not") {
        return new NotGate(id, inputWires[0], outputWire);
    }
    return nullptr;
}

Component* CommandHandler::createModule(const string& moduleName, const string& instanceId, const vector<Wire*>& inputWires, Wire* outputWire) {
    const ModuleDefinition* moduleDef = Scope::getModuleDefinition(moduleName);
    return new Module(instanceId, *moduleDef, inputWires, outputWire, scope);
}

void CommandHandler::handlePrint(istringstream& iss) {
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

void CommandHandler::handleConnect(istringstream& iss) {
    string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Wire* inputWire = scope.getWire(inputWireId);
    Wire* outputWire = scope.getWire(outputWireId);

    if (!inputWire || !outputWire) {
        cerr << "ID not found" << endl;
        return;
    }

    if (inputWireId == outputWireId) {
        cerr << "Invalid connection" << endl;
        return;
    }

    outputWire->setInputComponent(inputWire);
    cout << "Connected " << inputWireId << " to " << outputWireId << endl;

}

void CommandHandler::handlePut(istringstream& iss) {
    string wireId;
    int value;
    iss >> wireId >> value;

    Wire* wire = scope.getWire(wireId);

    if (!wire) {
        cerr << "ID not found" << endl;
        return;
    }

    if (value != 0 && value != 1) {
        cerr << "Value not valid" << endl;
        return;
    }

    wire->setValue(value);
}