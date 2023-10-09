//TP 2022/2023: Zadaća 3, Zadatak 3
#include <iostream>
#include <cmath>
#include <new>
#include <iomanip>
#include <vector>
#include <stdexcept>

template <typename TipElemenata>
struct Matrica{
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr;
    char ime_matrice;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica <TipElemenata> &mat){
    if(!mat.elementi){
        return;
    }
    for(int i = 0; i < mat.br_redova; i++){
        delete[] mat.elementi[i];
    }
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica <TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0){
    Matrica <TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova] {};
    try{
        for(int i = 0; i < br_redova; i++){
            mat.elementi[i] = new TipElemenata[br_kolona];
        }
    }catch(...){
            UnistiMatricu(mat);
            throw;
        }
        return mat;
    }


template <typename TipElemenata>
void UnesiMatricu(Matrica <TipElemenata> &mat){
    for(int i = 0; i < mat.br_redova; i++){
        for(int j = 0; j < mat.br_kolona; j++){
            std::cout<<mat.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>mat.elementi[i][j];
        }
    }
}


template <typename TipElemenata>
void IzbrisiGa(const Matrica<TipElemenata> &mat){
    if(!mat.elementi){
        return;
    }
    for(int i = 0; i < mat.br_redova; i++){
        delete[] mat.elementi[i];
    }
    delete[] mat.elementi;
}


template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost = 6, bool p = false){
    for(int i = 0; i < mat.br_redova; i++){
        for(int j = 0; j < mat.br_kolona; j++){
            std::cout<<std::setw(sirina_ispisa)<<std::setprecision(preciznost)<<mat.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    if(p == true){
        IzbrisiGa(mat);
    }
}


template <typename TipElemenata>
Matrica <TipElemenata> ZbirMatrica(const Matrica <TipElemenata> &m1, const Matrica <TipElemenata> &m2){
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona){
        throw std::domain_error("Matrice nemaju jednake dimenizje!");
    }
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++){
        for(int j = 0; j < m1.br_kolona; j++){
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        }
    }
    return m3;
}



template <typename TipElemenata>
bool ProvjeriDimenzije(const Matrica <TipElemenata> &m1, const Matrica <TipElemenata> &m2){
    if(m1.br_kolona == 0 || m2.br_kolona == 0 || m1.br_redova == 0 || m2.br_redova == 0){
        return false;
    }
    return true;
}



template <typename TipElemenata>
Matrica <TipElemenata> ProduktMatrica(const Matrica <TipElemenata> &m1, const Matrica <TipElemenata> &m2){
    if(m1.br_kolona != m2.br_redova || ProvjeriDimenzije(m1, m2) == false){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    auto nova = StvoriMatricu <TipElemenata> (m1.br_redova, m2.br_kolona);
    for(int i = 0; i < m1.br_redova; i++){
        for(int j = 0; j < m2.br_kolona; j++){
            nova.elementi[i][j] = 0;
            for(int k = 0; k < m1.br_kolona; k++){
                nova.elementi[i][j] += m1.elementi[i][k] * m2.elementi[k][j];
            }
        }
    }
    return nova;
}


template <typename TipElemenata>
void Skalarno(Matrica <TipElemenata> &m1, TipElemenata n){
    for(int i = 0; i < m1.br_redova; i++){
        for(int j = 0; j < m1.br_kolona; j++){
            m1.elementi[i][j] *= 1./n;
        }
    }
}



template <typename TipElemenata>
void Prepisi(const Matrica<TipElemenata> &m1,  const Matrica <TipElemenata> &m2){
    for(int i = 0; i < m2.br_redova; i++){
        for(int j = 0; j < m2.br_kolona; j++){
            m1.elementi[i][j] = m2.elementi[i][j];
        }
    }
}


template <typename TipElemenata>
Matrica <TipElemenata> MatricniHarmonijskiPolinom(const Matrica <TipElemenata> &m1, int n){
    if(m1.br_kolona != m1.br_redova){
        throw std::domain_error("Matrica nije kvadratna");
    }
    if(n < 0){
        throw std::domain_error("Pogresan parametar n");
    }
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona, 'a');
    Prepisi(m3, m1);
    auto m4 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona, 'f');
    Prepisi(m4, m1);
    auto m5 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona, 'f');
    Prepisi(m5, m1);
    auto m6 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona, 'f');
    for(TipElemenata i = 1; i <= n; i++){
        if(i != 1){
            auto m2 = ProduktMatrica(m5, m3);
            Prepisi(m5, m2);
            Prepisi(m6, m2);
            UnistiMatricu(m2); 
        }
        if(i != 1){
            Skalarno(m6, i);
            auto m7 = ZbirMatrica(m4, m6);
            Prepisi(m4, m7);
            UnistiMatricu(m7);
        }
    }
    UnistiMatricu(m6);
    UnistiMatricu(m3);
    UnistiMatricu(m5);
    return m4;
}


int main ()
{
std::cout<<"Unesite dimenziju kvadratne matrice: ";
int dimenzija;
std::cin>>dimenzija;
std::cout<<"Unesite elemente matrice A: ";


	return 0;
}
