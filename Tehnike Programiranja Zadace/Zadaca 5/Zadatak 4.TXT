//TP 2022/2023: Zadaća 5, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>
#include <istream>
#include <new>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cstring>

void BaciRangeError(){
     throw std::range_error("Neispravan index");
}

void BaciLogicError1(){
    throw std::logic_error("Trazena datoteka ne postoji");
}

void BaciLogicError2(){
    throw std::logic_error("Trazena datoteka ne postoji");
}
template <typename Tip>
class Matrica{

    int br_redova;
    char ime_matrice;
    int br_kolona;
    Tip **elementi;
    static Tip **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(Tip **elementi, int br_redova);
    void KopirajElemente(Tip **elementi);

public:
Matrica(int br_redova, int br_kolona, char ime = 0);
Matrica(const Matrica &m);
Matrica(Matrica &&m);
~Matrica(){
    DealocirajMemoriju(elementi, br_redova);
}
Matrica &operator =(const Matrica &m);
Matrica &operator =(Matrica &&m);

template <typename T>
friend std::istream &operator>>(std::istream &tok, Matrica <T> &mat);

template <typename T>
friend std::ostream &operator<<(std::ostream &tok, Matrica <T> &mat);

template <typename T>
friend Matrica<T> operator+(const Matrica <T> &m1, const Matrica <T> &m2);

template <typename T1, typename T2>
friend Matrica<T1> operator*(T2 broj, const Matrica <T1> &m1);

template <typename T1, typename T2>
friend Matrica<T1> operator*(const Matrica<T1> &m1, T2 broj);

template <typename T>
friend Matrica<T> operator*(const Matrica<T> &m1, const Matrica<T> &m2);

template <typename T>
friend Matrica<T> operator-(const Matrica<T> &m1, const Matrica<T> &m2);

Tip* operator[](int index) const{
    return elementi[index];
}

Tip &operator ()(int index1, int index2) const{
    if(index1 < 1 || index1 > br_redova || index2 < 1 || index2 > br_kolona){
        BaciRangeError();
    }
    return elementi[index1 - 1][index2 - 1];
}

operator std::string() const;
template <typename T>
friend Matrica<T> &operator+=(Matrica<T> &m1, const Matrica<T> &m2);

template <typename T>
friend inline Matrica<T> &operator-=(Matrica<T> &m1, const Matrica<T> &m2);

template <typename T>
friend inline Matrica<T> &operator*=(Matrica<T> &m1, const Matrica<T> &m2);

template <typename T>
friend inline Matrica<T> &operator*=(Matrica<T> &m1, double cifra);

template <typename T>
friend inline Matrica<T> &operator*=(double cifra, Matrica<T> &m1);

void SacuvajUTekstualnuDatoteku(std::string dat){
    std::ostream tok(dat);
    if(!tok){
        BaciLogicError1();
    }
    for(int i = 0; i < br_redova; i++){
        for(int j = 0; j < br_kolona; j++){
            if(j != br_kolona - 1){
                tok<<elementi[i][j]<<',';
            }
            else{
                tok<<elementi[i][j];
            }
            if(!tok){
                throw std::logic_error("Problemi sa upisom u datoteku");
            }
        }
        tok<<std::endl;
    }
}

void SacuvajUBinarnuDatoteku(std::string dat){
    std::ofstream tok(dat, std::ios::binary);
    if(!tok){
        BaciLogicError2();
    }
    tok.write(reinterpret_cast<const char*>(this), sizeof*this);
    for(int i = 0; i < br_redova; i++){
        tok.write(reinterpret_cast<char*>(elementi[i]), sizeof(Tip)*br_kolona);
        if(!tok){
            throw std::logic_error("Problemi sa upisom u datoteku");
        }
    }
}

void ObnoviIzTekstualneDatoteke(std::string dat){
    std::ifstream tok(dat);
    if(!tok){
        BaciLogicError2();
    }
        Tip br;
        char znak;
        std::vector<std::vector<Tip>> v;
        std::vector<Tip> red;
        while(tok>>br){
            red.push_back(br);
            if(tok.peek()!=tok.eof()){
                if(tok.peek() == '\n'){
                    tok.ignore(1, '\n');
                    znak = '\n';
                }
                else{
                    tok>>znak;
                    if(znak != ','){
                        throw std::logic_error("Datoteka sadrzi besmislene podatke");
                    }
                }
                if(znak == '\n'){
                    
                    v.push_back(red);
                    red.clear();
                }
            }
        }
        v.push_back(red);
        int kol(v.at(0).size());
        for(auto x : v)
            if(x.size() != kol){
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            DealocirajMemoriju(elementi, br_redova);
            elementi = AlocirajMemoriju(v.size(), kol);
            for(int i = 0; i < v.size(); i++)
                for(int j = 0; j < kol; j++)
                elementi[i][j] = v.at(i).at(j);
}

void ObnoviIzBinarneDatoteke(std::string dat){
    std::ifstream tok(dat, std::ios::binary);
    if(!tok){
        BaciLogicError2();
    }
    DealocirajMemoriju(elementi, br_redova);
    tok.read(reinterpret_cast<char*>(this), sizeof *this);
    elementi = new Tip*[br_redova];
    for(int i = 0; i < br_redova; i++){
        elementi[i] = new Tip[br_kolona];
        tok.read(reinterpret_cast<char*>(elementi[i]), sizeof(Tip)*br_kolona);
        if(!tok) throw std::logic_error("Problemi pri citanju datoteke");
    }
}

Matrica(std::string dat, bool binarna){
    if(binarna){
        std::ifstream tok(dat, std::ios::binary);
        if(!tok) BaciLogicError2();
        tok.read(reinterpret_cast<char*>(this), sizeof *this);
        elementi = new Tip*[br_redova]{};
        for(int i = 0; i < br_redova; i++){
            elementi[i] = new Tip[br_kolona];
            tok.read(reinterpret_cast<char*>(elementi[i]), sizeof(Tip)*br_kolona);
            if(!tok) throw std::logic_error("Problemi pri citanju datoteke");
        }
    }else{
        std::ifstream tok(dat);
        if(!tok) BaciLogicError2();
        Tip br;
        char znak;
        std::vector<std::vector<Tip>> v;
        std::vector<Tip> red;
        while(tok >> br){
            red.push_back(br);
            if(tok.peek() != tok.eof()){
                if(tok.peek() == '\n'){
                    tok.ignore(1, '\n');
                    znak = '\n';
                }else{
                    tok>>znak;
                    if(znak != ',') throw std::logic_error("Datoteka sadrzi besmislene podatke");
                }
                if(znak == '\n'){
                    
                    v.push_back(red);
                    red.clear();
                }
            }
        }
        v.push_back(red);
        int kol(v.at(0).size());
        for(auto x : v)
            if(x.size() != kol){
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            elementi = AlocirajMemoriju(v.size(), kol);
            br_redova = v.size();
            br_kolona = kol;
            ime_matrice = 0;
            for(int i = 0; i < v.size(); i++)
                for(int j = 0; j < kol; j++)
                elementi[i][j] = v.at(i).at(j);
        }
    }
};

template <typename Tip>
Tip ** Matrica<Tip>::AlocirajMemoriju(int br_redova, int br_kolona){
    Tip **elementi = new Tip*[br_redova] {};
    try{
        for(int i = 0; i < br_redova; i++){
            elementi[i] = new Tip[br_kolona];
        }
    }catch(...){
        DealocirajMemoriju(elementi, br_redova);
        throw;
    }
    return elementi;
}

template <typename Tip>
void Matrica<Tip>::DealocirajMemoriju(Tip **elementi, int br_redova){
    for(int i = 0; i < br_redova; i++){
        delete[] elementi[i];
    }
    delete[] elementi;
}

template <typename Tip>
Matrica<Tip>::Matrica(int br_redova, int br_kolona, char ime) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime), elementi(AlocirajMemoriju(br_redova, br_kolona)) {}

template <typename Tip>
void Matrica<Tip>::KopirajElemente(Tip **elementi){
    for(int i = 0; i < br_redova; i++)
        for(int j = 0; j < br_kolona; j++)
            Matrica::elementi[i][j] = elementi[i][j];
}

template <typename Tip>
Matrica<Tip>::Matrica(const Matrica<Tip> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrica), elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)){
    KopirajElemente(m.elementi);
}

