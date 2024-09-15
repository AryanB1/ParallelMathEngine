// OperatorNode.h
#ifndef OPERATORNODE_H
#define OPERATORNODE_H

#include "Node.h"
#include <memory>

class OperatorNode : public Node {
    char op;

public:
    OperatorNode(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
            : op(o), left(std::move(l)), right(std::move(r)) {}

    int evaluate() override {
        if (op == '+') {
            return left->evaluate() + right->evaluate();
        } else if (op == '*') {
            return left->evaluate() * right->evaluate();
        }
        else if (op == '-') {
            return left->evaluate() - right->evaluate();
        }
        else if (op == '/') {
            return left->evaluate() - right->evaluate();
        }
        return 0;
    }

    std::unique_ptr<Node> right;
    std::unique_ptr<Node> left;
};

#endif
