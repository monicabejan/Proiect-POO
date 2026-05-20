#include <iostream>
#include <vector>
#include <functional>

#include "../include/serviciu.h"
#include "../include/exceptii.h"


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



ServiciuLaundry::ServiciuLaundry(int nr, double pretPerPiesa):Serviciu("Laundry x"+std::to_string(nr), pretPerPiesa),nrPiese(nr) {}

ServiciuLaundry::ServiciuLaundry(const ServiciuLaundry& other):Serviciu(other), nrPiese(other.nrPiese){}


double ServiciuLaundry::calculeazaCost() const{
    return pretServiciu*nrPiese;
}



ServiciuRoomService::ServiciuRoomService(const std::string& cmd, bool urg, double pret) : Serviciu("Room Service "+cmd, pret), comanda(cmd), urgent(urg){}
ServiciuRoomService::ServiciuRoomService( const ServiciuRoomService& other):Serviciu(other),comanda(other.comanda), urgent(other.urgent) {}


double ServiciuRoomService::calculeazaCost() const{
    return urgent ? pretServiciu*2.0 : pretServiciu;
}



ServiciuSpa::ServiciuSpa(int durata, double pretPerMinut):Serviciu("Spa "+std::to_string(durata)+"min",pretPerMinut),durataMasaj(durata) {}
ServiciuSpa::ServiciuSpa(const ServiciuSpa& other) : Serviciu(other), durataMasaj(other.durataMasaj) {}


double ServiciuSpa::calculeazaCost() const{
    return pretServiciu*durataMasaj;
}