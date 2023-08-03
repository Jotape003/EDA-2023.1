#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include "Pessoa.h"

template <typename T>
struct Node {
    // atributos para Node
    T key; // chave;
    int height; // altura;
    Node<T> *left; // ponteiro para a esquerda;
    Node<T> *right; // ponteiro para a direita;
    Pessoa *pes; // ponteiro para Pessoa; 
    
    // Construtor que passa apenas key e pes como parâmetros, sendo os outros iniciados por default;
    Node (const T& key, Pessoa *pes){
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
        this->pes = pes;
    }
        
};

#endif