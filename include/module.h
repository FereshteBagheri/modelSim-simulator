#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include <map>
#include <optional>
#include "Wire.h"
#include "Component.h"

class Module : public Component {
public:
    // Blueprint Constructor
    Module(const std::string& id, int numInputs);

    // Circuit Instantiation Constructor (Deep Copy Constructor)
    Module(const std::string& id, const Module* blueprint, const std::vector<Wire*>& inputWires, Wire* outputWire);

    // Add a component (gate/module) to the module (during blueprint creation)
    void addComponent(const std::string& id, Component* component);

    // Add a wire to the module (during blueprint creation)
    void addWire(const std::string& id, Wire* wire);

    // Connect internal wires (during blueprint creation)
    void connectInternal(const std::string& fromId, const std::string& toId);

    // Evaluate the module's output
    std::optional<bool> evaluate() override;

    // Get an input wire by index (for blueprint creation)
    Wire* getInput(int index) const;

    // Get the output wire (for blueprint creation)
    Wire* getOutput() const;

    int getNumInputs() const;

    // Get internal wire by ID
    Wire* getInternalWire(const std::string& id) const;

private:
    std::string id; 
    int numInputs;                              // Module ID
    std::vector<Wire*> inputs;                  // Input wires (in0, in1, ...)
    Wire* output;                               // Output wire (out)
    std::map<std::string, Component*> components;  // Internal components (gates/modules)
    std::map<std::string, Wire*> wires;         // Internal wires

    // Internal function to set up connections in instantiated modules
    void setupConnections(const std::vector<Wire*>& inputWires, Wire* outputWire);
};

#endif // MODULE_H
