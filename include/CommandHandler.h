#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Scope.h"
#include "ModuleDefinition.h"
#include "Module.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NandGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "NotGate.h"

#include <string>
#include <sstream>

class CommandHandler {
public:
    CommandHandler(Scope& scope);

    void processCommand(const string& command);

private:
    Scope& scope;

    void handleAddNewModule(istringstream& iss);
    void handleAddComponent(istringstream& iss);
    void handlePrint(istringstream& iss);
    void handleConnect(istringstream& iss);
    void handlePut(istringstream& iss);

    vector<Wire*> createOrRetrieveWires(const vector<string>& ids);
    Wire* createOrRetrieveWire(const string& id);

    Component* createBasicGate(const string& type, const string& id, const vector<Wire*>& inputWires, Wire* outputWire);
    Component* createModule(const string& moduleName, const string& instanceId, const vector<Wire*>& inputWires, Wire* outputWire);
};

#endif
