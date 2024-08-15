#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <string>
#include <optional>

using namespace std;

class Wire {
private:
    string wireId;
    Wire* inputWirePtr;
    optional<bool> value; // Use 'bool' for 0 or 1. For 'Z' (unknown), use a specific representation.

public:
    Wire(string id);
    void connectInput(Wire* input);
    void setValue(bool value);
    optional<bool> calculateOutput();
    optional<bool> getOutput();
};

#endif // WIRE_H
