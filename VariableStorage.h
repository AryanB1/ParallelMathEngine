#ifndef VARIABLESTORAGE_H
#define VARIABLESTORAGE_H
#include <unordered_map>
#include <string>
#include <stdexcept>

class VariableStorage {
public:
    std::unordered_map<std::string, int> variables;

    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }

    int getVariable(const std::string& name) const {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }

    bool isVariableDefined(const std::string& name) const {
        return variables.find(name) != variables.end();
    }
};

#endif //VARIABLESTORAGE_H
