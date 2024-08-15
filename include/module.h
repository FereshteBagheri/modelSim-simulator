#ifndef MODULE_H
#define MODULE_H

#include "component.h"
#include <vector>

using namespace std;

class Module : public Component {
private:
    vector<Component*> components;

public:
    Module(int id, const vector<bool>& inputs, bool output);
    void addComponent(Component* component);
    bool evaluate() override;
};

#endif // MODULE_H
