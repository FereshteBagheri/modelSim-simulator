#include "CommandHandler.h"
#include "ErrorMessages.h"
#include "TrackingStreamBuf.h"

#include <iostream>
#include <sstream>

using namespace std;

CommandHandler::CommandHandler(Scope& scope) : scope(scope) {}

bool CommandHandler::processCommand(const string& command) {
    istringstream iss(command);
    string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        return handleAddNewModule(iss);
    }else if (cmdType == "add") {
        return handleAddComponent(iss);
    } else if (cmdType == "connect") {
        return handleConnect(iss);
    } else if (cmdType == "put") {
        return handlePut(iss);
    } else if (cmdType == "print") {
        return handlePrint(iss);
    } else {
        cerr << ErrorMessages::INVALID_COMMAND << cmdType << endl;
        return false;
    }
}

bool CommandHandler::handleAddNewModule(istringstream& iss) {
    string moduleName;
    int numInputs;
    iss >> moduleName >> numInputs;

    if(!validator.validateNewModule(scope, moduleName)) {
        return false;
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

    istringstream moduleDefInputStream(moduleDefStream.str());

    ModuleDefinition* moduleDef = new ModuleDefinition(moduleName, numInputs, moduleDefInputStream);
    scope.addModuleName(moduleName, moduleDef);
    return true;
}

bool CommandHandler::handleAddComponent(istringstream& iss) {
    string componentType, componentId, outputId;
    vector<string> passedIds;

    iss >> componentType >> componentId;

    string passedId;
    while (iss >> passedId) {
        passedIds.push_back(passedId);
    }

    if(!validator.validateAddComponent(scope, componentType, componentId, passedIds.size())) {
        return false;
    }

    outputId = passedIds.back();
    passedIds.pop_back();

    vector<Wire*> inputWires = createOrRetrieveWires(passedIds);
    Wire* outputWire = createOrRetrieveWire(outputId);

    Component* component = nullptr;
    if (scope.isBasicGate(componentType)) {
        component = createBasicGate(componentType, componentId, inputWires, outputWire);
    } else{
        component = createModule(componentType, componentId, inputWires, outputWire);
    }
    
    scope.addComponent(componentId, component);
    return true;
}

bool CommandHandler::handlePrint(istringstream& iss) {
    string id;
    iss >> id;

    if(!validator.validatePrint(scope, id)) {
        return false;
    }
    
    Component* component = scope.getComponent(id);
    auto outputValue = component->evaluate();

    if (outputValue.has_value()) {
        cout << (outputValue.value() ? "1" : "0") << endl;
    } else {
        cout << "z" << endl;
    }
    return true;
}

bool CommandHandler::handleConnect(istringstream& iss) {
    string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Wire* inputWire = scope.getWire(inputWireId);
    Wire* outputWire = scope.getWire(outputWireId);

    if (!inputWire || !outputWire) {
        cerr << ErrorMessages::ID_NOT_FOUND << endl;
        return false;
    }

    if (inputWireId == outputWireId) {
        cerr << ErrorMessages::INVALID_CONNECTION << endl;
        return false;
    }

    outputWire->setInputComponent(inputWire);
    return true;
}

bool CommandHandler::handlePut(istringstream& iss) {
    string wireId;
    int value;
    iss >> wireId >> value;

    Wire* wire = scope.getWire(wireId);

    if (!wire) {
        cerr << ErrorMessages::ID_NOT_FOUND << endl;
        return false;
    }

    if (value != 0 && value != 1) {
        cerr << ErrorMessages::VALUE_NOT_VALID << endl;
        return false;
    }

    wire->setValue(value);
    return true;
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
    return new Module(instanceId, *moduleDef, inputWires, outputWire);
}
