#include "rezervare.h"
#include <vector>
#include <iostream>

rezervare::rezervare(const std::string& nume) : numeClient(nume){}

const std::string& rezervare::getNumeClient() const{
    return numeClient;
} 

void rezervare::adaugaCamera(std::shared_ptr<camera> cam){
    camereRezervate.push_back(cam);
}

bool rezervare::esteGoala() const{
    return camereRezervate.empty();
}

double rezervare::calculeazaTotal() const{
    double total=0;
    for(const auto& c : camereRezervate)
    total+=c->getPret();
    return total;
}

void rezervare::afiseazaSumar() const{
    std::cout<<"Client: "<<numeClient<<std::endl;
    std::cout<<"Camere rezervate: ";
    for(const auto& c : camereRezervate)
        std::cout<<c->getNr()<<" ";
    std::cout<<std::endl;
    std::cout<<"Total de plata: "<<calculeazaTotal()<<std::endl;

}