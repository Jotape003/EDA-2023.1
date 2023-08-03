#ifndef PESSOA_H
#define PESSOA_H
#include <iostream>
#include "Date.h"
#include "Avl.h"

class Pessoa : public Date{
    public:
        //Atributos
        std::string nome; // Nome da Pessoa;
        std::string sobrenome; // Sobrenome da Pessoa;
        std::string cidade; // Cidade da Pessoa;
        std::string cpf; // CPF da Pessoa;
        Date data; // Data de Nascimento da Pessoa;

        //Construtor que recebe todos os atributos como parâmetros;
        Pessoa(const std::string cpf, const std::string nome, const std::string sobrenome, Date data, const std::string cidade){
            this->cpf = cpf;
            this->nome = nome;
            this->sobrenome = sobrenome;
            this->data = data;
            this->cidade = cidade;
        }

        // Construtor Default;
        Pessoa() = default;

        // Função Print;
        void print(){
            std::cout << "├─> ° " << cpf << ", " << nome << ", " << sobrenome << ", " 
                      << (std::cout, data)
                      << ", " << cidade << std::endl;
        }
        
};

#endif