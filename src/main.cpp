#include "Circuit.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void handleNewModule(istringstream& iss, Circuit& circuit){}
void handleAddGate(istringstream& iss, Circuit& circuit);
void handleConnect(istringstream& iss, Circuit& circuit);
void handlePut(istringstream& iss, Circuit& circuit);

void printWires(Circuit& circuit){
    cout << "Current wire values:" << endl;
    for (const auto& [id, component] : circuit.getWires()) {
            Wire* wire = dynamic_cast<Wire*>(component);
            if (wire) {
                auto wireValue = wire->evaluate();
                if (wireValue.has_value()) {
                    cout << "Wire " << id << ": " << wireValue.value() << endl;
                } else {
                    cout << "Wire " << id << ": (undefined)" << endl;
                }
            }
        }
}



void handlePrint(istringstream& iss, Circuit& circuit) {
    string id;
    iss >> id;

    Component* component = circuit.getComponentById(id);
    
    if (!component) {
        cerr << "Invalid ID" << endl;
        return;
    }

    // Check if the component is a Gate
    Gate* gate = dynamic_cast<Gate*>(component);
    if (gate) {
        auto outputValue = gate->evaluate();
        if (outputValue.has_value()) {
            cout << (outputValue.value() ? "1" : "0") << endl;
        } else {
            cout << "z" << endl;
        }
        return;
    }
    cerr << "Invalid ID" << endl;

    printWires(circuit);
}



void handleConnect(istringstream& iss, Circuit& circuit) {

    string inputWireId, outputWireId;
    iss >> inputWireId >> outputWireId;

    Wire* inputWire = circuit.getWireById(inputWireId);
    Wire* outputWire = circuit.getWireById(outputWireId);

    
    if (!inputWire || !outputWire) {
        cerr <<"ID not found" << endl;
        return;
    }

    if (inputWireId == outputWireId){
        cerr << "invalid connection" <<endl;
        return;
    }

    outputWire->setInputComponent(inputWire);

    cout << "Connected " << inputWireId << " to " << outputWireId << endl;
    printWires(circuit);
    } 


void handlePut(istringstream& iss, Circuit& circuit) {
    string wireId;
    int value;
    iss >> wireId >> value;

    Wire* wire = circuit.getWireById(wireId);
    
    if (!wire) {
        cerr << "ID not found" << endl;
        return;
        
    } else if(!(value ==1 || value ==0)) {
        cerr<<"value not valid"<<endl;
        return;        
    } else {
        wire->setValue(value);
    }
    printWires(circuit);
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
        Wire* inputWire = circuit.getWireById(id);
        if (!inputWire) {
            inputWire = new Wire(id);
            circuit.addWire(id, inputWire);
        }
        inputWires.push_back(inputWire);
    }

    
    Gate* gate = nullptr;

    Wire* outputWire = circuit.getWireById(outputId);
    if (!outputWire) {
        outputWire = new Wire(outputId);
        circuit.addWire(outputId, outputWire);
    }

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
    } else if(gateType == "not") {
        gate = new NotGate(gateId, inputWires[0], outputWire);
    } else {
        cerr << "gate/module not found" << endl;
        return;
    }

    circuit.addComponent(gateId, gate);

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
