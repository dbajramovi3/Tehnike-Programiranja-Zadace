//TP 2022/2023: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <algorithm>

void BaciError(){
    throw std::range_error("Ilegalna maksimalna kolicina");
}

void BaciRangeError(){
    throw std::range_error("Ilegalna kolicina padavina");
}

class Padavine{

    std::vector<int> kolicina_padavina;
    int max_kolicina_padavina = 0;
public:
    explicit Padavine(int broj){
        if(broj <= 0){
            BaciError();
        }
        max_kolicina_padavina = broj;
    }

    void RegistrirajPadavine(int broj){
        if(broj < 0 || broj > max_kolicina_padavina){
            BaciRangeError();
        }
        kolicina_padavina.push_back(broj);
    }

    int DajBrojRegistriranihPadavina() const{
        return kolicina_padavina.size();
    }

    void BrisiSve(){
        kolicina_padavina.clear();
    }

    int DajMinimalnuKolicinuPadavina() const{
        if(kolicina_padavina.size() == 0){
            BaciRangeError();
        }
        return *std::min_element(kolicina_padavina.begin(), kolicina_padavina.end());
    }

    int DajMaksimalnuKolicinuPadavina() const{
        if(kolicina_padavina.size() == 0){
            BaciRangeError();
        }
        return *max_element(kolicina_padavina.begin(), kolicina_padavina.end());
    }

    int DajBrojDanaSaPadavinamaVecimOd(int broj) const{
        if(kolicina_padavina.size() == 0){
            BaciRangeError();
        }
        return std::count_if(kolicina_padavina.begin(), kolicina_padavina.end(), std::bind(std::greater<int>(), std::placeholders::_1, broj));
    }

    void Ispisi() const{
        auto pok(kolicina_padavina);
        std::sort(pok.begin(), pok.end(), std::greater<int>());
        for(auto x : pok){
            std::cout<<x<<std::endl;
        }
    }

    int operator [] (int broj) const{
        if(broj <= 0 || broj >= kolicina_padavina.size()){
            throw std::range_error("Neispravan indeks");
        }
        return kolicina_padavina.at(broj - 1);
    }

    friend Padavine& operator +=(Padavine &p1, int n);
    friend Padavine& operator -=(Padavine &p1, const Padavine &p2);
    friend Padavine& operator -=(Padavine &p1, int n);
    friend Padavine operator -(Padavine p1, Padavine p2);
    friend Padavine operator +(Padavine p, int n);
    friend Padavine operator +(int n, Padavine p);
    friend Padavine operator -(int n, Padavine p);
    friend Padavine operator -(Padavine p, int n);
    friend Padavine operator -(Padavine p);
    friend bool operator ==(const Padavine &p1, const Padavine &p2);
    friend bool operator !=(const Padavine &p1, const Padavine &p2);
    friend Padavine operator ++(Padavine &p1, int);
    friend Padavine& operator ++(Padavine &p1);
};

Padavine operator ++(Padavine &p, int){
    auto kopija = p;
    p.max_kolicina_padavina++;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::plus<int>(), 1, std::placeholders::_1));
    return kopija;
}

Padavine& operator ++(Padavine &p){
    p.max_kolicina_padavina++;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::plus<int>(), 1, std::placeholders::_1));
    return p;
}

bool operator ==(const Padavine &p1, const Padavine &p2){
    if(p1.kolicina_padavina.size() != p2.kolicina_padavina.size()){
        return false;
    }
    return std::equal(p1.kolicina_padavina.begin(), p1.kolicina_padavina.end(), p2.kolicina_padavina.begin());
}

bool operator !=(const Padavine &p1, const Padavine &p2){
    return !(p1 == p2);
}

Padavine operator -(Padavine p){
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::minus<int>(), p.max_kolicina_padavina, std::placeholders::_1));
    return p;
}

Padavine& operator +=(Padavine &p1, int n){
    p1 = p1 + n;
    return p1;
}

Padavine& operator -=(Padavine &p1, int n){
    p1 = p1 - n;
    return p1;
}

Padavine& operator -=(Padavine &p1, const Padavine &p2){
    p1 = p2 - p1;
    return p1;
}

Padavine operator -(Padavine p1, Padavine p2){
    if(p1.kolicina_padavina.size() != p2.kolicina_padavina.size()){
        throw std::domain_error("Nesaglasni operandi");
    }
    std::transform(p1.kolicina_padavina.begin(), p1.kolicina_padavina.end(), p2.kolicina_padavina.begin(), p1.kolicina_padavina.begin(), std::minus<int>());
    return p1;
}

Padavine operator +(Padavine p, int n){
    p.max_kolicina_padavina += n;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::plus<int>(), n, std::placeholders::_1));
    return p;
}

Padavine operator +=(int n, Padavine p){
    return p - n;
}

Padavine operator -(Padavine p, int n){
    p.max_kolicina_padavina -= n;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::plus<int>(), -n, std::placeholders::_1));
    if(std::count_if(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), std::bind(std::greater<int>(), 0, std::placeholders::_1))){
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    return p;
}

Padavine operator -(int n, Padavine p){
    p.max_kolicina_padavina = n;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), p.kolicina_padavina.begin(), std::bind(std::minus<int>(), n, std::placeholders::_1));
    if(std::count_if(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), std::bind(std::greater<int>(), 0, std::placeholders::_1))){
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    return p;
}

int main ()
{


	return 0;
}
