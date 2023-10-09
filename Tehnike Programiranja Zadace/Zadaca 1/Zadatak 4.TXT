//TP 2022/2023: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

char UVelika(char c){
    if(c >= 'a' && c <= 'z'){
        return c - ('a' - 'A');
    }
    return c;
}

//Provjera da li su velika slova
bool DaLiSuVelika(char c){
    return (c >= 'A' && c <= 'Z');
}

//Funkcija koja provjerava da li je string s sastavljen od alfanumerickih karaktera odnosno slova i brojeva
bool DaLiJeRijec(char c){
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            return true;
        }
    return false;
}

//Prima char i provjerava da li se radi o velikom slovu, ako da, pretvara ga u malo
char UManja(char c){
    if(c >= 'A' && c <= 'Z'){
        return c + ('a' - 'A');
    }
    return c;
}

bool Ispravnost(std::vector<std::string> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0 ; j < v.at(i).size(); j++){
            if(!DaLiJeRijec(v.at(i).at(j))){
                return false;
            }
        }
    }
    return true;
}

std::string Cenzura(std::string recenica, std::vector<std::string> zabranjene){
    if(!Ispravnost(zabranjene)){
        throw std::logic_error("Neispravna riječ");
    }
    for(int i = 0; i < zabranjene.size(); i++){
        std::string zabranjenaRijec = zabranjene.at(i);
        int vrijednost = 0;
        bool slaganje;
        while(vrijednost < recenica.size()){
            slaganje = true;
            if(vrijednost != 0){
                if(DaLiJeRijec(recenica.at(vrijednost-1))){
                    slaganje = false;
                }
            }
            for(int j = 0; j < zabranjenaRijec.size() && (vrijednost + j) < recenica.length(); j++){
                if(UManja(recenica.at(vrijednost + j)) != UManja(zabranjenaRijec.at(j))){
                    slaganje = false;
                    break;
                }
            }
            if(slaganje && ((vrijednost + zabranjenaRijec.length() == recenica.length()) || (!DaLiJeRijec(recenica.at(vrijednost + zabranjenaRijec.length()))))){
                for(int j = 0; j < zabranjenaRijec.length(); j++){
                    recenica.at(vrijednost + j) = '*';
                }
            }
            vrijednost++;
        }
    }
    return recenica;
}
int main (){
    std::string recenica;
    std::cout<<"Unesite recenicu: "<<std::endl;
    getline(std::cin, recenica);
    std::vector<std::string> zabranjene;
    std::cout<<"Unesite zabranjene rijeci (. za kraj): "<<std::endl;
    std::string zab;
    while(std::cin>>zab){
        if(zab == "."){
            break;
        }
        zabranjene.push_back(zab);
    }   
        if(Ispravnost(zabranjene)){
            std::cout<<"Cenzurisana recenica: "<<Cenzura(recenica, zabranjene);
        }else{
        std::cout<<"GRESKA: Nelegalne zabranjene rijeci!";
        }

	return 0;
}
