//TP 2022/2023: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>

std::vector<std::vector<double>> UsrednjavajuciFilter(std::vector<std::vector<double>> matrica, int N){
    //Ukoliko je N < 0 baca se domain error
    if(N < 0){
        throw std::domain_error("Neispravan red filtriranja");
    }
    /*else if( N == 0){
        return matrica;
    }*/
    else{
        std::vector<std::vector<double>> finalna_matrica;
    for(int i = 0; i < matrica.size(); i++){
        finalna_matrica.push_back(std::vector<double>(matrica.at(i).size()));
        for(int j = 0; j < matrica.at(i).size(); j++){
            double suma = 0;
            int broj_piksela = 0;
            //kod od 24-37
            //Izracunava zbir svih elemenata u kvadratnom prozoru oko određenog elementa u matrici i vraća prosjek tih elemenata
            for(int k = i - N; k <= i + N; k++){
                for(int l = j - N; l <= j + N; l++){
                    if(k >= 0){
                        if(k < matrica.size()){
                            if(l >= 0){
                                if(l < matrica.at(k).size()){
                                    suma += matrica.at(k).at(l);
                                    broj_piksela++;
                                }
                            }
                        }
                    }
                }
            }
            //Izracunava konacnu vr. za svaki element u finalnoj matrici
            if(broj_piksela == 0){
                //postavljen na 0
                finalna_matrica.at(i).at(j) = 0;
            }
            else{
                //izracunava prosjek el. u prozoru oko trenutnog elementa
            finalna_matrica.at(i).at(j) = suma / broj_piksela;
        }
    }
}
    return finalna_matrica;
    }
}
int main (){
    int bred, bkolona;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>bred>>bkolona;
    std::vector<std::vector<double>> m(bred, std::vector<double>(bkolona, 0.0));
    std::cout<<"Unesite elemente matrice: ";
    for(int i = 0; i < bred; i++){
        for(int j = 0; j < bkolona; j++){
            std::cin>>m.at(i).at(j);
        }
    }
    std::cout<<"Unesite red filtriranja: ";
    int N;
    std::cin>>N;
    try{
        std::vector<std::vector<double>> matrica = UsrednjavajuciFilter(m, N);
        std::cout<<"Matrica nakon filtriranja: ";
        for(int i = 0; i < bred; i++){
            for(int j = 0; j < bkolona; j++){
                std::cout<<std::setw(7)<<std::fixed<<std::setprecision(2)<<matrica.at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error e){
        std::cout<<"\nGRESKA: "<<e.what()<<"!";
    }
	return 0;
}
