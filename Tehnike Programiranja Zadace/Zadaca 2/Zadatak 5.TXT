//TP 2022/2023: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <deque>
#include <list>
#include <new>
template <typename T1, typename T2>
auto KreirajTablicuSabiranja(T1 start1, T1 end1, T2 start2) -> std::remove_reference_t<decltype(*start1 + *start2)> **{
    using T = std::remove_reference_t<decltype(*start1 + *start2)>;
    T **p = nullptr;
    int brojEl = 0, broj_pok = 0;
    for(auto p = start1; p != end1; p++){ 
        brojEl += broj_pok + 1;
        broj_pok++;
    }
    try{
        p = new T *[broj_pok];
        try{
            p[0] = new T[brojEl]{};
            for(int i = 1; i < broj_pok; i++){
                p[i] = i + p[i - 1];
            }
            auto q = start1;
            for(int i = 0; i < broj_pok; i++){
                auto r = start2;
                for(int j = 0; j <= i; j++){
                    if(*start1 + *r != *r + *start1)  throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
                        p[i][j] = *start1 + *r;
                        r++;
                }
                start1++;
            }

        }
        catch(std::logic_error e){
            delete[] p[0];
            delete[] p;
            throw;
    }catch(std::bad_alloc e){
        delete[] p[0];
        delete[] p;
        throw;
        }
    }catch(std::bad_alloc e){
        std::cout<<"Problemi sa memorijom!\n";
    }
  return p;
}

int main (){
    std::cout<<"Duzina sekvenci: "<<std::endl;
    int duzina = 0;
    std::cin>>duzina;
    std::vector<int> sek1(duzina, 0);
    std::deque<int> sek2(duzina, 0);

    std::cout<<"Elementi prve sekvence: ";
    for(int i = 0; i < duzina; i++){
        std::cin>>sek1.at(i);
    }
    std::cout<<"Elementi druge sekvence: ";
    for(int i = 0; i < duzina; i++){
        std::cin>>sek2.at(i);
    }
    try{
        auto p = KreirajTablicuSabiranja(sek1.begin(), sek1.end(), sek2.begin());
        std::cout<<"Tablica sabiranja: "<<std::endl;
        for(int i = 0; i <duzina; i++){
            for(int j = 0; j <= i; j++){
                std::cout<<p[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        delete[] p[0];
        delete[] p;
    }catch(...){
        std::cout<<"Izuzetak...";
    }
	return 0;
}
