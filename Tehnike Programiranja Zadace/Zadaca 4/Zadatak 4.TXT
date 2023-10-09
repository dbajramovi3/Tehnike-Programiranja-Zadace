//TP 2022/2023: Zadaća 4, Zadatak 4
#include <cstdint>
#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <stdexcept>

class Korisnik{

    private:
        int clanski_broj;
        std::string ime_i_prezime;
        std::string adresa;
        std::string broj_telefona;

    public:
        Korisnik(int cb, std::string imeprez, std::string adr, std::string brtel) : clanski_broj(cb), ime_i_prezime(imeprez), adresa(adr), broj_telefona(brtel) {}

        int DajClanskiBroj() const{
            return clanski_broj;
        }

        std::string DajImeIPrezime() const{
            return ime_i_prezime;
        }

        std::string DajAdresu() const{
            return adresa;
        }

        std::string DajBrojTelefeona() const{
            return broj_telefona;
        }

        void Ispisi(){
            std::cout<<"Clanski broj: "<<clanski_broj<<std::endl;
            std::cout<<"Ime i prezime: "<<ime_i_prezime<<std::endl;
            std::cout<<"Adresa: "<<adresa<<std::endl;
            std::cout<<"Telefon: "<<broj_telefona<<std::endl;
        }
};

    class Film{
    
            int evidencijski_broj;
            bool provjeraDVD;
            Korisnik *k;
            std::string naziv;
            std::string zanr;
            int godina_produkcije;

        public:
        Film(int evidencijski_broj, bool provjeraDVD, std::string naziv, std::string zanr, int godina) : evidencijski_broj(evidencijski_broj), provjeraDVD(provjeraDVD), naziv(naziv), zanr(zanr), godina_produkcije(godina), k(nullptr) {}

        int DajEvidencijskiBroj() const{
            return evidencijski_broj;
        }

        std::string DajNaziv() const{
            return naziv;
        }

        std::string DajZanr() const{
            return zanr;
        }

        int DajGodinuProdukcije() const{
            return godina_produkcije;
        }

        bool DaLiJeDVD() const{
            return provjeraDVD;
        }

        void ZaduziFilm(Korisnik &korisnik){
          if(!(this -> k))
        this -> k = &korisnik;
        else
          throw std::logic_error("Film vec zaduzen");
        }

        void RazduziFilm(){
            k = nullptr;
        }

        bool DaLiJeZaduzen() const {
            return this -> k != nullptr;
        }
        
       Korisnik DajKodKogaJe() const{
            if(k == nullptr){
                throw std::domain_error("Film nije zaduzen");
            }
            return *k;
        }

        Korisnik *DajPokKodKogaJe() const{
            return k;
        }

        void Ispisi() const{
            std::cout<<"Evidencijski broj: "<<evidencijski_broj<<std::endl;
            std::cout<<"Medij: ";
            if(provjeraDVD){
                std::cout<<"DVD";
            }else{
                std::cout<<"Video traka";
            }
            std::cout<<std::endl;
            std::cout<<"Naziv filma: "<<naziv<<std::endl;
            std::cout<<"Zanr: "<<zanr<<std::endl;
            std::cout<<"Godina produkcije: "<<godina_produkcije<<std::endl;
        }
    };


    class Videoteka{
       
            std::map<int, std::shared_ptr<Korisnik>> korisnici;
            std::map<int, std::shared_ptr<Film>> filmovi;

        public:
        Videoteka(){}
        Videoteka(const Videoteka &videoteka){
            for(auto it = videoteka.filmovi.begin(); it != videoteka.filmovi.end(); it++){
                filmovi[it -> first] = std::make_shared<Film>(*it -> second);
            } 
            for(auto it = videoteka.korisnici.begin(); it != videoteka.korisnici.end(); it++){
                korisnici[it -> first] = std::make_shared<Korisnik>(*it -> second);
            }
        }

      Videoteka(Videoteka &&videoteka){
            std::swap(filmovi, videoteka.filmovi);
            std::swap(korisnici, videoteka.korisnici);
        }

           Videoteka &operator = (const Videoteka &videoteka){
            for(auto it = videoteka.filmovi.begin(); it != videoteka.filmovi.end(); it++){
                filmovi[it -> first] = std::make_shared<Film>(*it -> second);
            }
             for(auto it = videoteka.korisnici.begin(); it != videoteka.korisnici.end(); it++){
                korisnici[it -> first] = std::make_shared<Korisnik>(*it -> second);
            }
            return *this;
        }

        Videoteka &operator = (Videoteka &&videoteka){
            std::swap(filmovi, videoteka.filmovi);
            std::swap(korisnici, videoteka.korisnici);
            return *this;
        }

        ~Videoteka(){
            for(auto it = filmovi.begin(); it != filmovi.end(); it++){
                it -> second = nullptr;
            }
            for(auto it = korisnici.begin(); it != korisnici.end(); it++){
                it -> second = nullptr;
            }
        }

      
        void RegistrirajNovogKorisnika(int clanski_broj, std::string ime_prezime, std::string adresa, std::string broj_telefona){
       if(korisnici.find(clanski_broj) != korisnici.end()){
               throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
       }
           korisnici[clanski_broj] = std::make_shared<Korisnik>(clanski_broj, ime_prezime, adresa, broj_telefona);
         
}


    void RegistrirajNoviFilm(int evidencijski_broj, bool dvd, std::string naziv, std::string zanr, int godina){
        if(filmovi.find(evidencijski_broj) != filmovi.end()){
            throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
        }
       filmovi[evidencijski_broj] = std::make_shared<Film>(evidencijski_broj, dvd, naziv, zanr,godina);

    }

    Korisnik &NadjiKorisnika(int clanski_broj){
        if(korisnici.find(clanski_broj) != korisnici.end())
        return *korisnici.find(clanski_broj) -> second;
        throw std::logic_error("Korisnik nije nadjen");
    }

    Korisnik NadjiKorisnika(int clanski_broj) const{
        if(korisnici.find(clanski_broj) != korisnici.end())
        return *korisnici.find(clanski_broj) -> second;
        throw std::logic_error("Korisnik nije nadjen");
    }

    Film &NadjiFilm(int evidencijski_broj){
        if(filmovi.find(evidencijski_broj) != filmovi.end())
        return *filmovi.find(evidencijski_broj) -> second;
        throw std::logic_error("Film nije nadjen");
    }

    Film NadjiFilm(int evidencijski_broj) const{
        if(filmovi.find(evidencijski_broj) != filmovi.end())
        return *filmovi.find(evidencijski_broj) -> second;
        throw std::logic_error("Film nije nadjen");
    }

    void IzlistajKorisnike(){
        for(auto it = korisnici.begin(); it != korisnici.end(); it++){
            (*it -> second).Ispisi();
        }
    }

    void IzlistajFilmove(){
        for(auto it = filmovi.begin(); it != filmovi.end(); it++){
            (*it -> second).Ispisi();
            std::cout<<std::endl;
            if((*it -> second).DaLiJeZaduzen()){
                auto l = (*it -> second).DajKodKogaJe();
                std::cout<<"Zaduzen kod korisnika: "<<l.DajImeIPrezime()<<" ("<<l.DajClanskiBroj()<<")"<<std::endl;
            }
        }
    }

    void ZaduziFilm(int clanski_broj, int evidencijski_broj){

        auto user = korisnici.find(clanski_broj);
        auto movie = filmovi.find(evidencijski_broj);

        if(korisnici.find(clanski_broj) == korisnici.end() || filmovi.find(evidencijski_broj) == filmovi.end())
        throw std::domain_error("Film nije nadjen");

        if((*movie -> second).DaLiJeZaduzen())
        throw std::domain_error("Film vec zaduzen");

        Korisnik *pok = nullptr;
        for(auto it = korisnici.begin(); it != korisnici.end(); it++){
            if((*it -> second).DajClanskiBroj() == clanski_broj){
                pok = &(*it -> second);
                break;
            }
        }
        for(auto it = filmovi.begin(); it != filmovi.end(); it++){
            if((*it -> second).DajPokKodKogaJe() == pok){
                throw std::domain_error("Korisnik je vec zaduzio film");
            }
        }
        (*movie -> second).ZaduziFilm((*user -> second));
    }

    void RazduziFilm(int evbroj){
        if(filmovi.end() == filmovi.find(evbroj))
        throw std::domain_error("Film nije nadjen");
        (*filmovi.find(evbroj) -> second).RazduziFilm();
    }

    void PrikaziZaduzenja(int clanski_broj){
        auto nemaZaduzenje(true);
        if(filmovi.size() == 0){
            throw std::domain_error("Korisnik nema zaduzenja!");
        }
        for(auto it = filmovi.begin(); it != filmovi.end(); it++){
            if((*it -> second).DaLiJeZaduzen()){
                nemaZaduzenje = false;
                auto p = (*it -> second).DajPokKodKogaJe();
                if(p -> DajClanskiBroj() == clanski_broj)
                (*it -> second).Ispisi();
            }
        }
        if(nemaZaduzenje)
        throw std::domain_error("Korisnik nema zaduzenja");
    }
};
int main ()
{


	return 0;
}
