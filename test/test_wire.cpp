#include "wire.h"
#include <iostream>
#include <cassert>

using namespace std;

void testInitialization() {
    Wire wire("W1");
    assert(wire.getOutput() == nullopt);
    cout << "testInitialization passed" << endl;
}

void testSetValue() {
    Wire wire("W2");
    wire.setValue(true);
    assert(wire.getOutput() == true);
    wire.setValue(false);
    assert(wire.getOutput() == false);
    cout << "testSetValue passed" << endl;
}

void testConnectAndCalculateOutput() {
    Wire wire1("W3");
    Wire wire2("W4");
    
    wire1.setValue(true);
    wire2.connectInput(&wire1);
    
    assert(wire2.calculateOutput() == true); // wire2 should take the value from wire1
    cout << "testConnectAndCalculateOutput passed" << endl;
}

void testConnectionWithNullValue() {
    Wire wire1("W5");
    Wire wire2("W6");
    
    wire2.connectInput(&wire1);
    assert(wire2.calculateOutput() == nullopt); // wire2 should be nullopt since wire1 has no value set
    wire1.setValue(false);
    assert(wire2.calculateOutput() == false); // wire2 should reflect the updated value of wire1
    cout << "testConnectionWithNullValue passed" << endl;
}

void runTests() {
    testInitialization();
    testSetValue();
    testConnectAndCalculateOutput();
    testConnectionWithNullValue();
}

int main() {
    runTests();
    cout << "All tests passed" << endl;
    return 0;
}
