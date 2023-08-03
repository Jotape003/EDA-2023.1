#ifndef AVL_H
#define AVL_H
#include <string>
#include "node.h"
#include <stack>
#include <vector>

class avl_tree {
public:
    avl_tree() = default;
    avl_tree(const avl_tree& t) = delete;
    avl_tree& operator=(const avl_tree& t) = delete;
    void add(int key);
    void bshow() const;
    void clear();
    ~avl_tree();
    void enchePilha (avl_tree* t, avl_tree* t2, avl_tree* t3);
    
private:
    Node *root {nullptr};

    int height(Node *node);
    int balance(Node *node);
    Node* rightRotation(Node *p);
    Node* leftRotation(Node *p);
    Node* add(Node *p, int key);
    Node* fixup_node(Node *p, int key);
    void bshow(Node *node, std::string heranca) const;
    Node* clear(Node *node);
    void enchePilha (Node* root, Node *root2, Node* &encheArvore);
    void inorder(Node *root, std::stack<Node*> &pilha);
    Node *mergePilha(std::stack<Node*> &pilha1, std::stack<Node*> &pilha2);
    Node* construirarvore(Node *t, std::vector<Node*> auxV, int p, int q);
};

#endif