#include "binaryop.h"
#include <stdexcept>

BinaryOperation::BinaryOperation(Expression* leftOperand, char operation, Expression* rightOperand)
    : left(leftOperand), right(rightOperand), op(operation) {
    type = ExpressionType::BinaryOperation;
}

BinaryOperation::~BinaryOperation() {
    delete left;
    delete right;
}

double BinaryOperation::evaluate() const {
    double leftValue = left->evaluate();
    double rightValue = right->evaluate();
    
    switch (op) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/':
            if (rightValue == 0.0) {
                throw std::runtime_error("Division by zero");
            }
            return leftValue / rightValue;
        default:
            throw std::runtime_error("Unknown operation");
    }
}