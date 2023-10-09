//TP 2022/2023: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using Matrica = std::vector<std::vector<int>>;

template <typename T>
bool Kriterij(const std::vector<T> v1, const std::vector<T> v2){
    T p1 = T();
    T p2 = T();
    if(v1.size() != 0){
        p1 = v1.at(0); 
    }
    if(v2.size() != 0){
        p2 = v2.at(0);
    }
    
    for(int i = 1; i < v1.size(); i++){
        p1 *= v1.at(i);
    }

    for(int i = 1; i < v2.size(); i++){
        p2 *= v2.at(i);
    }

    if(p1 == p2){
        return v1 < v2;
    }
    return p1 < p2;
}
    /*
    T p1 = 1;
    T p2 = 1;
    for(auto clan : v1){
        p1 *= clan;
    }
    for(auto clan : v2){
        p2 *= clan;
    }
    if(p1==p2) return v1<v2;
     return p1<p2;
}
*/

template <typename T>
void SortirajPoProizvoduRedova(std::vector<std::vector<T>> &m){
    std::sort(m.begin(), m.end(), Kriterij<T>);
}

int main (){
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
    std::cout<<std::endl;
    double broj = 0; 
    int vrijednost = 0;
    Matrica matrica;
    while(true){
        matrica.resize(vrijednost + 1);
        while(true){
            if(!(std::cin>>broj)){
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
            }
            matrica.at(vrijednost).push_back(broj);
        }
        if(matrica.at(vrijednost).size() == 0){
            break;
        }
        vrijednost++;
    }
std::cout<<"\nMatrica nakon sortiranja: ";
SortirajPoProizvoduRedova(matrica);
for(int i = 0; i < matrica.size(); i++){
    for(int j = 0; j < matrica.at(i).size(); j++){
        std::cout<<matrica.at(i).at(j)<<" ";
    }
    std::cout<<std::endl;
}
std::cout<<"\nUnesite elemente sekvence koja se trazi (* za kraj reda): ";
std::vector<int> sekvenca;
while(true){
    if(!(std::cin>>broj)){
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        break;
    }
    sekvenca.push_back(broj);
}
    std::vector<std::vector<int>>::iterator iter = std::lower_bound(matrica.begin(), matrica.end(), sekvenca, Kriterij<int>);

    if(iter != matrica.end() && *iter == sekvenca){
        std::cout<<"Trazena sekvenca se nalazi u "<<iter - matrica.begin()<<". redu (nakon sortiranja)";
    }else{
        std::cout<<"Trazena sekvenca se ne nalazi u matrici";
    }

	return 0;
}
