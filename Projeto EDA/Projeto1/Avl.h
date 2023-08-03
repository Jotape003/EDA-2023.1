#ifndef AVL_H
#define AVL_H
#include <string>
#include "Node.h"
#include <vector>
// #include "Date.h"

template <typename T>
class avl_tree {
public:
    avl_tree() = default; // construtor default;
    void add(T key, Pessoa *p) ; // função pública para add nós na árvore;
    void bshow() const; // função pública para print da árvore;
    void clear(); // função pública para deletar todos os nós da árvore;
    ~avl_tree(); // destrutor
    void searchNameCpf(Node<std::string> *k, std::string key, std::vector<Pessoa*> &aux); // função para consulta por nomes e CPF na árvore
    void searchDate(Node<Date> *k, Date d1, Date d2, std::vector<Pessoa*> &aux); // função para consulta por intervalo de datas;
    Node<std::string> *minimum(Node<std::string> *node); // função que retorna o menor nó de uma árvore;
    Node<std::string> *maximum(Node<std::string> *node); // função que retorna o maior nó de uma árvore;
    
    Node<T> *root {nullptr}; // atributo ponteiro para a raiz da árvore
private:

    int height(Node<T> *node); // função que retorna a altura de um nó;
    int balance(Node<T> *node); // função que retorna o balanceamento de um nó;
    Node<T>* rightRotation(Node<T> *p); // rotação a direita;
    Node<T>* leftRotation(Node<T> *p); // rotação a esquerda;
    Node<T>* add(Node<T> *p, T key, Pessoa* pes); // função add privada;
    Node<T>* fixup_node(Node<T> *p, T key); // função que balancea a árvore;
    void bshow(Node<T> *node, std::string heranca) const; // função bshow privada;
    Node<T>* clear(Node<T> *node); // função clear privada;
};

#endif