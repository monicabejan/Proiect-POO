#include "../include/hotel.h"
#include "../include/angajat.h"
#include "../include/exceptii.h"
#include "../include/rezervare.h"
#include <iostream>
#include <algorithm>
#include <numeric>

Angajat::Angajat(const std::string& n, const std::string& user, const std::string& p, double sal) {}
Angajat::Angajat(const Angajat& other) : nume(other.nume), username(other.username), parola(other.parola), salariu(other.salariu) {}
Angajat& Angajat::operator=(const Angajat& other){
    if(this!=&other){
        nume=other.nume;
        username=other.username;
        parola=other.parola;
        salariu=other.salariu;
    }
    return *this;
}

bool Angajat::verificaParola(const std::string& p) const{return parola == p;}
const std::string& Angajat::getUsername() const { return username;}
const std::string& Angajat::getNume() const { return nume;}
double Angajat::getSalariu() const { return salariu;}

std::ostream& operator<<(std::ostream& os, const Angajat& a){
    os<<a.getRol()<<" "<<a.nume<<" @"<<a.username;
    return os;
}

std::istream& operator>>(std::istream& is, Angajat& a){
    std::cout<<"\nNume: ";
    is>>a.nume;
    std::cout<<"\nUsername: "; //exceptie 
    is>>a.username;
    std::cout<<"\nParola: ";
    is>>a.parola;
    std::cout<<"\nSalariu: ";
    is>>a.salariu;
    if(a.salariu <=0) throw ExceptiePretInvalid(a.salariu);
    return is;
}

AngajatFrontDesk::AngajatFrontDesk(const std::string& n, const std::string& user, const std::string& p, double sal) :
        Angajat(n, user, p ,sal), nrCheckinuri(0) {}
AngajatFrontDesk::AngajatFrontDesk(const AngajatFrontDesk& other): Angajat(other), nrCheckinuri(other.nrCheckinuri) {}
AngajatFrontDesk& AngajatFrontDesk::operator=(const AngajatFrontDesk& other)
{
    if(this!=&other){
        Angajat::operator=(other);
        nrCheckinuri=other.nrCheckinuri;
    }
    return *this;
}

void AngajatFrontDesk::afiseazaMeniu(hotel *h){
    int optiune=0;
    do{
        std::cout<<"\nFRONT DESK\n";
        std::cout<<"\n0. Logout\n";
        std::cout<<"\n1. Camere disponibile\n";
        std::cout<<"\n2. Rezervare client\n";
        std::cout<<"\n3. Istoric rezervari\n";
        std::cout<<"\n4. Total incasari\n";
        std::cout<<"\nOptiune: \n";
        if(std::cin>>optiune){
            try{
                switch(optiune){
                    case 0:
                    break;

                    case 1:
                    h->afisareCamereLibere();
                    break;

                    case 2:
                    {
                    std::string nume;
                    std::cout<<"\nNume client: ";
                    std::cin>>nume;
                    rezervare sesiune(nume);
                    int nrCam;
                    do{
                        h->afisareCamereLibere();
                        std::cout<<"\nNr camera de rezervat (0 pentru finalizare): ";
                        std::cin>>nrCam;
                        if(nrCam)
                        {
                            try{
                                h->rezervaCameraInSesiune(sesiune, nrCam);
                                inregistreazaCheckin();
                            }catch(const ExceptieCamera& e){
                                std::cout<<"Eroare: "<<e.what()<<"\n";
                            }
                        }
                    }while(nrCam!=0);
                    try{
                        h->finalizeazaRezervare(sesiune);
                    }catch(const ExceptieRezervareInvalida& e){
                        std::cout<<"Eroare: "<<e.what()<<"\n";
                    }
                    break;
                    }
                     case 3:
                     h->afisareIstoricRezervari();
                     break;

                     case 4:
                    // h->afisareTotalIncasari();
                     break;
                     
                     default:
                     std::cout<<"Optiune invalida\n";
            }
        }catch(const ExceptieHotel& e){
            std::cout<<"Eroare "<<e.what()<<"\n";
        }
        }
    }while(optiune);
}

AngajatHousekeeping::AngajatHousekeeping(const std::string& n, const std::string& user, const std::string& p, double sal):
        Angajat(n, user, p, sal), nrCamereAsignate(0) {}
AngajatHousekeeping::AngajatHousekeeping(const AngajatHousekeeping& other): Angajat(other), nrCamereAsignate(other.nrCamereAsignate) {}
AngajatHousekeeping& AngajatHousekeeping::operator=(const AngajatHousekeeping& other){
    if(this!=&other){
        Angajat::operator=(other);
        nrCamereAsignate=other.nrCamereAsignate;
    }
    return *this;
}
void AngajatHousekeeping::marcheazaInCuratenie(hotel* h, int nrCamera){
    //h->ocupaCamera(nrCamera);
    ++nrCamereAsignate;
}

void AngajatHousekeeping::afiseazaMeniu(hotel *h){
    int optiune=0;
    do{
        std::cout<<"\nHOUSEKEEPING\n";
        std::cout<<"0. Logout\n";
        std::cout<<"1. Toate camerele\n";
        std::cout<<"2. Marcheaza camera in curatenie\n";
        std::cout<<"3. Marcheaza camera curata\n";
        std::cout<<"Optiune: ";

        if(std::cin>>optiune){
            try{
                switch(optiune){
                    case 0:
                    break;

                    case 1:
                    h->afisareCamereLibere();
                    break;

                    case 2:
                    {
                        int nr;
                        std::cout<<"\nNr. camera: ";
                        std::cin>>nr;
                        marcheazaInCuratenie(h, nr);
                        break;
                    }
                    case 3:
                    {
                        int nr;
                        std::cout<<"\nNr. camera: ";
                        std::cin>>nr;
                        //h->elibereazaCamera(nr);
                        break;
                    }
                    default:
                    std::cout<<"Optiune invalida";
                }
            }catch(const ExceptieHotel& e){
                std::cout<<"\nEroare "<<e.what()<<"\n";
            }
        }
    }while(optiune);
}