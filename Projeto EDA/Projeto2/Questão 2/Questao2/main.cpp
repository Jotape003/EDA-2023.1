#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;


int main(){
    fstream arq;
    arq.open("test.txt");
    vector<int> Bacon;
    unordered_map<string, vector<pair<string, string>>> hash;
    string linha;
    for(int i = 0; getline(arq,linha);i++){
        string nome;
        string filme;
        string vizinho;

        nome = linha.substr(0,linha.find(";"));
        linha.erase(0,linha.find(";")+1);

        filme = linha.substr(0,linha.find(";"));
        linha.erase(0,linha.find(";")+1);

        vizinho = linha;
        
        if (hash.count(nome) == 0){
            //VNome.push_back(nome);
            hash[nome].emplace_back(make_pair(filme, vizinho));
            // VFilme.push_back(filme);
            //VVizinho.push_back(vizinho);
            if (hash.count(vizinho) == 0){
                if (vizinho == "Kevin Bacon"){
                   hash[vizinho].emplace_back(make_pair("", ""));
                    //VNome.push_back(vizinho);
                    //VFilme.push_back("");
                    //VVizinho.push_back("");
                }
            }
        } 
        
        
    }

    // for (auto &i : hash)
    // {
    //     cout << i.first;
    //     for (auto &k : i.second)
    //     {
    //         cout << " -> " << k.first << "," << k.second;
    //     }
    //     cout << endl;
    // }

    // for (int i = 0; i < pai.size(); i++){
    //     cout << pai[i] << endl;
    // }
    // vector<int> grafo;

    // grafo.resize(VNome.size());

    // for(int i = 0; i < grafo.size(); i++){
    //     string aux = VVizinho[i];
    //     if(VNome[i] == "Kevin Bacon"){
    //         grafo[i] = -1;
    //     }else{
    //         for(int k = 0; k < grafo.size();k++){
    //             string equal = VNome[k];
    //             if(equal == aux){
    //                 grafo[i] = k;
    //             }
    //         }
    //     }
    // }

    // Bacon.resize(grafo.size());
    
    // vector<Person> ordena;
    // for(int i = 0; i < VNome.size(); i++){
    //     Person aux(VNome[i],VFilme[i],VVizinho[i],Bacon[i]);
    //     ordena.push_back(aux);
    // }
    
    // sort(ordena.begin(),ordena.end());
    // for(int i = 0; i < ordena.size(); i++){
    //     cout << "O numero de Bacon de " << ordena[i].nome << " e " << ordena[i].bacon << " pelo filme " << ordena[i].filme << endl;
    // }
}