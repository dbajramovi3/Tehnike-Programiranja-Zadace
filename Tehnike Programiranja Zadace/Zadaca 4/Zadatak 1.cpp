//TP 2022/2023: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <vector>

void Ciscenje(){
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

const double PI = 4 * atan(1);
const double EPSILON = std::pow(10, -10);

class Krug{
    double x, y, r;
    void TestPoluprecnika(const double r){
        if(r < 0){
            throw std::domain_error("Nedozvoljen poluprecnik");
        }
    }

   public:
    explicit Krug(double r = 0){
        TestPoluprecnika(r);
        x = y = 0;
        Krug::r = r;
    }

    Krug(double x, double y, double r = 0){
        TestPoluprecnika(r);
        Krug::x = x;
        Krug::y = y;
        Krug::r = r;
    }

    explicit Krug(const std::pair<double, double> &centar, double r = 0){
        TestPoluprecnika(r);
        x = centar.first;
        y = centar.second;
        Krug::r = r;
    }

    double DajX() const {
         return x; 
         }

    double DajY() const { 
        return y; 
        }

    std::pair<double, double> DajCentar() const {
        return std::pair<double, double> {x, y}; 
    }

    double DajPoluprecnik() const {
         return r; 
         }

    double DajPovrsinu() const;

    double DajObim() const;  

    Krug &PostaviCentar(const std::pair<double, double> &centar);

    Krug &PostaviPoluprecnik(double r){
        TestPoluprecnika(r);
        Krug::r = r;
        return *this;
    }

    void Ispisi() const{
        std::cout<<"{("<<DajX()<<","<<DajY()<<"),"<<DajPoluprecnik()<<"}"<<std::endl;
    }

Krug &Transliraj(double delta_x, double delta_y);
Krug &Rotiraj(double alpha);
Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
static double RastojanjeCentara(const Krug &k1, const Krug &k2);
static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2);
static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2);
static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2);
static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
static bool DaLiSeSijeku(const Krug &k1, const Krug &k2);
bool DaLiSadrzi(const Krug &k) const;
friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
friend Krug RotiraniKrug(const Krug &k, double alpha);
friend Krug RotiraniKrug(const Krug &k,
 const std::pair<double, double> &centar_rotacije, double alpha);

};

//Zavrsili smo sa klasom, slijedi implementacija izvan klase


double Krug::DajPovrsinu() const{
    double povrsina = 0;
    povrsina = r*r*PI;
    return povrsina;
}

double Krug::DajObim() const{
    double obim = 0;
    obim = 2*r*PI;
    return obim;
}

Krug &Krug::PostaviCentar(const std::pair<double, double> &centar){

    Krug::x = centar.first;
    Krug::y = centar.second;

    return *this;
}

Krug &Krug::Transliraj(double delta_x, double delta_y){
    Krug::x += delta_x;
    Krug::y += delta_y;
    return *this;
}

Krug &Krug::Rotiraj(double alpha){
    double x_prim = x;
    double y_prim = y;
    double pomocna;
    Krug::x = x_prim * cos(alpha * PI/180) - y_prim * sin(alpha * PI / 180);
    Krug::y = x_prim * sin(alpha * PI/180) + y_prim * cos(alpha * PI / 180);

    return *this;
}

Krug &Krug::Rotiraj(const std::pair<double, double>& centar_rotacije, double alpha){
    double x_prim = centar_rotacije.first + (x - centar_rotacije.first) * cos(alpha * PI /180 ) - (y - centar_rotacije.second) * sin(alpha * PI / 180);
    double y_prim = centar_rotacije.second + (x - centar_rotacije.first) * sin(alpha * PI /180 ) + (y - centar_rotacije.second) * cos(alpha * PI / 180);
    Krug::x = x_prim;
    Krug::y = y_prim;
    return *this;
}


bool Krug::DaLiSuIdenticni(const Krug &k1, const Krug &k2){
    if(!(std::abs(k1.x == k2.x) <= EPSILON && std::abs(k1.y == k2.y) <= EPSILON && std::abs(k1.r == k2.r) <= EPSILON)){
        return false;
    }
    return true;
}

bool Krug::DaLiSuPodudarni(const Krug &k1, const Krug &k2){
    if(!std::abs((k1.r == k2.r) <= EPSILON)){
        return true;
    }
    return false;
}

bool Krug::DaLiSuKoncentricni(const Krug &k1, const Krug &k2){
    if(!std::abs((k1.x == k2.x) <= EPSILON && std::abs(k1.y == k2.y) <= EPSILON)){
        return false;
    }
    return true;
}

double Krug::RastojanjeCentara(const Krug &k1, const Krug &k2){
    auto rastojanje_centara = std::sqrt((k1.x - k2.x) * (k1.x - k2.x) + (k1.y - k2.y) * (k1.y - k2.y));
    if(rastojanje_centara <= EPSILON){
        return 0.0;
    }
    return rastojanje_centara;
}

bool Krug::DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2){
    double rastojanje = RastojanjeCentara(k1, k2);
    double brojR = k1.r + k2.r;
    if(std::abs(rastojanje - brojR) <= EPSILON){
        return true;
    }
    return false;
}

