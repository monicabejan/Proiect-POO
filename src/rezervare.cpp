#include <vector>
#include <iostream>
#include <numeric>

#include "../include/rezervare.h"
#include "../include/exceptii.h"



int rezervare::contorID=0;

rezervare::rezervare(const std::string& nume, int nopti) : numeClient(nume), nrNopti(nopti){
    if(nopti<=0) throw ExceptieRezervareInvalida("Nr de nopti invalid");
    idRezervare=++contorID;
}

rezervare::rezervare(const rezervare& other) : idRezervare(other.idRezervare), numeClient(other.numeClient), nrNopti(other.nrNopti), camereRezervate(other.camereRezervate),serviciiAditionale(other.serviciiAditionale) {}
rezervare& rezervare::operator=(const rezervare& other){
    if(this!=&other){
        idRezervare=other.idRezervare;
        numeClient=other.numeClient;
        camereRezervate=other.camereRezervate;
        serviciiAditionale=other.serviciiAditionale;
        nrNopti=other.nrNopti;
    }
    return *this;
}
rezervare::~rezervare() {}
[[maybe_unused]] const std::string& rezervare::getNumeClient() const{
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
        total+=c->getPret()*nrNopti;
    for(const auto& s : serviciiAditionale)
        total+=s->calculeazaCost();
    return total;
}

void rezervare::afiseazaSumar() const{
    std::cout<<"\nRezervarea #"<<idRezervare;
    std::cout<<"\nClient: "<<numeClient<<std::endl;
    std::cout<<"\nNopti: "<<nrNopti<<std::endl;
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