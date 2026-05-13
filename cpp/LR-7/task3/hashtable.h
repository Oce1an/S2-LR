#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QString>
#include <QVector>

// Узел стека (односвязный список)
struct StackNode {
    int key;
    StackNode *next;
    StackNode(int k) : key(k), next(nullptr) {}
};

// Стек (вставка в начало для простоты)
class Stack {
private:
    StackNode *top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { clear(); }

    void push(int key) {
        StackNode *node = new StackNode(key);
        node->next = top;
        top = node;
    }

    bool pop(int &key) {
        if (isEmpty()) return false;
        StackNode *temp = top;
        key = temp->key;
        top = top->next;
        delete temp;
        return true;
    }

    bool search(int key) const {
        StackNode *cur = top;
        while (cur) {
            if (cur->key == key) return true;
            cur = cur->next;
        }
        return false;
    }

    bool remove(int key) {
        StackNode *cur = top, *prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else top = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    bool isEmpty() const { return top == nullptr; }

    QString toString() const {
        QString res;
        StackNode *cur = top;
        while (cur) {
            res += QString::number(cur->key) + " ";
            cur = cur->next;
        }
        return res.trimmed();
    }

    // Получить минимальный ключ в стеке (если не пуст)
    int minKey() const {
        if (!top) throw std::runtime_error("Empty stack");
        int min = top->key;
        StackNode *cur = top->next;
        while (cur) {
            if (cur->key < min) min = cur->key;
            cur = cur->next;
        }
        return min;
    }

    // Получить все ключи в виде QVector (для обхода)
    QVector<int> keys() const {
        QVector<int> vec;
        StackNode *cur = top;
        while (cur) {
            vec.append(cur->key);
            cur = cur->next;
        }
        return vec;
    }

    void clear() {
        while (top) {
            StackNode *temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// Родительский класс хеш-таблицы (массив стеков)
class HashTable {
protected:
    int tableSize;
    Stack *table;   // динамический массив стеков

    int hashFunction(int key) const {
        return abs(key) % tableSize; // простая хеш-функция
    }

public:
    HashTable(int size = 10) : tableSize(size) {
        table = new Stack[tableSize];
    }

    virtual ~HashTable() {
        delete[] table;
    }

    void insert(int key) {
        int idx = hashFunction(key);
        if (!table[idx].search(key)) // проверка на дубликат (опционально)
            table[idx].push(key);
    }

    bool search(int key) const {
        int idx = hashFunction(key);
        return table[idx].search(key);
    }

    bool remove(int key) {
        int idx = hashFunction(key);
        return table[idx].remove(key);
    }

    // Печать в виде строки: "0: 12 5\n1: \n2: 7 ..."
    QString print() const {
        QString result;
        for (int i = 0; i < tableSize; ++i) {
            result += QString::number(i) + ": ";
            if (!table[i].isEmpty())
                result += table[i].toString();
            result += "\n";
        }
        return result;
    }

    int getSize() const { return tableSize; }
};

// Производный класс с методом решения варианта
class ExtendedHashTable : public HashTable {
public:
    ExtendedHashTable(int size = 10) : HashTable(size) {}

    // Найти номер стека (индекс), содержащего минимальный ключ во всей таблице
    int findStackWithMinKey() const {
        int minKey = 0;
        int minStackIndex = -1;
        bool found = false;

        for (int i = 0; i < tableSize; ++i) {
            if (!table[i].isEmpty()) {
                int stackMin = table[i].minKey();
                if (!found || stackMin < minKey) {
                    minKey = stackMin;
                    minStackIndex = i;
                    found = true;
                }
            }
        }
        return minStackIndex; // если таблица пуста, вернёт -1
    }
};

#endif // HASHTABLE_H