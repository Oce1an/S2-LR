#include <stdexcept>

// Базовый абстрактный класс
class Expression {
public:
    // Виртуальный деструктор для корректного удаления производных классов
    virtual ~Expression() = default;

    // Чисто виртуальный метод для вычисления значения выражения
    virtual double evaluate() const = 0;
};

// Класс для представления чисел
class Number : public Expression {
private:
    double value;

public:
    // Конструктор
    explicit Number(double val) : value(val) {}

    // Реализация метода evaluate
    double evaluate() const override {
        return value;
    }

    // Деструктор не нужен - компилятор сгенерирует правильный
};

// Класс для представления бинарных операций
class BinaryOperation : public Expression {
private:
    Expression* left;   // Левый операнд
    Expression* right;  // Правый операнд
    char operation;     // Тип операции: '+', '-', '*', '/'

public:
    // Конструктор
    BinaryOperation(Expression* l, char op, Expression* r)
        : left(l), right(r), operation(op) {
    }

    // Деструктор - освобождаем оба операнда
    ~BinaryOperation() {
        delete left;
        delete right;
    }

    // Реализация метода evaluate
    double evaluate() const override {
        double leftVal = left->evaluate();
        double rightVal = right->evaluate();

        switch (operation) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal == 0) {
                throw std::runtime_error("Division by zero");
            }
            return leftVal / rightVal;
        default:
            throw std::runtime_error("Unknown operation");
        }
    }
};