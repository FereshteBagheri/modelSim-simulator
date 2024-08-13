// src/main.cpp
#include <iostream>
#include "Gate.h"

int main() {
    AndGate andGate;
    bool input1 = true;
    int input2 = 1;
    
    bool result = andGate.compute(input1, input2);
    std::cout << "AND Gate Result: " << result << std::endl;

    return 0;
}
