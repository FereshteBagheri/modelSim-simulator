#include "gate.h"
#include "module.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<bool> gateInputs1 = {true, false};
    Gate andGate("and", 1, gateInputs1, false);
    
    vector<bool> gateInputs2 = {true, true};
    Gate orGate("or", 2, gateInputs2, false);

    vector<bool> moduleInputs = {true, false};
    Module myModule(3, moduleInputs, false);
    myModule.addComponent(&andGate);
    myModule.addComponent(&orGate);

    myModule.evaluate();
    cout << "Module output: " << myModule.getOutput() << endl;

    return 0;
}
