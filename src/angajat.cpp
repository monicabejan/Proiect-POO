#include "../include/angajat.h"
#include "../include/hotel.h"
#include "../include/exceptii.h"
#include "../include/rezervare.h"
#include <iostream>
#include <algorithm>
#include <numeric>

#include <sstream>
#include <memory>

Angajat::Angajat(const std::string& n, const std::string& user, const std::string& p, double sal): nume(n), username(user), parola(p), salariu(sal) {}
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
                     h->afisareTotalIncasari();
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
    h->rezervaCamera(nrCamera);
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
                        h->elibereazaCamera(nr);
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

Manager::Manager(const std::string& n, const std::string& user, const std::string& p, double sal):
Angajat(n, user, p, sal), nrAngajatiSupervizati(0) {}
Manager::Manager(const Manager& other): Angajat(other), nrAngajatiSupervizati(other.nrAngajatiSupervizati) {}
Manager& Manager::operator=(const Manager& other){
    if(this!=&other){
        Angajat::operator=(other);
        nrAngajatiSupervizati=other.nrAngajatiSupervizati;
    }
    return *this;
}
void Manager::afiseazaMeniu(hotel* h){
    int optiune =0;
    do{
        std::cout<<"\nMANAGER\n";
        std::cout<<"0. Logout\n";
        std::cout<<"1. Istoric rezervari\n";
        std::cout<<"2. Lista angajati\n"; //pontaje?
        std::cout<<"3. Statistici\n";
        std::cout<<"Optiune: ";

        if(std::cin>>optiune){
            try{
                switch(optiune){
                    case 0:
                    break;

                    case 1:
                    h->afisareIstoricRezervari();
                    break;

                    case 2:
                    h->afisareAngajati();
                    break;

                    case 3:
                    h->afisareStatistici();
                    break;

                    default:
                    std::cout<<"\nOptiune invalida\n";
                }
            }catch(const ExceptieHotel& e){
                std::cout<<"\nEroare "<<e.what()<<" ";
            }
        }

    }while(optiune);
}


Admin::Admin(const std::string& n, const std::string& user, const std::string& p, double sal) : Angajat(n, user, p, sal) {}
Admin::Admin(const Admin& other): Angajat(other) {}
Admin& Admin::operator=(const Admin& other) {
    if(this!=&other){
        Angajat::operator=(other);
    }
    return *this;
}
void Admin::creeazaCameraInteractiv(hotel* h){
    std::cout<<"\nTip camera: \n";
    std::cout<<"1. Single\n";
    std::cout<<"2. Double\n";
    std::cout<<"3. Penthouse\n";
    std::cout<<"Optiune: ";

    int tip;
    std::cin>>tip;

    int nr, etaj;
    double pret;

    std::cout<<"\nNr. camera: "; std::cin>>nr;
    std::cout<<"\nEtaj: "; std::cin>>etaj;
    std::cout<<"\nPret: "; std::cin>>pret;
    if(pret<=0) throw ExceptiePretInvalid(pret);

    switch(tip){
        case 1:
        h->creeazaCamera<cameraSingle>(nr, etaj, pret);
        std::cout<<"\nA fost creata camera "<<nr<<"\n";
        break;

        case 2:{ 
        std::string config;
        std::cout<<"\nConfiguratie (Twin/Matrimonial): ";
        std::cin>>config;
        h->creeazaCamera<cameraDouble>(nr, etaj, config, pret);
        std::cout<<"\nA fost creata camera "<<nr<<"\n";
        break;
        }
        case 3:{
            int nrDorm;
            std::cout<<"\nNr. dormitoare: ";
            std::cin>>nrDorm;
            h->creeazaCamera<penthouse>(nr, etaj, nrDorm, pret);
            std::cout<<"\nA fost creat Penthouse "<<nr;
            break;
        }
        default:
        std::cout<<"Invalid";
    }

}

void Admin::creeazaAngajatInteractiv(hotel* h){
    std::cout<<"\nRol angajat: "; 
    std::cout<<"\n1. Front desk \n";
    std::cout<<"2. Housekeeping\n";
    std::cout<<"3. Manager\n";
    std::cout<<"Optiune: ";

    int rol;
    std::cin>>rol;

    std::string nume, user, parola;
    double salariu;
    std::cout<<"\nNume: "; std::cin>>nume;
    std::cout<<"\nUsername: "; std::cin>>user;
    std::cout<<"\nParola: "; std::cin>>parola;
    std::cout<<"\nSalariu: "; std::cin>>salariu;

    //if(salariu<=0) throw ExceptionPretInvalid(salariu);
    try{
    switch(rol){
        case 1:
        h->adaugaAngajat(std::make_shared<AngajatFrontDesk>(nume, user, parola, salariu));
        std::cout<<"\n"<<nume<<" lucreaza acum la Front Desk\n";
        break;

        case 2:
        h->adaugaAngajat(std::make_shared<AngajatHousekeeping>(nume, user, parola, salariu));
        std::cout<<nume<<" lucreaza acum la Housekeeping\n";
        break;

        case 3:
        h->adaugaAngajat(std::make_shared<Manager>(nume, user, parola, salariu));
        std::cout<<nume<<" e acum Manager\n";
        break;

        default:
        std::cout<<"\nInvalid\n";
    }
}catch(const std::exception& e){
    std::cout<<"\nWarning "<<e.what()<<"\n";
}
}

void Admin::afiseazaMeniu(hotel* h){
    int optiune=0;
    do{
        std::cout<<"\nADMINISTRATOR\n";
        std::cout<<"0. Logout\n";
        std::cout<<"1. Adauga camera\n";
        std::cout<<"2. Adauga angajat\n";
        std::cout<<"3. Lista angajati\n";
        std::cout<<"4. Total incasari\n";
        std::cout<<"Optiune: ";
        
        std::cin>>optiune;

        try{
            switch(optiune){
                case 0:
                break;

                case 1:
                creeazaCameraInteractiv(h);
                break;

                case 2:
                creeazaAngajatInteractiv(h);
                break;

                case 3:
                //afisareAngajati();
                break;

                case 4:
                h->afisareTotalIncasari();
                break;

                default:
                std::cout<<"Invalid";
            }
        }catch(const std::exception& e){
            std::cout<<"\nEroare: "<<e.what()<<"\n";
        }
    }while(optiune);
}