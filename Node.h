// Node.h
#ifndef NODE_H
#define NODE_H

class Node {
public:
    virtual ~Node() = default;
    virtual int evaluate() = 0;
};

#endif  // NODE_H
