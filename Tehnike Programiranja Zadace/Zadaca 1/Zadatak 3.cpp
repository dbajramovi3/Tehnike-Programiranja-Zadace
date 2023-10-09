//TP 2022/2023: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

std::vector<std::vector<int>> KreirajSpiralnuMatricu(int broj_redova, int broj_kolona, int broj, bool provjeraD){
    if(broj_redova <= 0 || broj_kolona <= 0){
        return {};
    }
    std::vector<std::vector<int>> matrica(broj_redova, std::vector<int>(broj_kolona));
    int udaljenost = 0;
    int brojac = 0;
    while(brojac < broj_redova * broj_kolona){
        for(int j = udaljenost; j < broj_kolona - udaljenost; j++){
            if(provjeraD){
                matrica.at(udaljenost).at(j) = broj++;
            }
            else{
                matrica.at(j).at(udaljenost) = broj++;
            }
            brojac++;
            if(brojac == broj_redova * broj_kolona){
                return matrica;
            }
        }
        for(int i = udaljenost + 1; i < broj_redova - udaljenost; i++){
            if(provjeraD){
                matrica.at(i).at(broj_kolona - udaljenost - 1) = broj++;
            }
            else{
                matrica.at(broj_kolona - udaljenost - 1).at(i) = broj++;
            }
            brojac++;
            if(brojac == broj_redova * broj_kolona){
                return matrica;
            }
        }
        for(int j = broj_kolona - udaljenost - 2; j >= udaljenost; j--){
            if(provjeraD){
                matrica.at(broj_redova - udaljenost -1).at(j) = broj++;
            }
            else{
                matrica.at(j).at(broj_kolona - udaljenost - 1) = broj++;
            }
            brojac++;
            if(brojac == broj_redova * broj_kolona){
                return matrica;
            }
        }
        for(int i = broj_redova - udaljenost -2; i >= udaljenost + 1; i--){
            if(provjeraD){
                matrica.at(i).at(udaljenost) = broj++;
            }
            else{
                matrica.at(udaljenost).at(i) = broj++;
            }
            brojac++;
            if(brojac == broj_redova * broj_kolona){
                return matrica;
            }
        }
        udaljenost++;
    }
   return matrica;
}

bool DaLiJeSpiralnaMatrica(std::vector<std::vector<int>> mat){
    int prvi = mat.at(0).at(0);
    long long int posljednji = prvi + mat.size() * mat.at(0).size() - 1;
    long long int suma = 0;
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat.at(i).size(); j++){
            suma += mat.at(i).at(j);
        }
    }
    long double prosjek = suma * 1.0 / (mat.size() * mat.at(0).size());
    long double pr = (prvi + posljednji) / 2.0;
    return fabs(prosjek - pr ) < 0.0001;
}

//Funkcija vraca maks broj cifri u bilo kojem elementu matrice
//Ukljucujuci i negativni predznak ako je prisutan
int Sirina(std::vector<std::vector<int>> matrica){
    int max_sirina = 0;
    for(int i = 0; i < matrica.size(); i++){
        for(int j = 0; j < matrica.at(i).size(); j++){
            int broj = matrica.at(i).at(j);
            int sirina = 1;
            if(broj < 0){
                sirina ++;
                broj = -broj;
            }
            while(broj >= 10){
                sirina++;
                broj /= 10;
            }
            if(sirina > max_sirina){
                max_sirina = sirina;
            }
        }
    }
    return max_sirina;
}

int main (){
    std::cout<<"Unesite broj redova i kolona matrice: ";
    int bred, bkolona;
    std::cin>>bred>>bkolona;

    int pvrijednost;
    std::cout<<"Unesite pocetnu vrijednost: ";
    std::cin>>pvrijednost;

    std::cout<<"Unesite L za lijevu, a D za desnu spiralnu matricu: "<<std::endl;
    char dD_ili_lL;
    std::cin>>dD_ili_lL;

    bool orijentacija = (dD_ili_lL == 'D');
    auto finalna = KreirajSpiralnuMatricu(bred, bkolona, pvrijednost, orijentacija);

    std::cout<<"Kreirana spiralna matrica: \n";
    for(int i = 0; i < finalna.size(); i++){
        for(int j = 0; j < finalna.at(i).size(); j++){
            std::cout<<std::right<<std::setw(Sirina(finalna) + 1)<<finalna.at(i).at(j);
        }
        std::cout<<std::endl;
    }
	return 0;
}
