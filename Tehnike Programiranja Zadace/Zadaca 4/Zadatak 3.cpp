//TP 2022/2023: Zadaća 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <vector>
#include <list>

void DomainError(){
    throw std::domain_error("Pogresno!");
}

void LogicError(){
    throw std::logic_error("Vrijednost koja nije regularna");
}

void RangeError(){
    throw std::range_error("Greska!");
}


class Polazak{
    std::string odrediste;
    std::string oznaka;
    int broj_perona;
    int sat;
    int minute;
    int trajanje;
    int kasnjenje;

    void provjeravanje(std::string odrediste, std::string oznaka_voznje, int br_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
        if(broj_perona < 1 || broj_perona > 15){
            DomainError();
        }
        else if(sat_polaska < 0 || sat_polaska > 23 || minute_polaska < 0 || minute_polaska > 59){
            DomainError();
        }
        else if(trajanje_voznje <= 0){
            DomainError();
        }
    }

    public:
    Polazak(std::string odrediste, std::string oznaka_voznje, int br_perona, int sat_polaska, int minute_polaska, int trajanje_voznje) : odrediste(odrediste), oznaka(oznaka_voznje), broj_perona(br_perona), sat(sat_polaska), minute(minute_polaska), trajanje(trajanje_voznje), kasnjenje(0){
        provjeravanje(odrediste, oznaka_voznje, br_perona, sat_polaska, minute_polaska, trajanje_voznje);
    }

    int PostaviKasnjenje(int lateness){
        if(lateness < 0){
            LogicError();
        }
        else{
            kasnjenje = lateness;
        }
    }
  

    bool DaLiKasni() const {
        bool rezultat = kasnjenje > 0;
        return rezultat;
    }

    int DajTrajanje() const {
        return trajanje;
    }

    void OcekivanoVrijemePolaska(int &sati, int &minute2) const{
        if((minute + kasnjenje) <= 60){
            minute2 = minute + kasnjenje;
            sati = sat;
        }
        else{
            minute2 = (minute + kasnjenje) % 60;
            sati = sat + ((minute + kasnjenje) / 60);
        }
        if(sati > 24){
            while(sati > 24){
                sati -= 24;
            }
        }
    }


    void OcekivanoVrijemeDolaska(int &sati, int &minute2) const{
        if(minute + trajanje + kasnjenje <= 60){
            sati = sat;
            minute2 = minute + kasnjenje + trajanje;
        }
        else{
            sati = sat + ((minute + trajanje + kasnjenje) / 60);
            minute2 = (minute + trajanje + kasnjenje) % 60;
        }
        if(sati > 23){
            sati -= 23;
        }
            if(minute > 59){
                while(minute2 > 59){
                    minute2 -= 60;
                    sati -= 23;
                }
            }
        if(sati == 23 && minute2 == 60){
            sati = 0;
            minute2 = 0;
        }
    }

    void Ispisi() const{
        std::cout<<std::left<<std::setw(10)<<oznaka<<std::setw(35)<<odrediste<<" "<<std::setw(1)<<sat<<":";
        if(!(minute < 10)){
            std::cout<<minute + kasnjenje<<" ";
        }else{
            std::cout<<"0"<<minute + kasnjenje<<" ";
        }

        if(!DaLiKasni()){
            int sat_dolaska = sat + static_cast<int>(trajanje) / 60;
            int minute_dolaska = minute + (trajanje % 60);
            if(minute_dolaska >= 60){
                sat_dolaska++;
                minute_dolaska -= 60;
            }
            if(minute_dolaska < 10){
                std::cout<<"     "<<sat_dolaska<<":0"<<minute_dolaska;
            }else{
                std::cout<<"     "<<sat_dolaska<<":"<<minute_dolaska;
            }
            std::cout<<"     "<<broj_perona<<std::endl;
        }else{
            std::cout<<"(Planirano "<<sat<<":";
            if(minute < 10){
                std::cout<<"0"<<minute<<", Kasni "<<kasnjenje<<" min)";
            }else{
                std::cout<<minute<<", Kasni "<<kasnjenje<<" min)";
            }
        }
    }
};

