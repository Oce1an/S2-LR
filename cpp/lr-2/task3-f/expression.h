#ifndef EXPRESSION_H
#define EXPRESSION_H

enum class ExpressionType {
    Number,
    BinaryOperation
};

class Expression {
protected:
    ExpressionType type;

public:
    virtual ~Expression() = default;

    virtual double evaluate() const = 0;

    friend bool check_equals(Expression const* left, Expression const* right);
};

#endif