#include <iostream>
#include "Avl.h"
#include <vector>
#include <typeinfo>

using namespace std;

// retorna a altura do nó.
// se a arvore for vazia ela tem altura 0
// caso contrario, retorna o valor que está no campo height
template <typename T>
int avl_tree<T>::height(Node<T> *node) {
    return (node == nullptr) ? 0 : node->height;
}

// função que retorna o balanço de um nó;
template <typename T>
int avl_tree<T>::balance(Node<T> *node) {
    return height(node->right) - height(node->left);
}

// implementação da rotação a direita;
template <typename T>
Node<T>* avl_tree<T>::rightRotation(Node<T> *p) {
    Node<T> *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// implementação da rotação a esquerda;
template <typename T>
Node<T>* avl_tree<T>::leftRotation(Node<T> *p) {
    Node<T> *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->right),height(p->left));
    u->height = 1 + max(height(u->left),height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
template <typename T>
void avl_tree<T>::add(T key, Pessoa *p) {
    root = add(root, key, p);
}

// função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se 
// ela nao for repetida. Claro, tem que deixar AVL novamente
template <typename T>
Node<T>* avl_tree<T>::add(Node<T> *p, T k, Pessoa *t) {
    if(p == nullptr){
        return new Node<T>(k, t);
    }
    else if (k < p->key){
        p->left = add(p->left, k, t);
    }

    else if(k >= p->key){
        p->right = add(p->right, k, t);
    }
    p = fixup_node(p, k);

    return p;
}

// função que rebalancea a árvore fazendo rotações se necessário;
template <typename T>
Node<T>* avl_tree<T>::fixup_node(Node<T> *p, T key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left),height(p->right));

    // calcula o balanço do p
    int bal = balance(p);

    if(bal < -1 && key < p->left->key) {
        p = rightRotation(p);
    }
    else if(bal < -1 && key >= p->left->key) {
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else if(bal > 1 && key >= p->right->key) {
        p = leftRotation(p);
    }
    else if(bal > 1 && key < p->right->key) {
        p->right = rightRotation(p->right);
        p = leftRotation(p);
    }
    return p;
}

// função pública que deleta todos os nós da árvore
template <typename T>
void avl_tree<T>::clear() {
    root = clear(root);
}

// função privada que deleta todos os nós da árvore;
template <typename T>
Node<T> *avl_tree<T>::clear(Node<T> *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

// destrutor
template <typename T>
avl_tree<T>::~avl_tree() {
    clear();
}

// função bshow pública para print de uma árvore;
template <typename T>
void avl_tree<T>::bshow() const {
    bshow(root, "");
}

// função bshow privada para print de uma árvore;
template <typename T>
void avl_tree<T>::bshow(Node<T> *node, std::string heranca) const {
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

// função de consulta de pessoas por Nome ou CPF;
template <typename T>
void avl_tree<T>::searchNameCpf(Node<string> *p, string key, vector<Pessoa*> &aux){
    if (p == nullptr) return;

    if (p->key.substr(0, key.size()) == key){
        aux.push_back(p->pes);
        if (p->left != nullptr && maximum(p->left)->key.substr(0, key.size()) == key){
            searchNameCpf(p->left, key, aux);
        }
        if (p->right != nullptr && minimum(p->right)->key.substr(0, key.size()) == key){
            searchNameCpf(p->right, key, aux);
        }
    }
    
    else {
        if (p->key > key){
            searchNameCpf(p->left, key, aux);
        }

        searchNameCpf(p->right, key, aux);
    }
    
}

// função de consulta de pessoas por intervalo de Datas, se existir;
template <typename T>
void avl_tree<T>::searchDate(Node<Date> *p, Date d1, Date d2, vector<Pessoa*> &aux){
    
    if (p == nullptr) return;

    if (p->key.isBetween(d1, d2)){
        aux.push_back(p->pes);
        searchDate(p->left, d1, d2, aux);
        searchDate(p->right, d1, d2, aux);
    }

    else if (p->key > d1) searchDate(p->left, d1, d2, aux);

    else if (p->key < d1 ){
        searchDate(p->right, d1, d2, aux);
    }
}

// função que retorna o menor nó de uma árvore
template <typename T>
Node<string> *avl_tree<T>::minimum(Node<string> *node) {
    if (node->left == nullptr){
        return node;
    }

    else {
        Node<string>* aux = node;

        while (aux != nullptr && aux->left != nullptr) {
            aux = aux->left;
        }
        
        if (aux != nullptr){
            return aux;
        }
    }
    return nullptr;
}

// Funcao privada
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
template <typename T>
Node<string> *avl_tree<T>::maximum(Node<string> *node) {
    if (node->right == nullptr){
        return node;
    }

    else {
        Node<string>* aux = node;

        while (aux != nullptr && aux->right != nullptr) {
            aux = aux->right;
        }
        
        if (aux != nullptr){
            return aux;
        }
    }
    return nullptr;
}

// template class avl_tree<int>;
template class avl_tree<Date>;
template class avl_tree<string>;