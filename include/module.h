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
    
    Module(const string& id, int numInputs);

    
    Module(const string& id, const Module* blueprint, const vector<Wire*>& inputWires, Wire* outputWire);

    
    void addComponent(const string& id, Component* component);

    
    void addWire(const string& id, Wire* wire);

    
    void connectInternal(const string& fromId, const string& toId);

    
    optional<bool> evaluate() override;

    
    Wire* getInput(int index) const;

    
    Wire* getOutput() const;

    int getNumInputs() const;

    
    Wire* getInternalWire(const string& id) const;

private:
    string id; 
    int numInputs;                              
    vector<Wire*> inputs;                  
    Wire* output;                               
    map<string, Component*> components;  
    map<string, Wire*> wires;         

    
    void setupConnections(const vector<Wire*>& inputWires, Wire* outputWire);
};

#endif 
