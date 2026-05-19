#include "../include/serviciu.h"
#include "../include/exceptii.h"
#include <iostream>
#include <vector>
#include <functional>

std::vector<std::function<void(const std::string&)>>Serviciu::observatori;

Serviciu::Serviciu(const std::string& den, double pret): denumire(den), pretServiciu(pret){
    if(pret<0)
        throw ExceptiePretInvalid(pret);
}

double Serviciu::calculeazaCost() const { return pretServiciu;}
bool Serviciu::operator==(const Serviciu& other) const{
    return denumire==other.denumire;
}
std::ostream& operator<<(std::ostream& os, const Serviciu& s){
    os<<s.getTip()<<" "<<s.denumire<<" "<<s.calculeazaCost()<<" RON";
    return os;
}
void Serviciu::inregistreazaObservator(std::function<void(const std::string&)>obs){
    observatori.push_back(std::move(obs));

}

void Serviciu::notificaObservatori(const std::string& mesaj){
    for(const auto& obs: observatori)
        obs(mesaj);
}

ServiciuLaundry::ServiciuLaundry(int nr, double pretPerPiesa):Serviciu("Laundry x"+std::to_string(nr), pretPerPiesa),nrPiese(nr) {}

ServiciuLaundry::ServiciuLaundry(const ServiciuLaundry& other):Serviciu(other), nrPiese(other.nrPiese){}
ServiciuLaundry& ServiciuLaundry::operator=(const ServiciuLaundry& other){
    if(this!=&other)
    {
        Serviciu::operator=(other);
        nrPiese=other.nrPiese;
    }
    return *this;

}


void ServiciuLaundry::executa() const {
    std::cout<<"Se proceseaza "<<nrPiese<<" piese la spalatorie.\n";
    notificaObservatori("Laundry activat: "+denumire);
}

double ServiciuLaundry::calculeazaCost() const{
    return pretServiciu*nrPiese;
}



ServiciuRoomService::ServiciuRoomService(const std::string& cmd, bool urg, double pret) : Serviciu("Room Service "+cmd, pret), comanda(cmd), urgent(urg){}
ServiciuRoomService::ServiciuRoomService( const ServiciuRoomService& other):Serviciu(other),comanda(other.comanda), urgent(other.urgent) {}

ServiciuRoomService& ServiciuRoomService::operator=(const ServiciuRoomService& other){
    if(this!=&other){
        Serviciu::operator=(other);
        comanda=other.comanda;
        urgent=other.urgent;
    }
    return *this;
}


void ServiciuRoomService::executa() const{
    std::cout<<"Room Service "<<(urgent ? "URGENT" : "")<<": "<<comanda<<"\n";
    notificaObservatori("RoomService activat: "+comanda);
}

double ServiciuRoomService::calculeazaCost() const{
    return urgent ? pretServiciu*2.0 : pretServiciu;
}



ServiciuSpa::ServiciuSpa(int durata, double pretPerMinut):Serviciu("Spa "+std::to_string(durata)+"min",pretPerMinut),durataMasaj(durata) {}
ServiciuSpa::ServiciuSpa(const ServiciuSpa& other) : Serviciu(other), durataMasaj(other.durataMasaj) {}
ServiciuSpa& ServiciuSpa::operator=(const ServiciuSpa& other){
    if(this!=&other){
        Serviciu::operator=(other);
        durataMasaj=other.durataMasaj;
    }
    return *this;
}


void ServiciuSpa::executa() const {
    std::cout<<"Sesiune Spa: "<<durataMasaj<<" minute.\n";
    notificaObservatori("Spa activat: "+std::to_string(durataMasaj)+" min");
}

double ServiciuSpa::calculeazaCost() const{
    return pretServiciu*durataMasaj;
}