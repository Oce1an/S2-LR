#include <iostream>
#include "number.h"
#include "binaryop.h"

bool check_equals(Expression const* left, Expression const* right);

int main() {
    std::cout << "Task 3\n" << std::endl;
    
    Expression* num = new Number(42.5);
    std::cout << "Number: " << num->evaluate() << std::endl;
    delete num;
    
    Expression* subexpr = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '+', subexpr);
    std::cout << "3 + 4.5 * 5 = " << expr->evaluate() << std::endl;
    delete expr;
    
    try {
        Expression* divZero = new BinaryOperation(new Number(10), '/', new Number(0));
        divZero->evaluate();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\nTask 4\n" << std::endl;
    
    Expression* num1 = new Number(10);
    Expression* num2 = new Number(20);
    Expression* binop1 = new BinaryOperation(new Number(1), '+', new Number(2));
    Expression* binop2 = new BinaryOperation(new Number(3), '*', new Number(4));
    
    std::cout << "num1 == num2: " << check_equals(num1, num2) << std::endl;
    std::cout << "binop1 == binop2: " << check_equals(binop1, binop2) << std::endl;
    std::cout << "num1 == binop1: " << check_equals(num1, binop1) << std::endl;
    std::cout << "nullptr == nullptr: " << check_equals(nullptr, nullptr) << std::endl;
    
    delete num1;
    delete num2;
    delete binop1;
    delete binop2;
    
    return 0;
}