#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <optional>
#include <string>

using namespace std;

class Component {
protected:
    string id;

public:
    Component(const string& id);

    virtual optional<bool> evaluate() = 0;
    

    const string& getId() const;

};

#endif
