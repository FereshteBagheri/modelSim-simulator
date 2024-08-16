#include "Circuit.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void handleNewModule(istringstream& iss, Circuit& circuit){}
void handleAddGate(istringstream& iss, Circuit& circuit);
void handleConnect(istringstream& iss, Circuit& circuit);
void handlePut(istringstream& iss, Circuit& circuit);
void handlePrint(istringstream& iss, Circuit& circuit){}

void handleConnect(std::istringstream& iss, Circuit& circuit) {
    std::string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Component* inputWire = circuit.getComponentById(inputWireId);
    if (!inputWire) {
        inputWire = new Wire(inputWireId, nullptr);
        circuit.addComponent(inputWireId, inputWire);
    }

    Component* outputWire = circuit.getComponentById(outputWireId);
    if (!outputWire) {
        outputWire = new Wire(outputWireId, inputWire);
        circuit.addComponent(outputWireId, outputWire);
    }

    inputWire->addConnectedComponent(outputWire);

    std::cout << "Connected " << inputWireId << " to " << outputWireId << std::endl;
}


void handlePut(std::istringstream& iss, Circuit& circuit) {
    std::string wireId;
    bool value;
    iss >> wireId >> value;

    Wire* wire = dynamic_cast<Wire*>(circuit.getComponentById(wireId));
    
    if (wire) {
        wire->setValue(value);
        

        // Print the values of all wires
        std::cout << "Current wire values:" << std::endl;
        for (const auto& [id, component] : circuit.getComponents()) {
            Wire* wire = dynamic_cast<Wire*>(component);
            if (wire) {
                auto wireValue = wire->getOutput();
                if (wireValue.has_value()) {
                    std::cout << "Wire " << id << ": " << wireValue.value() << std::endl;
                } else {
                    std::cout << "Wire " << id << ": (undefined)" << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Wire " << wireId << " not found" << std::endl;
    }
}

void handleAddGate(std::istringstream& iss, Circuit& circuit) {
    std::string gateType, gateId, outputId;
    std::vector<std::string> inputIds;

    iss >> gateType >> gateId;

    // Check if the gate/module ID already exists in the circuit
    if (circuit.getComponentById(gateId)) {
        std::cerr << "ID duplicate" << std::endl;
        return;
    }

    std::string inputId;
    while (iss >> inputId) {
        inputIds.push_back(inputId);
    }

    // The last ID is considered the output wire ID
    outputId = inputIds.back();
    inputIds.pop_back();

    // Check the number of inputs for the gate
    if (gateType == "not") {
        if (inputIds.size() != 1) {
            std::cerr << "inputs incompatible" << std::endl;
            return;
        }
    } else if (inputIds.size() < 2) {
        std::cerr << "inputs incompatible" << std::endl;
        return;
    }

    // Prepare the input wires vector
    std::vector<Wire*> inputWires;
    for (const auto& id : inputIds) {
        Wire* inputWire = dynamic_cast<Wire*>(circuit.getComponentById(id));
        if (!inputWire) {
            inputWire = new Wire(id);
            circuit.addComponent(id, inputWire);
        }
        inputWires.push_back(inputWire);
    }

    // Create the gate based on the type
    Gate* gate = nullptr;

    if (gateType == "and") {
        gate = new AndGate(gateId, inputWires);
    } else if (gateType == "or") {
        gate = new OrGate(gateId, inputWires);
    } else {
        std::cerr << "gate/module not found" << std::endl;
        return;
    }

    // Add the gate to the circuit
    circuit.addComponent(gateId, gate);

    // Create the output wire if it doesn't exist and connect it to the gate
    Wire* outputWire = dynamic_cast<Wire*>(circuit.getComponentById(outputId));
    if (!outputWire) {
        outputWire = new Wire(outputId);
        circuit.addComponent(outputId, outputWire);
    }

    gate->setOutput(outputWire);
    std::cout << "Added " << gateType << " gate with ID " << gateId << std::endl;
}




void processCommand(const string& command, Circuit& circuit) {
    istringstream iss(command);
    string cmdType;
    iss >> cmdType;

    if (cmdType == "new_module") {
        handleNewModule(iss, circuit);
    } else if (cmdType == "add") {
        handleAddGate(iss, circuit);
    } else if (cmdType == "connect") {
        handleConnect(iss, circuit);
    } else if (cmdType == "put") {
        handlePut(iss, circuit);
    } else if (cmdType == "print") {
        handlePrint(iss, circuit);
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