//Druga klasa

    class Polasci{
       std::vector<Polazak *> polasci;
       int kapacitet, velicina;

       void provjeraPolasci(){
           if(this -> velicina == 0){
               RangeError();
           }
       }

        void provjeraKapacitet(){
        if(velicina == kapacitet){
            RangeError();
        }
    }
        
    public:
        explicit Polasci(int kapacitet) : kapacitet(kapacitet), velicina(0){
            polasci.reserve(kapacitet);
        }

        Polasci(std::initializer_list<Polazak> lista_polazaka) : kapacitet(lista_polazaka.size()), velicina(0) {
            polasci.reserve(kapacitet);
            for(const Polazak &polazak : lista_polazaka){
                Polazak *novi_polazak = new Polazak(polazak);
                polasci.push_back(novi_polazak);
                velicina++;
            }
        }

        ~Polasci(){
            IsprazniKolekciju();
        }
        Polasci(const Polasci &polasci){
            kapacitet = polasci.kapacitet;
            velicina = polasci.velicina;
            for(const auto *polazak : polasci.polasci){
                Polazak *novi_polazak = new Polazak(*polazak);
                this -> polasci.push_back(novi_polazak);
            }
        }
        Polasci(Polasci &&polasci) : kapacitet(polasci.kapacitet), velicina(polasci.velicina), polasci(std::move(polasci.polasci)){
            polasci.velicina = 0;
        }

        Polasci &operator = (const Polasci &polasci){
            if(this != &polasci){
                IsprazniKolekciju();
            
            for(const auto *polazak : polasci.polasci){
                    auto *novi_polazak = new Polazak(*polazak);
                    this -> polasci.push_back(novi_polazak);
                    velicina++;
                }
             }
             return *this;
          }

        Polasci &operator = (Polasci &&polasci){
            if(this != &polasci){
                IsprazniKolekciju();
                for(auto *polazak : polasci.polasci){
                    delete polazak;
                }
                kapacitet = polasci.kapacitet;
                velicina = polasci.velicina;
                this -> polasci = std::move(polasci.polasci);
                polasci.velicina = 0;
            }
            return *this;
        }


    void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int br_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
        provjeraKapacitet();
        auto *novi_polazak = new Polazak(odrediste, oznaka_voznje, br_perona, sat_polaska, minute_polaska, trajanje_voznje);
        polasci.push_back(novi_polazak);
        velicina++;
    }

    void RegistrirajPolazak(Polazak *polazak){
        provjeraKapacitet();
        polasci.push_back(polazak);
        velicina++;
    }

    int DajBrojPolazaka() const {
        return velicina;
    }

    int DajBrojPolazakaKojiKasne() const{
        return std::count_if(polasci.begin(), polasci.end(), [](const Polazak *p){ return p -> DaLiKasni(); });
    }


    Polazak &DajPrviPolazak() {
        provjeraPolasci();
        return *polasci.front();
    }

    Polazak DajPrviPolazak() const{
        if(!(this -> velicina)){
            RangeError();
        }
        return *polasci.front();
    }

    Polazak &DajPosljednjiPolazak(){
        provjeraPolasci();
        return *polasci.back();
    }
    
    Polazak DajPosljednjiPolazak() const {
        if(!(this -> velicina)){
            RangeError();
        }
        return *polasci.back();
    }

    void Ispisi() const{
        std::cout<<std::left<<std::setw(30)<<"Voznja"<<std::setw(5)<<"Odrediste"<<std::setw(30)<<"Polazak Dolazak Peron"<<std::endl;
        std::cout << "---------------------------------------------------------------------"<<std::endl<<std::endl;
        for(const auto *polazak : polasci){
            polazak -> Ispisi();
        }
    }

    void IsprazniKolekciju(){
        for(auto *polazak : polasci){
            delete polazak;
        }
        polasci.clear();
        velicina = 0;
    }
};

int main ()
{


	return 0;
}
