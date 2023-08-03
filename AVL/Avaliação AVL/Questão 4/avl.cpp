
#include <iostream>
#include "node.h"
#include "avl.h"
#include <stack>
#include <vector>
using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
void avl_tree::add(int key) {
    root = add(root, key);
}

// função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    if(p == nullptr)
        return new Node(key);
    if(key == p->key) 
        return p;
    if(key < p->key)
        p->left = add(p->left, key);
    else 
        p->right = add(p->right, key);
    
    p = fixup_node(p, key);

    return p;
}

//função pública que recebe o ponteiro para as raízes das árvores
void avl_tree::enchePilha(avl_tree* t, avl_tree* t2, avl_tree* t3){
    enchePilha(t->root, t2->root, t3->root);
}

//função privada recursiva que chama a função inorder que irá rodar n vezes para raiz 1 e m vezes para raiz 2
//dessa forma o código irá rodar m+n vezes, logo sua complexidade será de O(m+n);
void avl_tree::enchePilha(Node *root, Node *root2, Node* &raizArvore){
    stack<Node*> pilha1,pilha2;

    inorder(root, pilha1);
    inorder(root2, pilha2);

    raizArvore = mergePilha(pilha1,pilha2);
}



void avl_tree::inorder(Node *root, stack<Node*> &pilha){
    if (!root){
        return;
    }
    else {
        inorder(root->left, pilha);
        pilha.push(root);
        inorder(root->right, pilha);
    }
}

//Função mergePilha que tem complexidade O(p), onde p é o número de nós da nova árvore, sendo p portanto o número de nós da árvore 1 + árvore 2,
//logo mergePilha tem complexidade O(m+n), isto porque cada nó é visitado no máximo uma vez.
Node* avl_tree::mergePilha(stack<Node*> &pilha1, stack<Node*> &pilha2){
    avl_tree *tree = new avl_tree;
    vector<Node*> auxV;
    vector<Node*> auxV2;
    while(!pilha1.empty() && !pilha2.empty()){
        if(pilha1.empty()){
            auxV.push_back(pilha2.top());
            pilha2.pop();
        }
        else if(pilha2.empty()){
            auxV.push_back(pilha1.top());
            pilha1.pop();
        }
        else{
            if (pilha1.top()->key > pilha2.top()->key){
                auxV.push_back(pilha1.top());
                pilha1.pop();
            }
            else {
                auxV.push_back(pilha2.top());
                pilha2.pop();
            }
        }
    }

    tree->root = construirarvore(tree->root, auxV, 0, auxV.size()-1);
    return tree->root;
}

//Função com grau de complexidade O(p), sendo p o número de nós da nova árvore, que é a soma dos nós de t1 + t2, logo construirarvore tem grau de O(m+n).
Node* avl_tree::construirarvore(Node* t, vector<Node*> auxV, int p, int q){
    if (p > q) return nullptr;

        t = new Node(auxV[(p+q)/2]->key);
        t->left = construirarvore(t->left, auxV, (((p+q)/2)+1), q);
        t->right = construirarvore(t->right, auxV, p, (((p+q)/2)-1));
        t = fixup_node(t, (p+q)/2);
    
        return t;
}

Node* avl_tree::fixup_node(Node *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key > p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key > p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}