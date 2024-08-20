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


void ModuleManager::handleModuleDefinition(const string& moduleId, int numInputs, Circuit& circuit, istream& commandStream) {
    
    Module* module = new Module(moduleId, numInputs);
    addBlueprint(moduleId, module);

    string line;
    while (getline(commandStream, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "end_module") {
            break;  
        }

        if (command == "add") {
            
            string gateType, gateId, outputId;
            vector<string> inputIds;

            iss >> gateType >> gateId;

            if (module->components.find(gateId) != module->components.end()) {
                cerr << "Component ID duplicate within module: " << gateId << endl;
                continue;
            }

            string inputId;
            while (iss >> inputId) {
                inputIds.push_back(inputId);
            }

            outputId = inputIds.back();
            inputIds.pop_back();

            vector<Wire*> inputWires;
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
                cerr << "Unknown gate type: " << gateType << endl;
                continue;
            }

            module->addComponent(gateId, gate);
        } else if (command == "connect") {
            string fromId, toId;
            iss >> fromId >> toId;

            Wire* fromWire = module->getInternalWire(fromId);
            Wire* toWire = module->getInternalWire(toId);

            if (!fromWire || !toWire) {
                cerr << "Wire ID not found within module: " << fromId << " or " << toId << endl;
                continue;
            }

            toWire->setInputComponent(fromWire);
        } else if (command == "put") {
            
            string wireId;
            int value;
            iss >> wireId >> value;

            Wire* wire = module->getInternalWire(wireId);

            if (!wire) {
                cerr << "Wire ID not found within module: " << wireId << endl;
                continue;
            }

            if (value != 0 && value != 1) {
                cerr << "Invalid value for wire: " << value << endl;
                continue;
            }

            wire->setValue(value);
            cout << "Set value of wire " << wireId << " to " << value << endl;
        } else {
            cerr << "Unknown command within module: " << command << endl;
        }
    }
}
