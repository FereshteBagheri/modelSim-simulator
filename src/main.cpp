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

    // Check if the input wire already exists in the circuit
    Component* inputWire = circuit.getComponentById(inputWireId);
    if (!inputWire) {
        inputWire = new Wire(inputWireId, nullptr);
        circuit.addComponent(inputWireId, inputWire);
    }

    // Check if the output wire already exists in the circuit
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

void handleAddGate(istringstream& iss, Circuit& circuit) {
    string gateType, gateId, outputId;
    vector<string> inputIds;

    iss >> gateType >> gateId;
    string inputId;
    while (iss >> inputId) {
        inputIds.push_back(inputId);
    }

    outputId = inputIds.back();
    inputIds.pop_back();

    Gate* gate = nullptr;
    vector<Component*> inputs;

    for (const auto& id : inputIds) {
        inputs.push_back(circuit.getComponentById(id));
    }

    if (gateType == "and") {
        gate = new AndGate(gateId, inputs);
    } else if (gateType == "or") {
        gate = new OrGate(gateId, inputs);
    }

    if (gate) {
        circuit.addComponent(gateId, gate);
        Component* outputWire = new Wire(outputId, gate);
        circuit.addComponent(outputId, outputWire);
        cout << "Added " << gateType << " gate with ID " << gateId << endl;
    } else {
        cerr << "Invalid gate type: " << gateType << endl;
    }
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
