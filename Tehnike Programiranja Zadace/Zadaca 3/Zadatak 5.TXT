//TP 2022/2023: Zadaća 3, Zadatak 5
#include <iostream>
#include <cmath>

struct Cvor{
    int redni_broj;
    Cvor *sljedeci;
};

int Poglavica(int n, int m, bool p = false){
    if(m == 1){
        return n;
    }
    Cvor *pocetak = nullptr;
    Cvor *prethodni;
        for(int i = 1; i <= n; i++){
            Cvor *var = new Cvor{
                i, nullptr
            };
            if(!pocetak){
                pocetak = var;
                var -> sljedeci = pocetak;
            }else{
                prethodni -> sljedeci = var;
            }
            prethodni = var;
            if(i == n){
                var -> sljedeci = pocetak;
            }
        }
    int var2 = 0, var3 = 1;
    auto p1 = pocetak -> sljedeci;
    while(var2 != n - 1){
        if(var3 == m - 1){
            auto p2 = p1;
            if(p == true){
                std::cout<<p2 -> redni_broj<<", ";
            }
            pocetak -> sljedeci = p1 -> sljedeci;
            p1 = p1 -> sljedeci;
            delete p2;
            var2++;
            var3 = 0;
        }
        var3++;
        p1 = p1 -> sljedeci;
        pocetak = pocetak -> sljedeci;
    }
    int final = pocetak -> redni_broj;
    p1 = nullptr;
    delete pocetak;
    pocetak = nullptr;
    return final;
}
//SigurnoMjesto funkcija ce ostati ista, isto kao i main
int SigurnoMjesto(int m, int n1, int n2){
    for(int i = 1; i <= n2; i++){
        int var = n1;
        bool safe = true;
        while(var <= n2){
            if(Poglavica(var, m) == i) safe = false;
            var++;
        }
        if(safe)
        return i;
    }
    return 0;
}

int main ()
{
    std::cout<<"Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
    int br_cl, br_raz, N1, N2;
    std::cin>>br_cl;
    std::cout<<"Unesite korak razbrajanja: ";
    std::cin>>br_raz;
    std::cout<<"Unesite raspon za odabir (N1 i N2): ";
    std::cin>>N1>>N2;
    std::cout<<"Redni broj osobe koja postaje poglavica: "<<Poglavica(br_cl, br_raz);
    std::cout<<std::endl;
    auto var = SigurnoMjesto(br_raz, N1, N2);
    if(var == 0){
        std::cout<<"Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
        return 0;
    }
    std::cout<<"Mbebe Mgogo, stani na sigurno mjesto "<<SigurnoMjesto(br_raz, N1, N2)<<" da ne bi bio poglavica!";
    return 0;
}
