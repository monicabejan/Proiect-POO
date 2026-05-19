#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "camera.h"
#include "hotel.h"
#include "rezervare.h"
#include "serviciu.h"
#include "exceptii.h"
#include "angajat.h"

void meniuVizitator(hotel* h){
    int optiune=0;
    do{
        std::cout<<"\nMENIU VIZITATOR\n";
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
                    case 3:{
                        std::string nume;
                        std::cout<<"\nNume: ";
                        std::cin>>nume;
                        rezervare sesiune(nume);
                        int nrCam;
                        do{
                            h->afisareCamereLibere();
                            std::cout<<"\nNr. camera de rezervat (0 pentru finalizare): ";
                            std::cin>>nrCam;
                            if(nrCam){
                                try{
                                    h->rezervaCameraInSesiune(sesiune, nrCam);
                                }catch(const ExceptieCamera& e){
                                    const ExceptieHotel& eh=e;
                                    std::cout<<"\nEroare "<<eh.what()<<"\n";
                                }
                            }
                        }while(nrCam);
                        try{
                            h->finalizeazaRezervare(sesiune);    
                        }catch( const ExceptieRezervareInvalida& e){
                            std::cout<<"\nEroare "<<e.what()<<"\n";
                        }
                        break;
                    }
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

    Angajat* a=h->gasesteAngajat(user, parola);
    if(!a){
        std::cout<<"\nUsername sau parola incorecte\n";
        return;
    }
    std::cout<<"\n"<<a->getNume()<<" "<<a->getRol()<<" Start pontaj";
    auto start=std::chrono::steady_clock::now();
    a->afiseazaMeniu(h);
    auto stop=std::chrono::steady_clock::now();
    auto sec=std::chrono::duration_cast<std::chrono::seconds>(stop-start).count();
    std::cout<<"\nPontaj: "<<a->getNume()<<" "<<sec/3600<<"h "<<(sec%3600)/60<<"m "<<sec%60<<"s\n";

}

int main()
{ 
    Serviciu::inregistreazaObservator([](const std::string& msg){
        std::cout<<"LOG "<<msg<<"\n";
    });
    hotel* hotel=hotel::getInstanta();

    hotel->creeazaCamera<cameraSingle>(101, 1, 100);
    hotel->creeazaCamera<cameraSingle>(102, 1, 100);
    hotel->creeazaCamera<cameraSingle>(103, 1);

    hotel->creeazaCamera<cameraDouble>(105, 1, "Twin", 200);
    hotel->creeazaCamera<cameraDouble>(106, 2, "Matrimonial");

    hotel->creeazaCamera<penthouse>(201, 2, 3, 550);
    hotel->creeazaCamera<penthouse>(202, 2, 4);


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
                meniuVizitator(hotel);
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
    return 0;
}