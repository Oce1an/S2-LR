#ifndef BINARYOP_H
#define BINARYOP_H

#include "expression.h"

class BinaryOperation : public Expression {
private:
    Expression* left;
    Expression* right;
    char op;

public:
    BinaryOperation(Expression* leftOperand, char operation, Expression* rightOperand);
    ~BinaryOperation() override;
    double evaluate() const override;
    
    Expression* getLeft() const { return left; }
    Expression* getRight() const { return right; }
    char getOperation() const { return op; }
};

#endif