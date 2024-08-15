#ifndef WIRE_H
#define WIRE_H

#include <string>
#include <optional>
#include <unordered_map>

using namespace std;

class Wire {
private:
    string wireId;
    Wire* inputWirePtr;
    optional<bool> value;

    static unordered_map<string, Wire*> wireMap;

public:
    Wire(const string& id);
    void connectInput(Wire* input);
    void setValue(bool value);
    optional<bool> calculateOutput();
    optional<bool> getOutput();

    static Wire* getWireById(const string& id);
    static bool addWire(Wire* wire);
};

#endif // WIRE_H
