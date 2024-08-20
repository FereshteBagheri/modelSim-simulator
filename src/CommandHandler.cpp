#include "CommandHandler.h"
#include <iostream>

CommandHandler::CommandHandler(Scope& scope) : scope(scope) {}

void CommandHandler::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        handleAddNewModule(iss);
    } else if (cmdType == "add") {
        handleAddComponent(iss);
    } else if (cmdType == "connect") {
        handleConnect(iss);
    } else if (cmdType == "put") {
        handlePut(iss);
    } else if (cmdType == "print") {
        handlePrint(iss);
    } else {
        std::cerr << "Invalid command: " << cmdType << std::endl;
    }
}

void CommandHandler::handleAddNewModule(std::istringstream& iss) {
    std::string moduleName;
    int numInputs;
    iss >> moduleName >> numInputs;

    ModuleDefinition* moduleDef = new ModuleDefinition(moduleName, numInputs, iss);

    if (!Scope::validateModuleDefinition(moduleName, moduleDef)) {
        Scope::addModuleName(moduleName, moduleDef);
    } else {
        delete moduleDef;
    }
}

void CommandHandler::handleAddComponent(std::istringstream& iss) {
    std::string componentType, componentId, outputId;
    std::vector<std::string> passedIds;

    iss >> componentType >> componentId;

    if (scope.getComponent(componentId) != nullptr) {
        std::cerr << "Duplicate ID" << std::endl;
        return;
    }

    std::string passedId;
    while (iss >> passedId) {
        passedIds.push_back(passedId);
    }

    if ((componentType == "not" && passedIds.size() != 2) || (componentType != "not" && passedIds.size() < 3)) {
        std::cerr << "Inputs incompatible" << std::endl;
        return;
    }

    outputId = passedIds.back();
    passedIds.pop_back();

    std::vector<Wire*> inputWires;
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
        std::cerr << "Unknown gate type" << std::endl;
        return;
    }

    scope.addComponent(componentId, component);
    std::cout << "Added " << componentType << " gate with ID " << componentId << std::endl;
}

void CommandHandler::handlePrint(std::istringstream& iss) {
    std::string id;
    iss >> id;

    Component* component = scope.getComponent(id);

    if (!component) {
        std::cerr << "Invalid ID" << std::endl;
        return;
    }

    auto outputValue = component->evaluate();
    if (outputValue.has_value()) {
        std::cout << (outputValue.value() ? "1" : "0") << std::endl;
    } else {
        std::cout << "z" << std::endl;
    }
}

void CommandHandler::handleConnect(std::istringstream& iss) {
    std::string inputWireId, outputWireId;
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

    printWires();
}

void CommandHandler::handlePut(std::istringstream& iss) {
    std::string wireId;
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

void CommandHandler::printWires() const {
    std::cout << "Current wire values:" << std::endl;
    for (const auto& [id, wire] : scope.getWires()) {
        auto wireValue = wire->evaluate();
        if (wireValue.has_value()) {
            std::cout << "Wire " << id << ": " << wireValue.value() << std::endl;
        } else {
            std::cout << "Wire " << id << ": (undefined)" << std::endl;
        }
    }
}
