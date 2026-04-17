#include "expression.h"

bool check_equals(Expression const* left, Expression const* right) {
    
    if (left == nullptr && right == nullptr) {
        return true;
    }
    
    if (left == nullptr || right == nullptr) {
        return false;
    }
    
    return left->type == right->type;
}