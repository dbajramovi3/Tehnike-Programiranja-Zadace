//TP 2022/2023: Zadaća 5, Zadatak 5
#include <iostream>
#include <cmath>
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

using namespace std;

void BaciRangeError(){
    throw std::range_error("Neispravna pozicija");
}

template <typename T> 
class DatotecniKontejner{

    fstream tok;

public:
DatotecniKontejner(const string &ime){
    tok.open(ime, ios::binary | ios::in | ios::out | ios::app);
}

void DodajNoviElement(const T &el){
    auto var = tok.tellp();
    tok.seekp(0, ios::end);
    tok.write(reinterpret_cast<const char*>(&el), sizeof(T));

    tok.seekp(var);
}

int DajBrojElemenata(){
    tok.seekp(0, ios::end);

    auto var2 = tok.tellg() / sizeof(T);
    return var2;
}

T DajElement(int p){
    int v = DajBrojElemenata();
    if(p < 0 || p >= v) BaciRangeError();

    tok.seekp(p * sizeof(T));

    T element;
    tok.read(reinterpret_cast<char*>(&element), sizeof(T));


    return element;
};

void IzmijeniElement(int p, const T &el){
    int vel = DajBrojElemenata();
    if(p < 0 || p >= vel) BaciRangeError();

    fstream tempTok("var.bin", ios::binary | ios::out);

    for(int i = 0; i < vel; i++){
        auto pom = DajElement(i);
        if(i == p){
         pom = el;
        }
        tempTok.write(reinterpret_cast<const char*>(&pom), sizeof(T));
        if(tempTok.fail()){
            tempTok.close();

        }
    }
    tempTok.close();
    tok.close();
    remove("testiranje.bin");
    rename("var.bin", "testiranje.bin");
    tok.open("testiranje.bin", ios::binary | ios::in | ios::out);

}

void Sortiraj(function<bool(const T &, const T &)> kriterij = less<T>()){
    int vel = DajBrojElemenata();
    for(int i = 0; i < vel - 1; i++){
        for(int j = 0; j < vel - 1 - i; j++){
            auto pot = DajElement(j);
            auto pot2 = DajElement(j + 1);
            if(kriterij(pot2, pot)){
                IzmijeniElement(j, pot2);
                IzmijeniElement(j + 1, pot);
            }
        }
    }
}
};
int main ()
{


	return 0;
}