bool Krug::DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2){
    int varijabla;
    if(k1.r > k2.r){
        if(std::abs(k1.r == k2.r - RastojanjeCentara(k1, k2) <= EPSILON)){
            return true;
        }
    }
    else if(k1.r < k2.r){
            if(std::abs(k2.r == k1.r) - RastojanjeCentara(k1, k2) <= EPSILON){
                return true;
            }
        }
    return false;
}

bool Krug::DaLiSePreklapaju(const Krug &k1, const Krug &k2){
    if(k1.r > k2.r){
        if(std::abs(k1.r > k2.r) - RastojanjeCentara(k1, k2) <= EPSILON){
            return true;
        }
    }
    if(k1.r < k2.r){
        if(std::abs(k1.r > k1.r) - RastojanjeCentara(k1, k2) <= EPSILON){
            return true;
        }
    }
    return false;
}

//Nema potrebe da u ovom dijelu koristimo epsilon
bool Krug::DaLiSeSijeku(const Krug &k1, const Krug &k2){
    if(RastojanjeCentara(k1, k2) < k1.r + k2.r ){
        return true;
    }
    return false;
}

//Također ovdje i u ostalim funkcijama
bool Krug::DaLiSadrzi(const Krug &k) const {
   if(Krug::r > k.r + RastojanjeCentara(*this, k)){
       return true;
   }
   return false;
}

Krug TranslirajKrug(const Krug &k1, double delta_x, double delta_y){
    Krug krug;
    std::pair<double, double> centar_K = k1.DajCentar();
    krug.PostaviCentar(centar_K).PostaviPoluprecnik(k1.DajPoluprecnik()).Transliraj(delta_x, delta_y);
    return krug;
}

Krug RotiraniKrug(const Krug &k1, double alpha){
    Krug n = k1;
    return n.Rotiraj(alpha);
}

int main ()
{
        int brKrugova = 0;
        int brojac = 0;
        int brojac2 = 0;

        std::cout<<"Unesite broj krugova: ";
        std::cin>>brKrugova;

        if(brKrugova <= 0){
            std::cout<<"Uneseni broj nije prirodan!";
            return 0;
        }

        Krug **n1 =new Krug*[brKrugova];
        for(int i = 0; i < brKrugova; i++){
            bool var = false;
            double x, y, poluprecnik;
            x = y = poluprecnik = 0;
            for(;!var;){
                std::cout<<"Unesite centar "<< i + 1 << ". kruga: ";
                if(!(std::cin>>x>>y)){
                    Ciscenje();
                    std::cout<<"Neispravne koordinate centra! Pokusajte ponovo: "<<std::endl;
                    std::cout<<std::endl;
                    var = false;
                    continue;
                }
            std::cout<<"Unesite poluprecnik "<< i + 1 <<". kruga: ";
            if(!(std::cin>>poluprecnik)){
                Ciscenje();
                std::cout<<"Neispravan unos poluprecnika, unesite ponovo: "<<std::endl;
                var = false;
                continue;
            }
            var = true;
            }
            try{
                n1[i] = new Krug({x, y}, poluprecnik);
            }
            catch(std::domain_error e){
                std::cout<<"Neispravan poluprecnik! Pokusajte ponovo: "<<std::endl<<std::endl;
                i--;
            }
        }
        double delta_x, delta_y;
        delta_x = delta_y = 0;
    std::cout<<"Unesite parametre translacije (delta_x,delta_y): ";
    std::cin>>delta_x>>delta_y;

    std::transform(n1, n1 + brKrugova, n1, [&](Krug *iter){
        iter -> Transliraj(delta_x, delta_y);
        return iter;
    });

    std::cout<<"Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
    auto alpha = 0;
    std::cin>>alpha;
    std::transform(n1, n1 + brKrugova, n1, [&](Krug *iter){
        iter -> Rotiraj({0, 0}, alpha);
        return iter;
    });

    std::cout<<"Parametri krugova nakon obavljene transformacije su: "<<std::endl;
    std::sort(n1, n1 + brKrugova, [](Krug *iterat, Krug *iterat2){
        return iterat -> DajPovrsinu() < iterat2 -> DajPovrsinu();
    });

    std::for_each(n1, n1 + brKrugova, [](Krug *iter){
        iter -> Ispisi();
        std::cout<<std::endl;
    });

    Krug *o = *std::max_element(n1, n1 + brKrugova, [](Krug *iter1, Krug *iter2){
        return iter1 -> DajObim() < iter2 -> DajObim();
    });

    std::cout<<"Krug sa najvecim obimom je: ";
    o -> Ispisi();
    std::vector<std::pair<Krug*, Krug*>> v;

    for(int i = 0; i < brKrugova; i++){
        for(int j = i + 1; j < brKrugova; j++){
            auto l1 = n1[i]; auto l2 = n1[j];

            if(Krug::DaLiSeSijeku(*l1, *l2) && !l1 -> DaLiSadrzi(*l2) && !l2 ->DaLiSadrzi(*l1)){
                std::cout<<"\nPresjecaju se krugovi: ";
                l1 -> Ispisi();
                std::cout<<" i ";
                l2 -> Ispisi();
                brojac++;
            }
        }
    }
    if(brojac == 0){
        std::cout<<"\nNe postoje krugovi koji se presjecaju!"<<std::endl;
    }
        for(int i = 0; i < brKrugova; i++){
            delete n1[i];
        }
        delete[] n1;

	return 0;
}
