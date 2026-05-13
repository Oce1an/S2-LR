#ifndef BST_H
#define BST_H

#include <QString>
#include <QList>
#include <functional>

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    // Основные операции
    bool add(int key);
    bool remove(int key);
    BSTNode* find(int key) const;
    void traverse(std::function<void(BSTNode*)> visit) const;

    // Вставка/удаление поддерева
    bool insertSubtree(BSTNode* subtree);
    BSTNode* removeSubtree(int key);      // возвращает корень удалённого поддерева

    // Вставка/удаление ветви (левой или правой)
    bool insertBranch(int parentKey, int key, bool asLeft);
    BSTNode* removeBranch(int parentKey, bool leftBranch);

    // Вставка в определённую позицию (как левый/правый потомок)
    bool insertAtPosition(int parentKey, int key, bool asLeft);

    // Поиск наименьшего общего предка (LCA)
    int lowestCommonAncestor(int key1, int key2) const;

    // Вспомогательные
    void clear();
    BSTNode* getRoot() const { return root; }

private:
    BSTNode* root;

    void clearTree(BSTNode* node);
    BSTNode* findNode(BSTNode* node, int key) const;
    BSTNode* findMin(BSTNode* node) const;
    void transplant(BSTNode* u, BSTNode* v);
    BSTNode* cloneTree(BSTNode* node, BSTNode* parent);
};

#endif