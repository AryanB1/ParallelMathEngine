#ifndef PARSER_H
#define PARSER_H
#include "OperandNode.h"
#include "OperatorNode.h"
#include "VariableStorage.h"
#include <string>
#include <stack>
#include <memory>
#include <cctype>
#include <algorithm>

class Parser {
public:
    static std::unique_ptr<Node> parse(const std::string& expression, VariableStorage& storage) {
        std::stack<std::unique_ptr<Node>> operands;
        std::stack<char> operators;

        size_t assignmentPos = expression.find('=');
        std::string variableName;
        std::string expressionToEvaluate;

        // Check if this is an assignment
        if (assignmentPos != std::string::npos) {
            // Extract the variable name (left side of '=')
            variableName = expression.substr(0, assignmentPos);
            variableName.erase(remove_if(variableName.begin(), variableName.end(), isspace), variableName.end()); // trim spaces

            // The rest of the expression is what we need to evaluate
            expressionToEvaluate = expression.substr(assignmentPos + 1);
        } else {
            // No assignment, treat the whole expression as a regular one
            expressionToEvaluate = expression;
        }

        // Parse and evaluate the expression part
        for (size_t i = 0; i < expressionToEvaluate.length(); ++i) {
            char token = expressionToEvaluate[i];

            // Handle numeric values
            if (isdigit(token)) {
                operands.push(std::make_unique<OperandNode>(token - '0'));
            }

            // Handle operators
            else if (token == '+' || token == '*') {
                operators.push(token);
            }

            // Handle closing parenthesis
            else if (token == ')') {
                char op = operators.top();
                operators.pop();
                auto right = std::move(operands.top());
                operands.pop();
                auto left = std::move(operands.top());
                operands.pop();
                operands.push(std::make_unique<OperatorNode>(op, std::move(left), std::move(right)));
            }
        }

        // If it's an assignment, we store the result in the variable
        if (!variableName.empty()) {
            int result = operands.top()->evaluate();
            storage.setVariable(variableName, result);
        }

        return std::move(operands.top());
    }
};

#endif
