#include "ModuleManager.h"
#include "Gate.h"
#include "Wire.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "NotGate.h"
#include <sstream>
#include <iostream>


void ModuleManager::handleModuleDefinition(const std::string& moduleId, int numInputs, Circuit& circuit, std::istream& commandStream) {
    // Create a new module blueprint
    Module* module = new Module(moduleId, numInputs);
    addBlueprint(moduleId, module);

    std::string line;
    while (std::getline(commandStream, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "end_module") {
            break;  // End the module definition
        }

        if (command == "add") {
            // Parse and add components to the module
            std::string gateType, gateId, outputId;
            std::vector<std::string> inputIds;

            iss >> gateType >> gateId;

            if (module->components.find(gateId) != module->components.end()) {
                std::cerr << "Component ID duplicate within module: " << gateId << std::endl;
                continue;
            }

            std::string inputId;
            while (iss >> inputId) {
                inputIds.push_back(inputId);
            }

            outputId = inputIds.back();
            inputIds.pop_back();

            std::vector<Wire*> inputWires;
            for (const auto& id : inputIds) {
                Wire* inputWire = module->getInternalWire(id);
                if (!inputWire) {
                    inputWire = new Wire(id);
                    module->addWire(id, inputWire);
                }
                inputWires.push_back(inputWire);
            }

            Wire* outputWire = module->getInternalWire(outputId);
            if (!outputWire) {
                outputWire = new Wire(outputId);
                module->addWire(outputId, outputWire);
            }

            Gate* gate = nullptr;
            if (gateType == "and") {
                gate = new AndGate(gateId, inputWires, outputWire);
            } else if (gateType == "or") {
                gate = new OrGate(gateId, inputWires, outputWire);
            } else if (gateType == "xor") {
                gate = new XorGate(gateId, inputWires, outputWire);
            } else if (gateType == "nand") {
                gate = new NandGate(gateId, inputWires, outputWire);
            } else if (gateType == "nor") {
                gate = new NorGate(gateId, inputWires, outputWire);
            } else if (gateType == "not") {
                gate = new NotGate(gateId, inputWires[0], outputWire);
            } else {
                std::cerr << "Unknown gate type: " << gateType << std::endl;
                continue;
            }

            module->addComponent(gateId, gate);
        } else if (command == "connect") {
            std::string fromId, toId;
            iss >> fromId >> toId;

            Wire* fromWire = module->getInternalWire(fromId);
            Wire* toWire = module->getInternalWire(toId);

            if (!fromWire || !toWire) {
                std::cerr << "Wire ID not found within module: " << fromId << " or " << toId << std::endl;
                continue;
            }

            toWire->setInputComponent(fromWire);
        } else if (command == "put") {
            // Handle the 'put' command to set the value of a wire within the module
            std::string wireId;
            int value;
            iss >> wireId >> value;

            Wire* wire = module->getInternalWire(wireId);

            if (!wire) {
                std::cerr << "Wire ID not found within module: " << wireId << std::endl;
                continue;
            }

            if (value != 0 && value != 1) {
                std::cerr << "Invalid value for wire: " << value << std::endl;
                continue;
            }

            wire->setValue(value);
            std::cout << "Set value of wire " << wireId << " to " << value << std::endl;
        } else {
            std::cerr << "Unknown command within module: " << command << std::endl;
        }
    }
}
