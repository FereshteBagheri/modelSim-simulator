#include "wire.h"
#include <iostream>
#include <cassert>

using namespace std;

void testWireCreationWithUniqueID() {
    try {
        Wire wire1("W1");
        Wire wire2("W2");
        
        assert(Wire::getWireById("W1") == &wire1);
        assert(Wire::getWireById("W2") == &wire2);

        cout << "testWireCreationWithUniqueID passed" << endl;
    } catch (const runtime_error& e) {
        cout << "testWireCreationWithUniqueID failed: " << e.what() << endl;
    }
}

void testDuplicateWireID() {
    try {
        Wire wire1("W3");
        Wire wireDuplicate("W3"); // Should throw an exception
        cout << "testDuplicateWireID failed: Exception not thrown" << endl;
    } catch (const runtime_error& e) {
        cout << "testDuplicateWireID passed: " << e.what() << endl;
    }
}

void testWireConnection() {
    Wire wire1("W4");
    Wire wire2("W5");
    
    wire1.setValue(true);
    wire2.connectInput(&wire1);
    
    assert(wire2.calculateOutput() == true);
    cout << "testWireConnection passed" << endl;
}

void testWireSetValue() {
    Wire wire1("W6");
    wire1.setValue(true);
    assert(wire1.getOutput() == true);
    
    wire1.setValue(false);
    assert(wire1.getOutput() == false);
    
    cout << "testWireSetValue passed" << endl;
}

void testWireConnectionWithNullValue() {
    Wire wire1("W7");
    Wire wire2("W8");
    
    wire2.connectInput(&wire1);
    assert(wire2.calculateOutput() == nullopt);
    
    wire1.setValue(false);
    assert(wire2.calculateOutput() == false);
    
    cout << "testWireConnectionWithNullValue passed" << endl;
}

void runTests() {
    testWireCreationWithUniqueID();
    testDuplicateWireID();
    testWireConnection();
    testWireSetValue();
    testWireConnectionWithNullValue();
}

int main() {
    runTests();
    cout << "All tests passed" << endl;
    return 0;
}
