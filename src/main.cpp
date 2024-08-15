#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class Circuit {
public:
    int id;
};

void handleNewModule(istringstream& iss, Circuit& circuit);
void handleAddGate(istringstream& iss, Circuit& circuit);
void handleConnect(istringstream& iss, Circuit& circuit);
void handlePut(istringstream& iss, Circuit& circuit);
void handlePrint(istringstream& iss, Circuit& circuit);

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

void handleNewModule(istringstream& iss, Circuit& circuit) {
    cout << "Handling new_module command" << endl;
}

void handleAddGate(istringstream& iss, Circuit& circuit) {
    cout << "Handling add command" << endl;
}

void handleConnect(istringstream& iss, Circuit& circuit) {
    cout << "Handling connect command" << endl;
}

void handlePut(istringstream& iss, Circuit& circuit) {
    cout << "Handling put command" << endl;
}

void handlePrint(istringstream& iss, Circuit& circuit) {
    cout << "Handling print command" << endl;
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
