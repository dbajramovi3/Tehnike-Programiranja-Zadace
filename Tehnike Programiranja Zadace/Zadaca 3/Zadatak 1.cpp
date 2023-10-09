//TP 2022/2023: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

double F(double x){
    double rezultat = log(x+1) + sin(x) + x * x;
    return rezultat;
}

bool KoordinatiProvjera(const std::vector<std::pair<double, double>> &vec){
    for(int i = 0; i < vec.size(); i++){
        for(int j = i + 1; j < vec.size(); j++){
            if(vec.at(i).first == vec.at(j).first){
                return false;
            }
        }
    }
    return true;
}

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double, double>> vector){
    return [vector](double x){
        if(!KoordinatiProvjera(vector)){
            throw std::domain_error("Neispravni cvorovi");
        }
        double br, naz;
        double suma = 0;
        for(int i = 0; i < vector.size(); i++){
            br = 1; naz = 1;
            for(int j = 0; j<vector.size(); j++){
                if(i != j){
                    br *= (x - vector.at(j).first);
                    naz *= (vector.at(i).first - vector.at(j).first);
                        }
            }
            suma += (br/naz) * vector.at(i).second;
        }
        return suma;
    };
}

std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)> f, double xmin, double xmax, double delta){
    if(xmin > xmax){
        throw std::domain_error("Nekorektni parametri");
    }
    else if(delta <= 0){
        throw std::domain_error("Nekorektni parametri");
    }
    std::vector<std::pair<double, double>> vector;
    while(1){
        if(xmin > xmax) break;
        vector.push_back(std::make_pair(xmin, f(xmin)));
        xmin += delta;
    }
    return LagrangeovaInterpolacija(vector);
}

int main (){
    int jedan_ili_dva;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>jedan_ili_dva;
    //prvo cemo uraditi sta ako se unese 1
    if(jedan_ili_dva == 1){
        std::vector<std::pair<double, double>> vector;
        std::cout<<"Unesite broj cvorova: ";
        int broj_cvorova;
        std::cin>>broj_cvorova;
        if(broj_cvorova <= 0){
            std::cout<<"Broj cvorova mora biti pozitivan broj!";
            return 0;
        }
        std::cout<<"Unesite cvorove kao parove x y: ";
        try{
            for(int i = 1; i <= broj_cvorova; i++){
                double x, y;
                std::cin>>x>>y;
                vector.push_back(std::make_pair(x,y));
                if(!KoordinatiProvjera(vector)){
                    throw std::domain_error("Neispravni cvorovi");
                }
            }
        }catch(...){
            std::cout<<"Neispravni cvorovi";
            return 0;
        }
        int minimum = vector.at(0).first;
        int maximum = vector.at(0).first;
        for(int i = 0; i < vector.size(); i++){
            if(vector.at(i).first < minimum){
                minimum = vector.at(i).first;
            }
            if(vector.at(i).first > maximum){
                maximum = vector.at(i).first;
            }
        }
        auto fu = LagrangeovaInterpolacija(vector);
        do{
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
           double argument;
           if(!(std::cin>>argument)){
               break;
           } 
           if(argument <= maximum && argument >= minimum){
               std::cout<<"f("<<argument<<") = "<<fu(argument)<<"\n";
           }
           else {
           auto P = LagrangeovaInterpolacija(F, minimum, maximum, (maximum - minimum)/broj_cvorova);
           std::cout<<"f("<<argument<<") = "<<fu(argument)<<" [ekstrapolacija]\n";
           }
        }while(1);
    }
    //Kada se unosi 2 
    else if(jedan_ili_dva == 2){
        std::vector<std::pair<double, double>> vector2;
        std::cout<<"Unesite krajeve intervala i korak: ";
        double xmin, xmax, delta;
        try{
            std::cin>>xmin>>xmax>>delta;
            if(xmin > xmax){
                throw std::domain_error("Nekorektni parametri");
            }
            else if(delta <= 0){
                throw std::domain_error("Nekorektni parametri");
            }
        }catch(std::domain_error e){
            std::cout<<e.what();
            return 0;
        }
        auto minx(xmin);
        while(1){
            if(minx > xmax){
                break;
            }
            vector2.push_back(std::make_pair(minx, F(minx)));
            minx += delta;
        }
        auto minimum = vector2.at(0).first;
        auto maximum = vector2.at(vector2.size() - 1).first;
        do{
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            double argumentx;
            if(!(std::cin>>argumentx)){
                break;
            }
            auto fx = LagrangeovaInterpolacija(vector2);
            auto fy = LagrangeovaInterpolacija(F, xmin, xmax, delta);
            std::cout<<"f("<<argumentx<<") = "<<F(argumentx);
            if(argumentx <= maximum && argumentx >= minimum){
                std::cout<<" P("<<argumentx<<") = "<<fx(argumentx)<<"\n";
            }
            else{
                std::cout<<" P("<<argumentx<<") = "<<fy(argumentx)<<" [ekstrapolacija]\n";
            }
        }while(1);
    }else{
        std::cout<<"Nepoznato";
    }
	return 0;
}
