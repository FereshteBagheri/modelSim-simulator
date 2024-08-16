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

void printWires(Circuit& circuit){
    cout << "Current wire values:" << endl;
    for (const auto& [id, component] : circuit.getComponents()) {
            Wire* wire = dynamic_cast<Wire*>(component);
            if (wire) {
                auto wireValue = wire->getOutput();
                if (wireValue.has_value()) {
                    cout << "Wire " << id << ": " << wireValue.value() << endl;
                } else {
                    cout << "Wire " << id << ": (undefined)" << endl;
                }
            }
        }
}

void handleConnect(istringstream& iss, Circuit& circuit) {

    string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Component* inputWire = circuit.getComponentById(inputWireId);
    Component* outputWire = circuit.getComponentById(outputWireId);

    
    if (!inputWire || !outputWire) {
        cerr <<"ID not found" << endl;
        return;
    }

    if (inputWireId == outputWireId){
        cerr << "invalid connection" <<endl;
        return;
    }

    inputWire->addConnectedComponent(outputWire);
    outputWire->evaluate();

    cout << "Connected " << inputWireId << " to " << outputWireId << endl;

    printWires(circuit);
    } 


void handlePut(istringstream& iss, Circuit& circuit) {
    string wireId;
    bool value;
    iss >> wireId >> value;

    Wire* wire = dynamic_cast<Wire*>(circuit.getComponentById(wireId));
    
    if (!wire) {
        cerr << "ID not found" << endl;
        return;
        
    } else if(value !=1 && value !=0) {
        cerr<<"value not valid"<<endl;
        return;        
    } else {
        wire->setValue(value);
        printWires(circuit);
    }
}

void handleAddGate(istringstream& iss, Circuit& circuit) {
    string gateType, gateId, outputId;
    vector<string> inputIds;

    iss >> gateType >> gateId;

    
    if (circuit.getComponentById(gateId)) {
        cerr << "ID duplicate" << endl;
        return;
    }

    string inputId;
    while (iss >> inputId) {
        inputIds.push_back(inputId);
    }

    
    outputId = inputIds.back();
    inputIds.pop_back();

    
    if (gateType == "not") {
        if (inputIds.size() != 1) {
            cerr << "inputs incompatible" << endl;
            return;
        }
    } else if (inputIds.size() < 2) {
        cerr << "inputs incompatible" << endl;
        return;
    }

    
    vector<Wire*> inputWires;
    for (const auto& id : inputIds) {
        Wire* inputWire = dynamic_cast<Wire*>(circuit.getComponentById(id));
        if (!inputWire) {
            inputWire = new Wire(id);
            circuit.addComponent(id, inputWire);
        }
        inputWires.push_back(inputWire);
    }

    
    Gate* gate = nullptr;

    if (gateType == "and") {
        gate = new AndGate(gateId, inputWires);
    } else if (gateType == "or") {
        gate = new OrGate(gateId, inputWires);
    } else if (gateType == "xor") {
        gate = new XorGate(gateId, inputWires);
    } else if (gateType == "nand") {
        gate = new NandGate(gateId, inputWires);
    } else if (gateType == "nor") {
        gate = new NorGate(gateId, inputWires);
    } else if(gateType == "not") {
        gate = new NotGate(gateId, inputWires[0]);
    } else {
        cerr << "gate/module not found" << endl;
        return;
    }

    
    circuit.addComponent(gateId, gate);

    
    Wire* outputWire = dynamic_cast<Wire*>(circuit.getComponentById(outputId));
    if (!outputWire) {
        outputWire = new Wire(outputId);
        circuit.addComponent(outputId, outputWire);
    }

    gate->setOutput(outputWire);
    gate->evaluate();

    cout << "Added " << gateType << " gate with ID " << gateId << endl;

    
    printWires(circuit);
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
