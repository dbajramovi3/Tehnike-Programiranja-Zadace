//TP 2022/2023: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih{IgnorirajZnak, Odbaci, PrijaviGresku};

int MultiplikativniDigitalniKorijen(long long int broj, int baza){
    // Baza manja od 2
    if(baza < 2 ){
        throw std::domain_error("Neispravna baza");
    }
    // Ako je negativan pretvori u pozitivan
    if(broj < 0){
        broj *= -1;
    }
    else if(broj == 0){
        return 0;
    }
    long long int proizvod = 1;
    while(broj != 0){
        proizvod *= broj % baza;
        broj /= baza;
    }
    if(proizvod < baza){
        return proizvod;
    }
    return MultiplikativniDigitalniKorijen(proizvod, baza);
}
std::array<std::vector<long long int>, 10> RazvrstajBrojeve(std::vector<long long int> brojevi, enum TretmanNegativnih tretman){
    std::array<std::vector<long long int>, 10> razvrstani;
    for(long long int broj : brojevi){
        //Sad cemo da implementiramo TretmanNegativnih
        if(broj < 0 && tretman == TretmanNegativnih::PrijaviGresku){
            throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
        }
        if(broj < 0 && tretman == TretmanNegativnih::IgnorirajZnak){
            broj = -broj;
        }
        if(broj < 0 && tretman == TretmanNegativnih::Odbaci){
            continue;
        }
        int korijen = MultiplikativniDigitalniKorijen(broj, 10);
        razvrstani.at(korijen).push_back(broj);
    }
    return razvrstani;
}

int main ()
{
    /*
    Test
    int broj = 760;
    int baza = 7;
    std::cout<<MultiplikativniDigitalniKorijen(broj, baza);
    */
    std::vector<long long int> v;
    std::cout<<"Unesite brojeve (bilo koji ne-broj oznacava kraj): "<<std::endl;
    long long int unesi;
    while(std::cin>>unesi){
        if(unesi < 0){
            std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!";
            return 0;
        }
        v.push_back(unesi);
    }
    
    std::array<std::vector<long long int>, 10> razvrstani;

    try{
        razvrstani = RazvrstajBrojeve(v, TretmanNegativnih::PrijaviGresku);
    }catch(const std::domain_error e){
        std::cout<<e.what()<<std::endl;
        return 1;
    }
    //ispis
    std::cout<<"Rezultati razvrstavanja po multiplikativnom digitalnom korijenu: ";
    for(int korijen = 0; korijen <= 9; korijen++){ 
        bool tacnost = false;
        for(int i = 0; i < razvrstani.at(korijen).size(); i++){
            if(!tacnost){
                std::cout<<korijen<<": ";
                tacnost = true;
            }
            std::cout<<razvrstani.at(korijen).at(i)<<" ";
        }
        if(tacnost){
            std::cout<<std::endl;
        }
    }
	return 0;
}
