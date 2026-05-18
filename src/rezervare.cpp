#include "rezervare.h"
#include "serviciu.h"
#include <vector>
#include <iostream>
#include <numeric>

rezervare::rezervare(const std::string& nume) : numeClient(nume){}

rezervare::rezervare(const rezervare& other) : numeClient(other.numeClient), camereRezervate(other.camereRezervate),serviciiAditionale(other.serviciiAditionale) {}
rezervare& rezervare::operator=(const rezervare& other){
    if(this!=&other){
        numeClient=other.numeClient;
        camereRezervate=other.camereRezervate;
        serviciiAditionale=other.serviciiAditionale;
    }
    return *this;
}
rezervare::~rezervare() {}
const std::string& rezervare::getNumeClient() const{
    return numeClient;
}

void rezervare::adaugaCamera(std::shared_ptr<camera> cam){
    camereRezervate.push_back(cam);
}

void rezervare::adaugaServiciu(std::shared_ptr<Serviciu> srv)
{
    serviciiAditionale.push_back(srv);
}

bool rezervare::esteGoala() const{
    return camereRezervate.empty();
}

double rezervare::calculeazaTotal() const{
    double total=0;
    for(const auto& c : camereRezervate)
        total+=c->getPret();
    for(const auto& s : serviciiAditionale)
        total+=s->calculeazaCost();
    return total;
}

void rezervare::afiseazaSumar() const{
    std::cout<<"Client: "<<numeClient<<std::endl;
    std::cout<<"Camere rezervate: ";
    for(const auto& c : camereRezervate)
        std::cout<<c->getNr()<<" ";
    std::cout<<std::endl;
    if(!serviciiAditionale.empty())
    {
        std::cout<<"Servicii aditionale:\n";
        for(const auto& s : serviciiAditionale)
            std::cout<<" "<<*s<<"\n";
    }
    std::cout<<"Total de plata: "<<calculeazaTotal()<<std::endl;

}

bool rezervare::operator==(const rezervare& other) const{
    return numeClient==other.numeClient;
}

std::ostream& operator<<(std::ostream& os, const rezervare& r){
    r.afiseazaSumar();
    return os;
}