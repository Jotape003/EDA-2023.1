#include <iostream>
#include <fstream>
#include <sstream>
#include "Avl.h"
#include <vector>
#include "Date.h"
using namespace std;

int main() {
    vector<Pessoa*> aux;
    ifstream file;

    // leitura do arquivo data.csv;
    file.open("data.csv");
    string line;

    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    string linef;
    getline(file, linef);

    while (getline(file, line)) {
        
        int i=0;
        Pessoa *p = new Pessoa();
        stringstream ss(line);
        for (i; line[i] != ','; i++) {
            char c = line[i];
            p->cpf += c;
        }
        i += 1;

        for (i; line[i] != ','; i++) {
            char c = line[i];
            p->nome += c;
        }
        i += 1;

        
        for (i; line[i] != ','; i++) {
            char c = line[i];
            p->sobrenome += c;
        }
        i += 1;

        string data_str = "";
        for (i; line[i] != ','; i++) {
            char c = line[i];
            data_str += c;
        }
        i += 1;
        p->data = Date(data_str);

        for (i; i < line.size(); i++) {
            char c = line[i];
            p->cidade += c;
        }
        aux.push_back(p);
    }
    
    file.close();
    if (file.bad()) {
        cout << "Erro ao fechar o arquivo" << endl;
        return 1;
    }

    avl_tree<string> cpf;
    avl_tree<string> nome;
    avl_tree<string> snome;
    avl_tree<Date> data;
    avl_tree<string> cidade;

    // add todos os dados para as respectivas árvores;
    for(int i=0; i<aux.size(); i++){
        cpf.add(aux[i]->cpf, aux[i]);
        nome.add(aux[i]->nome, aux[i]);
        snome.add(aux[i]->sobrenome, aux[i]);
        data.add(aux[i]->data, aux[i]);
        cidade.add(aux[i]->cidade, aux[i]);
    }

    // início da interface;
    string option;
    string k;
    bool sair = false;
    bool aux1 = false;
    bool aux2 = false;
    bool aux3 = false;
    bool aux4 = false;
    bool aux5 = false;
    bool aux6 = false;
    bool Vdata = false;
    bool Vdata2 = false;
    int i;
    cout << "╭─────────────────────────────────────────────────╮" << endl;
    cout << "├─────────> Ola Usuario,seja Bem-Vindo! <─────────┤" << endl;
    cout << "╰─────────────────────────────────────────────────╯" << endl;
    cout << endl;

    while (!sair){
        cout << endl;
        cout << "╭────────────────> MENU PRINCIPAL <───────────────╮" << endl;
        cout << "├ ┄ Aqui está a lista de opções deste programa: ┄ ┤" << endl;
        cout << "├─> 1- Print de determinada árvore.               │" << endl;
        cout << "├─> 2- Consulta por prefixo.                      │" << endl;
        cout << "├─> 3- Consulta por intervalo de Data.            │" << endl;
        cout << "├─> 4- Consulta por CPF.                          │" << endl;
        cout << "├─> 5- Sair                                       │" << endl;
        cout << "╰─────────────────────────────────────────────────╯" << endl;
        cout << endl;
        cout << "  Digite um número: ";
        cin >> i;
        cin.ignore();

        switch (i) {
            case 1:
                aux1 = false;
                while(!aux1){
                    system ("clear || cls");
                    string j;
                    cout << "╭─────────────────────────────────────────────────╮" << endl;
                    cout << "│ -----  Qual árvore você quer verificar?:  ----- │" << endl;
                    cout << "├─────────────────────────────────────────────────┤" << endl;
                    cout << "├─> 1- CPF                                        │" << endl;
                    cout << "├─> 2- Nome                                       │" << endl;
                    cout << "├─> 3- Sobrenome                                  │" << endl;
                    cout << "├─> 4- Data                                       │" << endl;
                    cout << "├─> 5- Cidade                                     │" << endl;
                    cout << "╰─────────────────────────────────────────────────╯" << endl;
                    cout << endl;
                    cout << "  Digite um número: ";
                    getline (cin, j);

                    if (j == "1") cpf.bshow(); // chama bshow para cpf;
                    else if (j == "2") nome.bshow(); // chama bshow para nome;
                    else if (j == "3") snome.bshow(); // chama bshow para snome;
                    else if (j == "4") data.bshow(); // chama bshow para data;
                    else if (j == "5") cidade.bshow(); // chama bshow para cidade;
                    else {
                        cout << endl;
                        cout << "  ─> Digite um número válido <─" << endl; // condição para entrada inválida;
                    }

                    char c;
                    cout << endl;
                    cout << " ° Pressione 'M' para retornar ao menu principal" << endl 
                         << " ° Pressione 'E' para consultar por outro prefixo" << endl 
                        << endl
                         << " Digite sua opção: ";
                    cin >> c;
                    if (c == 'm' || c == 'M'){
                        aux4 = true; // encerra o laço e retorna para o menu;
                        break;
                    }
                    else if (c == 'e' || c == 'E'){
                        cin.ignore(); // continua no loop;
                        continue;
                    }
                    else { // condição dada caso c seja diferente de M ou E;
                        cout << "Você quer mesmo sair do programa? " << endl; 
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        cout << "° Pressione qualquer tecla para encerrar programa :(" << endl;
                        cin.ignore();
                        getline(cin, k);
                        if (k == "M"){
                            aux4 = true; // encerra o laço e retorna para o menu;
                            break;
                        }
                        else {
                            aux4 = true;
                            sair = true;
                            cout << "Programa Encerrado" << endl; // Encerramento do programa mesmo com consentimento do usuário;
                            break;
                        }
                    }
                }
                system ("clear || cls"); // chamada de sistema para limpar a tela de programa;
                break;
            
            case 2:   
                aux2 = false;
                while (!aux2){
                    system ("clear || cls");
                    string k;
                    cout << "╭─────────────────────────────────────────────────╮" << endl;
                    cout << "│ -----  Selecione a opção correspondente:  ----- │" << endl;
                    cout << "├─> 1- Consulta por Nome                          │" << endl
                         << "├─> 2- Consulta por Sobrenome                     │" << endl
                         << "╰─────────────────────────────────────────────────╯" << endl
                         << endl << "Digite um número: ";
                    
                    getline (cin, k);

                    if (k == "1"){ // consulta por nome;
                        string str;
                        cout << "─> Digite o prefixo desejado: ";
                        getline(cin, str);
                        for (char c = 'a'; c <= 'z'; c++){
                            if (str[0] == c){
                                str[0] = c - 32;
                            }
                        }
                        vector<Pessoa*> aux;
                        nome.searchNameCpf(nome.root, str, aux);
                        if (aux.size() == 0){ // se o tamanho do vector for 0, significa que não existem nomes com tal prefixo;
                            cout << endl;
                            cout << "        ╰───────────────────╮" << endl;
                            cout << "                            V" << endl;
                            cout << "╭────────────────────────────────────────────────────────╮" << endl;
                            cout << "│ Ops, parece que não existe pessoas com este prefixo... │" << endl;
                            cout << "╰────────────────────────────────────────────────────────╯" << endl;
                        }
                        else { // print percorrendo o vector aux e printando todas as pessoas; 
                            cout << endl;
                            cout << "        ╰─────────────────────────╮" << endl;
                            cout << "                                  V" << endl;
                            cout << "╭─────────────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│          Apresentando todas as " << std::setfill('0') << std::setw(3) << aux.size() << " pessoas com o prefixo" << "            │" << endl;
                            cout << "├─────────────────────────────────────────────────────────────────────╯" << endl;
                            
                            for (int i = 0; i < aux.size(); i++){
                                aux[i]->print();
                            }
                            cout << "╰────────────────────────────────────────────────────────────────────" << endl;
                        }

                    }

                    else if (k == "2"){ // semelhante a k == 1, porém com o sobrenome;
                        string str;

                        cout << "─> Digite o prefixo desejado: ";
                        getline(cin, str);
                        for (char c = 'a'; c <= 'z'; c++){
                            if (str[0] == c){
                                str[0] = c - 32;
                            }
                        }
                        vector<Pessoa*> aux;
                        snome.searchNameCpf(snome.root, str, aux);
                        if (aux.size() == 0){
                            cout << endl;
                            cout << "        ╰───────────────────╮" << endl;
                            cout << "                            V" << endl;
                            cout << "╭────────────────────────────────────────────────────────╮" << endl;
                            cout << "│ Ops, parece que não existe pessoas com este prefixo... │" << endl;
                            cout << "╰────────────────────────────────────────────────────────╯" << endl;
                        }
                        else {
                            cout << endl;
                            cout << "        ╰─────────────────────────╮" << endl;
                            cout << "                                  V" << endl;
                            cout << "╭─────────────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│          Apresentando todas as " << std::setfill('0') << std::setw(3) << aux.size() << " pessoas com o prefixo" << "            │" << endl;
                            cout << "├─────────────────────────────────────────────────────────────────────╯" << endl;
                            
                            for (int i = 0; i < aux.size(); i++){
                                aux[i]->print();
                            }
                            cout << "╰────────────────────────────────────────────────────────────────────" << endl;
                            
                        }
                    }
                    else {
                        cout << endl;
                        cout << "  ─> Digite um número válido <─" << endl;
                    }

                    char c;
                    cout << "° Pressione 'M' para retornar ao menu principal                    " << endl 
                         << "° Pressione 'E' para consultar por outro prefixo                      " << endl 
                         << endl
                         << "Digite sua opção: ";
                    cin >> c;
                    if (c == 'm' || c == 'M'){
                        aux4 = true;
                        break;
                    }
                    else if (c == 'e' || c == 'E'){
                        cin.ignore();
                        continue;
                    }
                    else {
                        cout << "Você quer mesmo sair do programa? " << endl;
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        cout << "° Pressione qualquer tecla para encerrar programa :(" << endl;
                        cin.ignore();
                        getline(cin, k);
                        if (k == "M"){
                            aux4 = true;
                            break;
                        }
                        else {
                            aux4 = true;
                            sair = true;
                            cout << "Programa Encerrado" << endl;
                            break;
                        }
                    }
                    
                }
                system ("clear || cls");
                break;

            case 3:
                aux3 = false;
                system ("clear || cls");
                while (!aux3){
                    string str;
                    cout << "╭──────────────────────────────────────────────────╮" << endl;
                    cout << "│ Digite a primeira data (no formato Mes/Dia/Ano): │" << endl;
                    cout << "╰──────────────────────────────────────────────────╯" << endl;
                    cout << " ° ";
                    getline(cin, str);
                    if (str.size() < 8){ // condição de aceitação somente se a string tiver mais de 8 caracteres, aceitando no mínimo m/d/yyyy;
                        cout << "Erro: " << str << " é uma data inválida"<< endl;
                        continue; // retorna para o início do while;
                    }
                    string str2;
                    cout << "╭──────────────────────────────────────────────────╮" << endl;
                    cout << "│ Digite a segunda data (no formato Mes/Dia/Ano):  │" << endl;
                    cout << "╰──────────────────────────────────────────────────╯" << endl;
                    cout << " ° ";
                    getline(cin, str2);
                    while (str2.size() < 8){ // semelhante condição, porém não saindo do while enquanto a condição não for escrita;
                        cout << "Erro: " << str2 << " é uma data inválida"<< endl;
                        cout << "╭──────────────────────────────────────────────────╮" << endl;
                        cout << "│ Digite a segunda data (no formato Mes/Dia/Ano):  │" << endl;
                        cout << "╰──────────────────────────────────────────────────╯" << endl;
                        cout << " ° ";
                        getline (cin, str2);
                    }
                    vector<Pessoa*> auxV;
                    cout << endl;
                    if (Date(str) < Date(str2)){ // condição para saber se as Datas estão ordenadas na forma correta, do menor para o maior;
                        data.searchDate(data.root, Date(str), Date(str2), auxV);
                        if (auxV.size()==0){ // Se auxV for vazio, não existe pessoas no intervalo;
                            
                            cout << "        ╰───────────────────╮" << endl;
                            cout << "                            V" << endl;
                            cout << "╭────────────────────────────────────────────────────────╮" << endl;
                            cout << "│  Ops, parece que não existe pessoas neste intervalo... │" << endl;
                            cout << "╰────────────────────────────────────────────────────────╯" << endl;
                        }
                        else { // print das pessoas dentro de auxV
                            
                            cout << "        ╰─────────────────────────╮" << endl;
                            cout << "                                  V" << endl;
                            cout << "╭───────────────────────────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│          Apresentando todas as " << std::setfill('0') << std::setw(3) << auxV.size() << " pessoas entre " << Date(str) << " e " << Date(str2)  << "          │" << endl;
                            cout << "├───────────────────────────────────────────────────────────────────────────────────╯" << endl;
                            
                            for (int i = 0; i < auxV.size(); i++){
                                auxV[i]->print();
                            }
                            cout << "╰─────────────────────────────────────────────────────────────────────" << endl;
                        }
                    }
                    else if (Date(str) > Date (str2)){ // condição para saber se as Datas estão ordenadas na forma correta, do menor para o maior;
                        data.searchDate(data.root, Date(str2), Date(str), auxV);
                        if (auxV.size()==0){
                            cout << "        ╰───────────────────╮" << endl;
                            cout << "                            V" << endl;
                            cout << "╭────────────────────────────────────────────────────────╮" << endl;
                            cout << "│  Ops, parece que não existe pessoas neste intervalo... │" << endl;
                            cout << "╰────────────────────────────────────────────────────────╯" << endl;
                        }
                        else {
                            cout << "        ╰─────────────────────────╮" << endl;
                            cout << "                                  V" << endl;
                            cout << "╭───────────────────────────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│          Apresentando todas as " << std::setfill('0') << std::setw(3) << auxV.size() << " pessoas entre " << Date(str2) << " e " << Date(str)  << "          │" << endl;
                            cout << "├───────────────────────────────────────────────────────────────────────────────────╯" << endl;
                            
                            for (int i = 0; i < auxV.size(); i++){
                                auxV[i]->print();
                            }
                            cout << "╰─────────────────────────────────────────────────────────────────────" << endl;
                        }
                    }

                    char c;
                    cout << "° Pressione 'M' para retornar ao menu principal                    " << endl 
                         << "° Pressione 'E' para consultar por outro intervalo                      " << endl 
                         << endl
                         << "Digite sua opção: ";
                    cin >> c;
                    if (c == 'm' || c == 'M'){
                        aux4 = true;
                        break;
                    }
                    else if (c == 'e' || c == 'E'){
                        cin.ignore();
                        system("clear || cls");
                        continue;
                    }
                    else {
                        cout << "Você quer mesmo sair do programa? " << endl;
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        cout << "Pressione qualquer tecla para encerrar programa :(" << endl;
                        cin.ignore();
                        getline(cin, k);
                        if (k == "M"){
                            aux3 = true;
                            break;
                        }
                        else {
                            aux3 = true;
                            sair = true;
                            cout << "Programa Encerrado" << endl;
                        }
                    }
                }
                system ("clear || cls");
                break;

            case 4:
                aux4 = false;
                system ("clear || cls");
                while(!aux4){
                    string str;
                    cout << "╭────────────────────────────────────────────────────────╮" << endl;
                    cout << "│  Digite o CPF desejado no formatao 'XXX.XXX.XXX-XX' :  │" << endl;
                    cout << "╰────────────────────────────────────────────────────────╯" << endl;
                    cout << " ° ";
                    getline(cin, str);

                    if (str.size() < 14){ // condição de aceitação somente se a string tiver mais de 14 caracteres;
                        cout << "Erro: " << str << " é um cpf inválido"<< endl;
                        continue; // retorna para o início do while;
                    }

                    vector<Pessoa*> vec;
                    cpf.searchNameCpf(cpf.root, str, vec);
                    if (vec.size() == 1){ // vec tem apenas um elemento, com size igual a 1;
                        cout << endl;
                            cout << "        ╰─────────────────────────╮" << endl;
                            cout << "                                  V" << endl;
                            cout << "╭─────────────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│          Apresentando a pessoa com o CPF: " << str << "            │" << endl;
                            cout << "├─────────────────────────────────────────────────────────────────────╯" << endl;
                            
                            vec[0]->print(); // print do único elemento de vec
                            cout << "╰─────────────────────────────────────────────────────────────────────" << endl;
                    }
                    else { // vec é vazio;
                        cout << endl;
                            cout << "        ╰───────────────────╮" << endl;
                            cout << "                            V" << endl;
                            cout << "╭───────────────────────────────────────────────────────────────╮" << endl;
                            cout << "│   Ops, parece que não existe nenhuma pessoa com este CPF...   │" << endl;
                            cout << "╰───────────────────────────────────────────────────────────────╯" << endl;
                    }

                    char c;
                    cout << "° Pressione 'M' para retornar ao menu principal                    " << endl 
                         << "° Pressione 'E' para consultar por outro CPF                      " << endl 
                         << endl
                         << "Digite sua opção: ";
                    cin >> c;
                    if (c == 'm' || c == 'M'){
                        aux4 = true;
                        break;
                    }
                    else if (c == 'e' || c == 'E'){
                        cin.ignore();
                        system ("clear || cls");
                        continue;
                    }
                    else {
                        cout << "Você quer mesmo sair do programa? " << endl;
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        cout << "Pressione qualquer tecla para encerrar programa :(" << endl;
                        cin.ignore();
                        getline(cin, k);
                        if (k == "M"){
                            aux4 = true;
                            break;
                        }
                        else {
                            aux4 = true;
                            sair = true;
                            cout << "Programa Encerrado" << endl;
                        }
                    }
                }
                system ("clear || cls");
                break;

            case 5:
                system ("clear || cls");

                // clear de todas as árvores;
                cout << "╭────────────────────────────────────────────────────────╮" << endl;
                cout << "├────────── Dando clear em todas as árvores... ──────────┤" << endl;
                cout << "╰────────────────────────────────────────────────────────╯" << endl;
                cpf.~avl_tree();
                nome.~avl_tree();
                snome.~avl_tree();
                data.~avl_tree();
                cidade.~avl_tree();

                
                    cout << "            ╰────────────╮" << endl;
                    cout << "                         V" << endl;
                    cout << "╭─────────────────────────────────────────────────╮" << endl;
                    cout << "│ -----  Selecione a opção correspondente:  ----- │" << endl;
                    cout << "├─> 1- Verificar árvores e sair do programa       │" << endl
                         << "├─> 2- Sair do programa                           │" << endl
                         << "╰─────────────────────────────────────────────────╯" << endl
                         << endl << "  Digite um número: ";
                    
                    getline (cin, option);

                if (option == "1"){ // print de todas as árvores nulas;
                    cout << endl;
                    cout << "╭──────────────────────────────────────────────────" << endl;
                    cout << "├─> Árvore CPF: # == nullptr" << endl;
                    cout << "├─> ° ";
                    cpf.bshow();
                    cout << "├─> Árvore Nome: # == nullptr" << endl;
                    cout << "├─> ° ";
                    nome.bshow();
                    cout << "├─> Árvore Snome: # == nullptr" << endl;
                    cout << "├─> ° ";
                    snome.bshow();
                    cout << "├─> Árvore Data: # == nullptr" << endl;
                    cout << "├─> ° ";
                    data.bshow();
                    cout << "├─> Árvore Cidade: # == nullptr" << endl;  
                    cout << "├─> ° ";
                    cidade.bshow();
                    cout << "╰──────────────────────────────────────────────────";
                    cout << endl;
                    sair = true;
                }
                else if (option == "2"){
                    sair = true;
                }
                else {
                        cout << "Você quer mesmo sair do programa? " << endl;
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        cout << "Pressione qualquer tecla para encerrar programa :(" << endl;
                        getline(cin, k);
                        if (k == "M"){
                            aux4 = true;
                            break;
                        }
                        else {
                        aux3 = true;
                        sair = true;
                        cout << "Programa Encerrado" << endl;
                        }
                }
                break;

                default: 
                    aux6 = false;
                    while (!aux6){
                        string def;
                        cout << "  ─> OPÇÃO INVÁLIDA <─" << endl;
                        cout << "° Pressione 'M' para retornar ao menu principal                    " << endl;
                        getline (cin, def);
                        // cout << option << endl;
                        if (def == "M" || def == "m") {
                            aux6 = true;
                            
                        }
                    }
                    system ("clear || cls");
                    break;

        }
    }
}