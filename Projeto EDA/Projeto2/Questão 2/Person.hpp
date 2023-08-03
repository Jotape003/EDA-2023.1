#ifndef person_hpp
#define person_hpp
#include <string>
#include <iostream>

class Person{
  public:
    std::string nome;
    std::string filme;
    std::string vizinho;
    int bacon = 0;

    Person(std::string n, std::string f, std::string v,int b){
        nome = n;
        filme = f;
        vizinho = v;
        bacon = b;
    }


    bool operator>(const Person& p){
      return nome > p.nome;
    }
    bool operator<(const Person& p){
      return nome < p.nome;
    }
};
#endif