template <typename Tip>
Matrica<Tip>::Matrica(Matrica<Tip> &&m) : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice){
    m.br_redova = 0;
    m.elementi = nullptr;
}

template <typename Tip>
Matrica<Tip> &Matrica<Tip>::operator =(const Matrica<Tip> &m){
    if(br_redova < m.br_redova || br_kolona < m.br_kolona){
        Tip **novi = AlocirajMemoriju(m.br_redova, m.br_kolona);
        DealocirajMemoriju(elementi, br_redova);
        elementi = novi;
    } else if(br_redova > m.br_redova)
        for(int i = m.br_redova; i < br_redova; i++)
        delete elementi[i];
    br_redova = m.br_redova;
    br_kolona = m.br_kolona;
    ime_matrice = m.ime_matrice;
    KopirajElemente(m.elementi);
    return *this;
}

template <typename Tip>
Matrica<Tip> &Matrica<Tip>::operator =(Matrica<Tip> &&m){
    std::swap(br_redova, m.br_redova);
    std::swap(br_kolona, m.br_kolona);
    std::swap(ime_matrice, m.ime_matrice);
    std::swap(elementi, m.elementi);
    return *this;
}

template <typename Tip>
std::istream &operator>>(std::istream &tok, Matrica<Tip> &mat){
    for(int i = 0; i < mat.br_redova; i++){
        for(int j = 0; j < mat.br_kolona; j++){
            std::cout<<mat.ime_matrice<<"("<<i + 1<<","<<j + 1<<") = ";
            tok>>mat.elementi[i][j];
        }
    }
    return tok;
}

