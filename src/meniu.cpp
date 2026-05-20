#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <memory>

#include "../include/meniu.h"
#include "../include/angajat.h"
#include "../include/exceptii.h"
#include "../include/serviciu.h"
#include "../include/hotel.h"


void proceseazaRezervareActiva(hotel * h, const std::string& numeClient){
    rezervare rez(numeClient);
    int optiune=0;

    do{

        std::cout<<"\nREZERVARE: "<<numeClient<<"\n";
        std::cout<<"0. Anulare\n";
        std::cout<<"1. Vezi camere libere \n";
        std::cout<<"2. Adauga camera in rezervare \n";
        std::cout<<"3. Adauga serviciu de spalatorie\n";
        std::cout<<"4. Adauga room service\n";
        std::cout<<"5. Adauga serviciu de spa\n";
        std::cout<<"6. Finalizare rezervare\n";
        std::cout<<"\nOptiune: ";

        if(std::cin>>optiune){

            try{

                switch(optiune){

                    case 0:
                    break;

                    case 1:
                    h->afisareCamereLibere();
                    break;

                    case 2:{
                        int nr;
                        std::cout<<"\nNr camera: ";
                        std::cin>>nr;
                        h->rezervaCameraInSesiune(rez, nr);
                        break;
                    }

                    case 3:{
                        int piese;
                        std::cout<<"\nNr piese de spalat: ";
                        std::cin>>piese;
                        rez.adaugaServiciu(std::make_shared<ServiciuLaundry>(piese));
                        break;
                    }

                    case 4:{
                        std::string comanda;
                        std::cout<<"\nCe doriti sa comandati (mancare/bautura): ";
                        std::cin.ignore();
                        std::getline(std::cin, comanda);
                        rez.adaugaServiciu(std::make_shared<ServiciuRoomService>(comanda,false));
                        break;
                    }

                    case 5: {
                        int minute;
                        std::cout<<"\nDurata masajului (minute): ";
                        std::cin>>minute;
                        rez.adaugaServiciu(std::make_shared<ServiciuSpa>(minute));
                        break;
                    }

                    case 6:
                    if(rez.esteGoala()){
                        //throw ExceptieRezervareInvalida();
                    }
                    else{
                        h->finalizeazaRezervare(rez);
                        optiune=0;
                    }
                    break;

                    default: 
                    std::cout<<"\nOptiune invalida\n";

                }

            }catch(const std::exception& e){
                std::cout<<"\nEroare "<<e.what()<<"\n";
            }

        }

    }while(optiune);
}

void meniuClient(hotel* h){
    std::string numeClient;
    std::cout<<"\nNume: ";
    std::cin.ignore();
    std::getline(std::cin, numeClient);

    int optiune=0;
    do{
        std::cout<<"\nMENIU CLIENT\n";
        std::cout<<"0. Inapoi\n";
        std::cout<<"1. Camere disponibile\n";
        std::cout<<"2. Filtrare dupa pret\n";
        std::cout<<"3. Rezervare\n";
        std::cout<<"Optiune: ";

        if(std::cin>>optiune){
            try{
                switch(optiune){
                    case 0:
                    break;

                    case 1:
                    h->afisareCamereLibere();
                    break;

                    case 2:{
                        double pretMax;
                        std::cout<<"\nPret maxim: ";
                        std::cin>>pretMax;
                        if(pretMax<=0) throw ExceptiePretInvalid(pretMax);
                        h->afisareCamereFiltrat(pretMax);
                        break;
                    }
                    case 3:
                    proceseazaRezervareActiva(h, numeClient);
                    break;

                    default:
                    throw ExceptieOptiuneInvalida();
                    
                }
            }catch(const ExceptieHotel& e) {
                std::cout<<"\nEroare "<<e.what()<<"\n";
            }
    }
}while(optiune);
}


void loginAngajat(hotel *h){
    std::string user, parola;
    std::cout<<"\nUsername: ";
    std::cin>>user;
    std::cout<<"\nParola: ";
    std::cin>>parola;

    const std::string ADMIN_USER = "admin";
    const std::string ADMIN_PWD= "admin123";

    Angajat* staffLogat=nullptr;
    std::unique_ptr<Admin> adminTemporar = nullptr;

    if(user == ADMIN_USER && parola== ADMIN_PWD){
        adminTemporar=std::make_unique<Admin>("Administrator", ADMIN_USER, ADMIN_PWD, 0.0);
        staffLogat=adminTemporar.get();
    }
    else{
        staffLogat=h->gasesteAngajat(user, parola);
    }
    if(!staffLogat) {
        std::cout<<"\n Username sau parola incorecte\n";
        return;
    }

   
    std::cout<<"\n"<<staffLogat->getNume()<<" "<<staffLogat->getRol()<<" Start pontaj";
    auto start=std::chrono::steady_clock::now();
    staffLogat->afiseazaMeniu(h);
    auto stop=std::chrono::steady_clock::now();
    auto sec=std::chrono::duration_cast<std::chrono::seconds>(stop-start).count();
    std::cout<<"\nPontaj: "<<staffLogat->getNume()<<" "<<sec/3600<<"h "<<(sec%3600)/60<<"m "<<sec%60<<"s\n";

}


void pornesteAplicatia(hotel* hotel){
    int optiune=0;
    do{
        std::cout<<"HOTEL \n";
        std::cout<<"0. Exit \n";
        std::cout<<"1. Continua ca vizitator \n";
        std::cout<<"2. Login angajat \n";
        

        std::cout<<"Optiune: ";
        if( std::cin>>optiune){

        try{
            switch(optiune){
                case 0:
                break;

                case 1:
                meniuClient(hotel);
                break;

                case 2:
                loginAngajat(hotel);
                break;

                default:
                throw ExceptieOptiuneInvalida();  
            }
        }catch(const std::exception& e)
           { std::cout<<"Exceptie std "<<e.what()<<"\n";}
        

        if(optiune)
            std::this_thread::sleep_for(std::chrono::seconds(2));
        

}
    }while ( optiune);
    std::cout<<"La revedere"<<"\n";
}