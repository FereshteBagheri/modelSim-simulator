#include "CommandHandler.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    Scope globalScope;
    CommandHandler handler(globalScope);
    string command;

    while (getline(cin, command)) {

        if (command.empty()) continue;
        handler.processCommand(command);
    }
    return 0;
}
