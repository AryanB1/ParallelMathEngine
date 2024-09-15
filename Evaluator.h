#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Node.h"
#include <thread>
#include <future>

class Evaluator {
public:
    static int evaluate_multithreaded(std::unique_ptr<Node>& root) {
        if (!root) return 0;

        // Multithreaded evaluation
        std::future<int> left_result = std::async(std::launch::async, [&]() {
            if (auto op_node = dynamic_cast<OperatorNode*>(root.get())) {
                return op_node->left->evaluate();
            }
            return 0;
        });

        std::future<int> right_result = std::async(std::launch::async, [&]() {
            if (auto op_node = dynamic_cast<OperatorNode*>(root.get())) {
                return op_node->right->evaluate();
            }
            return 0;
        });

        return left_result.get() + right_result.get();  // Returns the combined result
    }
};

#endif
