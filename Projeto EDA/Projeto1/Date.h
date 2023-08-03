#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

class Date {
    private:
        // Atributos
        int year; // Ano de Nascimento;
        int month; // Mês de Nascimento;
        int day; // Dia de Nascimento;
    
    public:
        // Construtor que recebe os atributos como parâmetros;
        Date(int year, int month, int day){
            this->year = year;
            this->month = month;
            this->day = day;
        }

        // Construtor default;
        Date(){
            this->year = 2023;
            this->month = 1;
            this->day = 1;
        }

        // Construtor que recebe uma data no formato de string e distribui aos atributos no tipo int
        // Recebendo datas com intervalos de '/' e '.' como 2/2/2000 e 2.2.2000;
        Date(std::string str){
            std::stringstream ss(str);
            std::stringstream ss2(str);
            std::string date;
            std::string date1;
            std::vector<std::string> aux;
            std::vector<std::string> aux1;

            while (getline(ss, date, ('/'))){
                aux.push_back(date);
            }

            while (getline(ss2, date1, '.')){
                aux1.push_back(date1);
            }

            if (aux[0].size() <= 2) {
                this->month = std::stoi(aux[0]);
                this->day = std::stoi(aux[1]);
                this->year = std::stoi(aux[2]);
            }
            else {
                this->month = std::stoi(aux1[0]);
                this->day = std::stoi(aux1[1]);
                this->year = std::stoi(aux1[2]);
            }
        }
        
        // Sobrecarga dos operadores >, <, >=, <=, == e != seguindo a seguinte lógica:
        // Data1 > Data2 se a idade de Date1 for maior que Data2;
        // Por exemplo: 1/9/1952 > 1/9/2000;
        bool operator >(const Date& a) {
            if (this->year < a.year) return true;
            else if (this->year == a.year && this->month < a.month) return true;
            else if (this->year == a.year && this->month == a.month && this->day < a.day) return true;
            else return false;
        }

        bool operator <(const Date& a) {
            if (this->year > a.year) return true;
            else if (this->year == a.year && this->month > a.month) return true;
            else if (this->year == a.year && this->month == a.month && this->day > a.day) return true;
            else return false;
        }

        bool operator >=(const Date& a) {
            if (this->year <= a.year) return true;
            else if (this->year == a.year && this->month <= a.month) return true;
            else if (this->year == a.year && this->month == a.month && this->day <= a.day) return true;
            else return false;
        }

        bool operator <=(const Date& a) {
            if (this->year >= a.year) return true;
            else if (this->year == a.year && this->month >= a.month) return true;
            else if (this->year == a.year && this->month == a.month && this->day >= a.day) return true;
            else return false;
        }

        bool operator == (const Date& a) {
            return ((this->year == a.year) && (this->month == a.month) && (this->day == a.day));
        }

        bool operator != (const Date& a){
            if(this->year != a.year || this->month != a.month || this->day != a.day) return true;
            return false;
        }

        // Gets e Sets;
        int getYear() const { return this->year; }
        int getMonth() const { return this->month; }
        int getDay() const { return this->day; }
        void setYear(int year) { this->year = year;}
        void setMonth(int month) { this->month = month;}
        void setDay(int day) { this->day = day;}

        // Sobrecarga do operador << para print de Datas no formato MM/DD/YYYY;
        friend std::ostream& operator <<(std::ostream& os, const Date&a) {
            std::cout << std::setfill('0') << std::setw(2) << a.getMonth() << "/" 
            << std::setfill('0') << std::setw(2) << a.getDay() << "/" 
            << std::setfill('0') << std::setw(4) << a.getYear(); 
            return os;
        }

        // Sobrecarga do operador >> para inserção de Datas no tipo string passando para o construtor Date(string);
        friend std::istream& operator >> (std::istream& is, Date& a) {
            std::string str;
            std::getline(is, str);
            a = Date(str);
            return is;
        }

        // Função que retorna true se this data está entre d1 e d2;
        bool isBetween(Date d1, Date d2) {
            return (*this >= d1 && *this <= d2);
        }

        

        
};

#endif