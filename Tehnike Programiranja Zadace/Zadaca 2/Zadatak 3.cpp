//TP 2022/2023: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <string>

template<typename t1, typename t2, typename t3, typename t4>
auto GeneraliziraniMatricniProizvod(const std::vector<std::vector<t1>> &a, const std::vector<std::vector<t2>> &b, t3 f, t4 g) -> std::vector<std::vector<decltype(g(a.at(0).at(0), b.at(0).at(0)))>>{
/*
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < b.at(0).size(); j++){
                decltype(g(a.at(0).at(0), b.at(0).at(0))) s = g(a.at(i).at(0), b.at(0).at(j));
                for(int k = 1; k < a.at(0).size(); k++){
                    s = f(s, g(a.at(i).at(k), b.at(k).at(j)));
                }
                c.at(i).at(j) = s;
            }
        }
*/
const int red = a.size();
const int red1 = b.size();
int v, v1;
using T = std::vector<decltype(g(t1(), t2()))>;
if(red <= 0){
    v = 0;
}else{
    v = a.at(0).size();
}
if(red1 <= 0){
    v1 = 0;
}else{
    v1 = b.at(0).size();
}

for(int i = 0 ; i < red; i++){
    if(a.at(i).size() != v){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
}
for(int i = 0; i < red1; i++){
    if(b.at(i).size() != v1){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
} 

if(v != red1){
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
}
std::vector<T> c(red, T(v1));
try{
    for(int i = 0; i < red; i++){
        for(int j = 0; j < v1; j++){
            c.at(i).at(j) = g(a.at(i).at(0), b.at(0).at(j));
            for(int l = 1; l < red1; l++){
                c.at(i).at(j) = f(c.at(i).at(j), g(a.at(i).at(l), b.at(l).at(j)));
            }
        }
    }
}
catch(...){
    throw std::runtime_error("Neocekivani problemi pri racunanju");
}

return c;
}
int main (){
int broj_kolona_druge, kolone_prve_red_druge, broj_redova_prve;
std::cout<<"Unesite broj redova prve matrice: ";
std::cin>>broj_redova_prve;
std::cout<<"Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
std::cin>>kolone_prve_red_druge;
std::cout<<"Unesite broj kolona druge matrice: "<<std::endl;
std::cin>>broj_kolona_druge;
std::vector<std::vector<std::string>> A(broj_redova_prve, std::vector<std::string>(kolone_prve_red_druge));
std::vector<std::vector<std::string>> B(kolone_prve_red_druge, std::vector<std::string>(broj_kolona_druge));
std::cout<<"Unesite elemente prve matrice: ";
std::cout<<std::endl;
for(int i = 0; i < A.size(); i++){
    for(int j = 0; j < A.at(i).size(); j++){
        std::cin>>A.at(i).at(j);
    }
}
std::cout<<"Unesite elemente druge matrice: "<<std::endl;
std::cout<<std::endl;

for(int i = 0; i < B.size(); i++){
    for(int j = 0; j < B.at(i).size(); j++){
        std::cin>>B.at(i).at(j);
    }
}

std::cout<<"Matricni proizvod:"<<std::endl;
auto C = GeneraliziraniMatricniProizvod(A, B, []( std::string a,  std::string b) -> std::string{ return a + "+" + b;}, []( std::string a, std::string b) -> std::string { return a + "*" + b;});
for(int i = 0; i < B.size(); i++){
    for(int j = 0; j < B.at(i).size(); j++){
        std::cout<<C.at(i).at(j)<<"  ";
        }
    std::cout<<std::endl;
    }
	return 0;
}
