//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <complex>

void BaciIzuzetak(){
    std::domain_error("Neispravan naziv parametra");
}

class Sinusoida{
    double vrijednost_A, vrijednost_fi, omega;
public:
Sinusoida(double vrijednost_A, double omega, double vrijednost_fi);

std::tuple<double, double, double> DajParametre() const{
    return std::make_tuple(vrijednost_A, omega, vrijednost_fi);
}

double DajAmplitudu();
double DajFrekvenciju();
double DajFazu();

Sinusoida& PostaviAmplitudu(double vr);
Sinusoida& PostaviFrekvenciju(double vr);
Sinusoida& PostaviFazu(double vr);
Sinusoida& PostaviParametre(std::tuple<double, double, double> parametri);

friend Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2);
friend Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2);

friend Sinusoida operator *(const Sinusoida &s1, double broj);
friend Sinusoida operator /(const Sinusoida &s1, double broj);

Sinusoida &operator +=(const Sinusoida &s);
Sinusoida &operator -=(const Sinusoida &s);
Sinusoida &operator *=(const double broj);
Sinusoida &operator /=(const double broj);

friend Sinusoida operator -(const Sinusoida &s){
    return Sinusoida(-s.vrijednost_A, s.omega, s.vrijednost_fi);
}

double operator [](const char *c) const;
double operator ()(double var);
double &operator [](const char *c);

};

double Sinusoida::DajAmplitudu(){
    return vrijednost_A;
}

double Sinusoida::DajFrekvenciju(){
    return omega;
}

double Sinusoida::DajFazu(){
    return vrijednost_fi;
}


Sinusoida::Sinusoida(double A, double W, double Fi){
    if(A < 0){
        A = abs(A);
    Fi = Fi + (4 * atan(1.));
}
    if(W < 0){
        W = abs(W);
        Fi = Fi + (4 * atan(1.)); 
    }

    Fi = atan2(sin(Fi), cos(Fi));
    vrijednost_A = A;
    omega = W;
    vrijednost_fi = Fi;

}

Sinusoida& Sinusoida::PostaviAmplitudu(double vr){
    if(vr < 0){
        vr = abs(vr);
        vrijednost_fi = vrijednost_fi + (4 * atan(1.));
    }
    vrijednost_fi = atan2(sin(vrijednost_fi), cos(vrijednost_fi));
    vrijednost_A = vr;
    return *this;
}

Sinusoida& Sinusoida::PostaviFrekvenciju(double vr){
    if(vr < 0){
        vr = abs(vr);
        vrijednost_fi = -vrijednost_fi + (4 * atan(1.));
    }
    vrijednost_fi = atan2(sin(vrijednost_fi), cos(vrijednost_fi));
    omega = vr;
    return *this;
}

Sinusoida& Sinusoida::PostaviFazu(double vr){
    vrijednost_fi = atan2(sin(vr), cos(vr));
    return *this;
}

Sinusoida& Sinusoida::PostaviParametre(std::tuple<double, double, double> parametri){
    double vrijednost_A = std::get<0>(parametri);
    double omega = std::get<1>(parametri);
    double vrijednost_fi = std::get<2>(parametri);
    PostaviAmplitudu(vrijednost_A);
    PostaviFrekvenciju(omega);
    PostaviFazu(vrijednost_fi);
    return *this;
}

Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2){
    if(fabs(s1.omega - s2.omega) > 0.0000000001){
        throw std::domain_error("Razlicite frekvencije");
    }
    std::complex<double> s3;
    s3 = s1.vrijednost_A * std::exp(std::complex<double>(0, s1.vrijednost_fi)) + s2.vrijednost_A * std::exp(std::complex<double>(0, s2.vrijednost_fi));
    return Sinusoida(abs(s3), s1.omega, arg(s3));
}

Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2){
    if(fabs(s1.omega - s2.omega) > 0.0000000001){
        throw std::domain_error("Razlicite frekvencije");
    }
    std::complex<double> s3;
    s3 = s1.vrijednost_A * std::exp(std::complex<double>(0, s1.vrijednost_fi)) - s2.vrijednost_A * std::exp(std::complex<double>(0, s2.vrijednost_fi));
    return Sinusoida(abs(s3), s1.omega, arg(s3));
}

Sinusoida operator *(const Sinusoida &s, double broj){
    return Sinusoida(s.vrijednost_A * broj, s.omega, s.vrijednost_fi);
}

Sinusoida operator *(double broj, const Sinusoida &s){
    return s * broj;
}

Sinusoida operator /(const Sinusoida &s, double broj){
    return Sinusoida(s.vrijednost_A / broj, s.omega, s.vrijednost_fi);
}

Sinusoida operator /(double broj, const Sinusoida &s){
    return s / broj;
}

Sinusoida &Sinusoida::operator +=(const Sinusoida &s){
    if(fabs(omega - s.omega) > 0.0000000001){
        std::domain_error("Razlicite frekvencije");
    }
    vrijednost_A += s.vrijednost_A;
    return *this;
}

Sinusoida &Sinusoida::operator -=(const Sinusoida &s){
    if(fabs(omega - s.omega) > 0.0000000001){
        std::domain_error("Razlicite frekvencije");
    }
    vrijednost_A -= s.vrijednost_A;
    return *this;
}

Sinusoida &Sinusoida::operator *=(const double broj){
    vrijednost_A *= broj;
    return *this;
}

Sinusoida &Sinusoida::operator /=(const double broj){
    vrijednost_A /= broj;
    return *this;
}

Sinusoida operator -(Sinusoida &s){
    return Sinusoida(-s.DajAmplitudu(), s.DajFrekvenciju(), s.DajFazu());
}

double Sinusoida::operator ()(double var){
    return vrijednost_A * sin(omega * var + vrijednost_fi);
}   

double Sinusoida::operator[](const char *c) const{
    std::string var = c;
    if(var == "A"){
        return vrijednost_A;
    }
    else if(var == "omega"){
        return omega;
    }
    else if(var =="vrijednost_fi"){
        return vrijednost_fi;
    }
    else{
        BaciIzuzetak();
    }
}

double &Sinusoida::operator[](const char *c){
    std::string var = c;
    if(var == "A"){
        return vrijednost_A;
    }
    else if(var == "omega"){
        return omega;
    }
    else if(var =="vrijednost_fi"){
        return vrijednost_fi;
    }
    else{
        BaciIzuzetak();
    }
}



int main ()
{


	return 0;
}
