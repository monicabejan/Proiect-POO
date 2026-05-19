#ifndef VALUTA_H
#define VALUTA_H

#include <iostream>
#include <string>

template <typename T = double>
class Valuta{
    T valoare;
    std::string simbolMoneda;
public:
    Valuta() : valoare(0), simbolMoneda("RON") {}
    Valuta( T val, const std::string& sim): valoare(val), simbolMoneda(sim) {}
    Valuta(const Valuta& other) : valoare(other.valoare), simbolMoneda(other.simbolMoneda){}
    Valuta& operator=(const Valuta& other){
        if(this!=&other){
            valoare=other.valoare;
            simbolMoneda=other.simbolMoneda;
        }
        return *this;
    }
    ~Valuta()=default;

    T getValoare() const { return valoare;}
    std::string getSimbol() const { return simbolMoneda;}

    Valuta& operator+=(const Valuta& other){
        if(this->simbolMoneda == other.simbolMoneda){
            this->valoare += other.valoare;
        }
        else{
            std::cout<<"\nNu se pot aduna "<<this->simbolMoneda<<" si "<<other.simbolMoneda<<"\n";

        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Valuta<T>& v){
        os<<v.valoare<<" "<<v.simbolMoneda;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Valuta<T>& v){
        std::cout<<"\nSuma: "; is>>v.valoare;
        std::cout<<"\nMoneda: "; is>>v.simbolMoneda;
        return is;
    }
};

template <typename T>
Valuta<T> operator+(const Valuta<T>& a, const Valuta<T>& b){
    if(a.getSimbol() != b.getSimbol()){
        std::cout<<"\nInvalid - Monedele nu coincid\n";
        return Valuta<T>(0,"err");
    }
    return Valuta<T>(a.getValoare()+b.getValoare(), a.getSimbol());
}

#endif