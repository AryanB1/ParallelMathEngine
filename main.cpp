#include <iostream>
#include <string>
#include "Parser.h"
#include "Evaluator.h"
#include "VariableStorage.h"

int main() {
    VariableStorage storage;
    std::string expression;

    while (true) {
        // Prompts the user to enter an expression
        std::cout << "Enter an arithmetic expression (or type 'exit' to quit): ";
        std::getline(std::cin, expression);
        if (expression == "exit") {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        try {
            // Parses the expression and store the result if it contains an assignment
            auto root = Parser::parse(expression, storage);

            // Evaluate the expression if it is not an assignment
            if (expression.find('=') == std::string::npos) {
                int result = Evaluator::evaluate_multithreaded(root);
                std::cout << "Result: " << result << std::endl;
            } else {
                std::cout << "Variable assigned successfully!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
