#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Scope.h"
#include "ModuleDefinition.h"
#include "Circuit.h"
#include <string>
#include <sstream>

class CommandHandler {
public:
    CommandHandler(Scope& scope);

    void processCommand(const std::string& command);

private:
    void handleAddNewModule(std::istringstream& iss);
    void handleAddComponent(std::istringstream& iss);
    void handlePrint(std::istringstream& iss);
    void handleConnect(std::istringstream& iss);
    void handlePut(std::istringstream& iss);

    void printWires() const;

    Scope& scope;
};

#endif // COMMANDHANDLER_H
