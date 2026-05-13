#ifndef DEQUE_H
#define DEQUE_H

// Узел двухсвязного списка
struct DNode {
    int data;
    DNode *next;
    DNode *prev;
    DNode(int d) : data(d), next(nullptr), prev(nullptr) {}
};

// Двухсвязная очередь (дек) с методами очереди (FIFO)
class Deque {
private:
    DNode *head;
    DNode *tail;
    int count;

public:
    Deque();
    ~Deque();

    void push_back(int value);   // добавление в конец
    int pop_front();             // удаление из начала
    int front() const;           // первый элемент
    int back() const;            // последний элемент
    bool isEmpty() const;
    int size() const;
    void clear();

    // Вспомогательные методы для задания
    void fromRandom(int n, int minVal = 0, int maxVal = 100);
    int* toArray(int &outSize) const; // возвращает массив (владелец удаляет)

    // Методы для поиска мин/макс (возвращают значения или узлы)
    int findMin() const;
    int findMax() const;

    // Получение указателей на голову и хвост (для внешнего использования при разделении)
    DNode* getHead() const { return head; }
    DNode* getTail() const { return tail; }
};

#endif