// include/Gate.h
#ifndef GATE_H
#define GATE_H

class Gate {
public:
    virtual bool compute(bool input1, bool input2) = 0;  // Pure virtual function
};

class AndGate : public Gate {
public:
    bool compute(bool input1, bool input2) override;
};

#endif // GATE_H
