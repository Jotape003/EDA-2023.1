#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
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

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.

bool BST::add(int k) {
    if (root == nullptr){
        Node *node = new Node(k, nullptr, nullptr);
        root = node;
        return true;
    }

    else {
        Node *prevAux = nullptr;
        Node *aux = root;
        while (aux != nullptr){
            if (aux->key == k)
                return false;

            else if (aux->key < k){
                prevAux= aux;
                aux = aux->right;
            }

            else {
                prevAux = aux;
                aux = aux->left;
            }    
        }

        Node *node = new Node (k, nullptr, nullptr);
        
        if (k < prevAux->key){
            prevAux->left = node;
            return true;
        }

        else if (k > prevAux->key){
            prevAux->right = node;
            return true;   
        }

        else {
            return false;
        }
    }
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    if (root == nullptr){
        if (root->key != k){
            return nullptr;
        }
        else {
            return root;
        }
    }

    else {
        Node *aux = root;
        while (aux != nullptr){
            if (aux->key == k){
                return aux;
            }
            else if (aux->key < k) {
                aux = aux->right;
            }
            else {
                aux = aux->left;
            }
        }
        return nullptr;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    Node* aux = root;

    while (aux != nullptr && aux->left != nullptr) {
        aux = aux->left;
    }

    if (aux == nullptr) {
        return INT_MAX;
    }
    
    else {
        return aux->key;
    }
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node) {
    if (node->left == nullptr){
        return node;
    }

    else {
        Node* aux = root;

        while (aux != nullptr && aux->left != nullptr) {
            aux = aux->left;
        }
        
        if (aux != nullptr){
            return aux;
        }
    }
    return nullptr;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    if (root == nullptr) {
        return INT_MAX;
    }
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    if (node->right == nullptr){
        return node;
    }

    else {
        Node* aux = root;

        while (aux != nullptr && aux->right != nullptr) {
            aux = aux->right;
        }
        
        if (aux != nullptr){
            return aux;
        }
    }
    return nullptr;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    Node *test = search(k);
    if(test != nullptr){
        Node*suc = successor(test);
        if(suc != nullptr){
            return suc->key;
        }
    }
    
    return INT_MAX;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    if (node->right != nullptr){
        return minimum(node->right);
    }
    else {
        Node* aux = root;
        Node* suc = nullptr;
        
        while(aux != node){
            if(aux->key < node->key){
                aux = aux->right;
            }
            else {
                suc = aux;
                aux = aux->left;
            }
        }
        
        return suc;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    Node *test = search(k);
    if(test != nullptr){
        Node* suc = predecessor(test);
        if(suc != nullptr){
            return suc->key;
        }
    }
    
    return INT_MIN;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node) {
    if (node->left != nullptr){
        return maximum(node->left);
    }
    else {
        Node* aux = root;
        Node* suc = nullptr;
        
        while(aux != node){
            if(aux->key < node->key){
                aux = aux->left;
            }
            else {
                suc = aux;
                aux = aux->right;
            }
        }
        
        return suc;
    }
}

#endif 