template <typename Tip>
std::ostream &operator<<(std::ostream &tok, Matrica<Tip> &mat){
    int sirina_ispisa = tok.width();
    for(int i = 0; i < mat.br_redova; i++){
        for(int j = 0; j < mat.br_kolona; j++)
            tok<<std::setw(sirina_ispisa)<<mat.elementi[i][j];
                tok<<std::endl;
    }
    return tok;
}

template <typename Tip>
Matrica <Tip> operator+(const Matrica<Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
    for(int i = 0; i <m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
            return m3;
}

template <typename Tip>
Matrica <Tip> operator-(const Matrica<Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
    for(int i = 0; i <m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
            return m3;
}

template <typename Tip>
Matrica<Tip> operator*(const Matrica<Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_kolona != m2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    Matrica<Tip> m3(m1.br_redova, m2.br_redova);
    for(int i = 0; i < m1.br_redova; i++){
        for(int j = 0; j < m2.br_kolona; j++){
            Tip s = 0;
            for(int k = 0; k < m2.br_redova; k++)
            s += m1.elementi[i][k] * m2.elementi[k][j];
            m3.elementi[i][j] = s;

        }
    }
    return m3;
}

template <typename Tip, typename T2>
Matrica<Tip> operator*(const Matrica<Tip> &m1, T2 broj){
    Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] * broj;
            return m3;
}

template <typename Tip, typename T2>
Matrica<Tip> operator*(T2 broj, const Matrica<Tip> &m1){
    Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] * broj;
            return m3;
}

template <typename Tip>
Matrica<Tip> &operator +=(Matrica <Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    m1 = m1 + m2;
    return m1;
}


template <typename Tip>
Matrica<Tip> &operator -=(Matrica <Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
    m1 = m1 - m2;
    return m1;
}

template <typename Tip>
Matrica<Tip> &operator *=(Matrica<Tip> &m1, const Matrica<Tip> &m2){
    if(m1.br_kolona != m2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
    m1 = m1 * m2;
}

template <typename Tip>
Matrica<Tip> &operator *=(Matrica<Tip> &m1, double broj){
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m1.elementi[i][j] = m1.elementi[i][j] * broj;
    return m1;
}

template <typename Tip>
Matrica<Tip> &operator *=(double broj, Matrica<Tip> &m1){
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m1.elementi[i][j] = m1.elementi[i][j] * broj;
    return m1;
}

template <typename Tip>
Matrica<Tip>::operator std::string() const{
    std::string novi;
    novi.push_back('{');
    for(int i = 0; i < br_redova; i++){
        novi.push_back('{');
        for(int j = 0; j < br_kolona; j++){
            int cifra(elementi[i][j]);
            std::string temp;
            while(cifra != 0){
                temp.push_back((cifra % 10)+ '0');
                cifra /= 10;
            }
            for(int k = temp.size() - 1; k >= 0; k--){
                novi.push_back(temp[k]);
            }
            if(j != br_kolona - 1){
                novi.push_back(',');
            }
        }
        novi.push_back('}');
        if(i != br_redova - 1){
            novi.push_back(',');
        }
    }
    novi.push_back('}');
    return novi;
}




int main ()
{


	return 0;
}
