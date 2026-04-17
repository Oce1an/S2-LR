#include "number.h"

Number::Number(double val) : value(val) {
    type = ExpressionType::Number;
}

double Number::evaluate() const {
    return value;
}