// OperandNode.h
#ifndef OPERANDNODE_H
#define OPERANDNODE_H

#include "Node.h"

class OperandNode : public Node {
    int value;

public:
    OperandNode(int val) : value(val) {}
    int evaluate() override {
        return value;
    }
};

#endif  // OPERANDNODE_H
