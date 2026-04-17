#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"

class Number : public Expression {
private:
    double value;

public:
    explicit Number(double val = 0.0);
    ~Number() override = default;
    double evaluate() const override;
    
    double getValue() const { return value; }
};

#endif