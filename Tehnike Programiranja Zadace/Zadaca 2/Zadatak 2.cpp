//TP 2022/2023: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <limits.h>

void RastavaBroja(int n,  int &p,  int &q){
    p = 1, q = 1;

    if(n == INT_MIN + 1){
        p = n;
        q = 1;
        return;
    }
    else if(n == INT_MAX){
        p = n;
        q = 1;
        return;
    }
    if(n == 0){
        p = 0;
        return;
    }
    if(n < 0){
        p *= -1;
        n *= -1;
    }

    int temp = n;
    
    for(int i = 2; i <= temp/2/2; i++){
        int brojac = 0;
        for(; n % i == 0; n /= i){
            brojac++;
            if(brojac % 2 == 0){
                q *= i;
            }
        }
        if(brojac % 2 == 1){
            p *= i;
        }
    }
}


int main (){
     int p, q, broj;
    std::cout<<"Unesi broj: ";
    std::cin>>broj;
    RastavaBroja(broj, p, q);
    std::cout<<broj<<" = "<<p;
    if(q != 1){
        std::cout<<"*"<<q<<"^2";
    }
    std::cout<<std::endl;
	return 0;
}
