// #include "module.h"

// using namespace std;

// Module::Module(int id, const vector<bool>& inputs, bool output)
//     : Component(id, inputs, output) {}

// void Module::addComponent(Component* component) {
//     components.push_back(component);
// }

// bool Module::evaluate() {
//     for (auto* component : components) {
//         component->evaluate();
//     }
//     output = components.back()->getOutput();
//     return output;
// }
