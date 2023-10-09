//TP 2022/2023: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <list>

int BrojElemenata(std::list<int> &v1){
    int broj = 0;
    for(auto it = v1.begin(); it != v1.end(); it++){
        broj++;
    }
    return broj;
}

int Poglavica(int n, int m, bool p = false){
    std::list<int> v;
        for(int i = 1; i <= n; i++){
            v.push_back(i);
        }
        int broj = 1;
        if(m == 1){
            return n;
        }
            for(auto it = v.begin(); it != v.end(); it++){
                auto var = --v.end();
                bool check = false;
                if(BrojElemenata(v) == 1){
                    return *it;
                }
                if(broj == m) {
                    if(p){
                        std::cout<<*it<<", ";
                    }
                    it = v.erase(it);
                    broj = 1;
                    check = true;
                }
                if(it == var){
                    it =-- v.begin();
                }
                else if(it == v.end() && check == true){
                    it = --v.begin();
                    broj = 0;
                }
                broj++;
            }
        }
    int SigurnoMjesto(int m, int n1, int n2){
        for(int i = 1; i <= n2; i++){
            int var = n1;
            bool safe = true;
            while(var <= n2){
                if(Poglavica(var, m) ==  i) safe = false;
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
