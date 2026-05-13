#ifndef BST_H
#define BST_H

#include <QString>
#include <QList>
#include <QTableWidget>
#include <QTreeWidget>

// Узел дерева
struct TreeNode {
    int key;
    QString str;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int k, const QString &s) : key(k), str(s), left(nullptr), right(nullptr) {}
};

// Родительский класс – бинарное дерево поиска
class BST {
public:
    BST();
    virtual ~BST();

    // Основные методы
    void insert(int key, const QString &str);
    void buildFromTable(QTableWidget *table);
    void balance();
    TreeNode* search(int key) const;
    bool remove(int key);
    void clear();

    // Обходы
    QString preorder() const;
    QString inorder() const;
    QString postorder() const;

    // Заполнение QTreeWidget
    void populateTreeWidget(QTreeWidget *treeWidget) const;

protected:
    TreeNode *root;

    // Вспомогательные рекурсивные функции
    void insertNode(TreeNode *&node, int key, const QString &str);
    TreeNode* searchNode(TreeNode *node, int key) const;
    TreeNode* removeNode(TreeNode *node, int key, bool &deleted);
    TreeNode* findMin(TreeNode *node) const;
    void clearTree(TreeNode *node);
    void inorderArray(TreeNode *node, QList<TreeNode*> &list) const;
    TreeNode* buildBalanced(QList<TreeNode*> &list, int start, int end);

    void preorderRec(TreeNode *node, QString &result) const;
    void inorderRec(TreeNode *node, QString &result) const;
    void postorderRec(TreeNode *node, QString &result) const;
    void populateTreeRec(TreeNode *node, QTreeWidgetItem *parent) const;
};

// Производный класс с индивидуальным заданием
class ExtendedBST : public BST {
public:
    ExtendedBST() : BST() {}

    // Подсчитать сумму длин всех строк в узлах
    int totalStringLength() const;
};

#endif // BST_H