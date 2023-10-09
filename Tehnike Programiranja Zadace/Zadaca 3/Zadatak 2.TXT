//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
using StandardnaBiblioteka = std::map<std::string, std::set<std::tuple<std::string, int, int>>>;

bool NegativeCharBroj(char c){
    if(c >= '0' && c <= '9'){
        return false;
    }
    else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return false;
    }
    return true;
}

std::map<std::string, std::set<std::tuple<std::string, int, int>>> KreirajIndeksPojmova(Knjiga k){
    StandardnaBiblioteka standardna;
    for(auto iter = k.begin(); iter != k.end(); iter++){
        for(auto i = iter -> second.begin(); i != iter -> second.end(); i++){
            for(auto l = 0; l < (*i).length(); l++){
                if((!NegativeCharBroj((*i)[l])) && (l == 0 || NegativeCharBroj((*i)[l-1]))){
            
                    int funct = 0;
                    for(int k = l + 1; k < (*i).length(); k++){
                        if(NegativeCharBroj((*i)[k])){
                            funct = k; break;
                        }
                        if(k == int((*i).length()) - 1){
                            funct = k + 1; break;
                        }
                    }
                    std::string r = (*i).substr(l, funct - l);
                    std::transform(r.begin(), r.end(), r.begin(),::tolower);
                    standardna[r].insert({
                        iter -> first, i - iter -> second.begin() + 1, l
                    });
            
                }
            }
        }
    }
    return standardna;
}

std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(std::string str, std::map<std::string, std::set<std::tuple<std::string, int, int>>> mapa){
    auto it = mapa.find(str);
    if(it == mapa.end()){
        throw std::logic_error("Pojam nije nadjen");
    }
    else{
        return it -> second;
    }
}

void IspisiIndeksPojmova(std::map<std::string, std::set<std::tuple<std::string, int, int>>> nova){
    for(auto it = nova.begin(); it != nova.end(); it++){
        std::cout<<it -> first<<": ";
        int i = 0;
        for(auto h = it -> second.begin(); h != it -> second.end(); h++){
            if(i == it -> second.size() - 1){
                std::cout<<std::get<0>(*h)<<"/"<<std::get<1>(*h)<<"/"<<std::get<2>(*h);
            }else{
                std::cout<<std::get<0>(*h)<<"/"<<std::get<1>(*h)<<"/"<<std::get<2>(*h)<<", ";
            }
            i++;
        }
        std::cout<<"\n";
    }
}


int main (){

    Knjiga k1;
    std::string str;
    do{
        std::cout<<"Unesite naziv poglavlja: ";
        std::getline(std::cin, str);
        int i = 1;
        if(str == "."){
            break;
        }
        std::vector<std::string> vec_stringova;
        for(;;){
            std::cout<<"Unesite sadrzaj stranice "<<i<<": ";
            std::string h;
            std::getline(std::cin, h);
            std::transform(h.begin(), h.end(), h.begin(),::tolower);
            if(h == std::string(".")){
                k1.insert(std::pair<std::string, std::vector<std::string>>(str, vec_stringova));
                break;
            }
            if(h != std::string(".")){
                vec_stringova.push_back(h);
            }
            i++;
        }
    }while(1);

    std::cout<<"\nKreirani indeks pojmova: \n";
    auto nova = KreirajIndeksPojmova(k1);
    IspisiIndeksPojmova(nova);
    do{
        std::cout<<"Unesite rijec: ";
        std::string s;
        std::getline(std::cin, s);
        if(s == std::string(".")){
            break;
        }
        try{
            auto it = PretraziIndeksPojmova(s, nova);
            int i = 0;
            for(auto h = it.begin(); h != it.end(); h++){
                if(i == it.size() - 1){
                    std::cout<<std::get<0>(*h)<<"/"<<std::get<1>(*h)<<"/"<<std::get<2>(*h)<<"\n";
                }else{
                    std::cout<<std::get<0>(*h)<<"/"<<std::get<1>(*h)<<"/"<<std::get<2>(*h)<<" ";
                    }
                i++;
            }
        }catch(std::logic_error e){
            std::cout<<"Unesena rijec nije nadjena!"<<"\n";
        }
    }while(1);
	return 0;
}
