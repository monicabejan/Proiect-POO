#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "camera.h"
#include "hotel.h"
#include "rezervare.h"
#include "serviciu.h"
#include "exceptii.h"
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
        std::cout<<"MENIU INTERACTIV \n";
        std::cout<<"0. Exit \n";
        std::cout<<"1. Vizualizare camere disponibile \n";
        std::cout<<"2. Filtrare dupa pret \n";
        std::cout<<"3. Rezervare camere \n";
        std::cout<<"4. Istoric rezervari \n";
        std::cout<<"5. Statistici \n";
        std::cout<<"6. Tarife \n";

        std::cout<<"Optiune: ";
        if( std::cin>>optiune){

        try{
            switch(optiune){
                case 0:
                break;

                case 1:
                hotel->afisareCamereLibere();
                break;

                case 2:{
                double pretMax;
                std::cout<<"\nPret maxim: ";
                std::cin>>pretMax;
                if(pretMax<=0) throw ExceptiePretInvalid(pretMax);
                hotel->afisareCamereFiltrat(pretMax);
                break;
                }
                
                case 3:{
                std::string nume;
                std::cout<<"\nNume client: ";
                std::cin>>nume;

                rezervare sesiune(nume);
                int nrCam;
                do{
                    hotel->afisareCamereLibere();
                    std::cout<<"\nNr camera de rezervat (0 pentru finalizare): ";
                    std::cin>>nrCam;

                    if(nrCam)
                        {
                            try{
                                hotel->rezervaCameraInSesiune(sesiune, nrCam);
                            }catch (const ExceptieCamera& e){
                                const ExceptieHotel& eh=e;
                                std::cout<<"Eroare: "<<eh.what()<<"\n";
                            }
                        }
                } while(nrCam);
                try{
                    hotel->finalizeazaRezervare(sesiune);
                }catch( const ExceptieRezervareInvalida& e){
                    std::cout<<"Eroare rezervare: "<<e.what()<<"\n";
                }
                
                break;
                }

                case 4:
                hotel->afisareIstoricRezervari();
                break;

                case 5:
                hotel->afisareStatistici();
                break;

                case 6:
                hotel->afisareTarife();
                break;

                default:
                throw ExceptieOptiuneInvalida();
                
                
            }
        } catch(const ExceptieHotel& e){
            std::cout<<"Exceptie "<<e.what()<<"\n";
        }catch(const std::exception& e){
            std::cout<<"Exceptie std "<<e.what()<<"\n";
        }
        }
        if(optiune)
            std::this_thread::sleep_for(std::chrono::seconds(2));

        
    } while ( optiune);
    std::cout<<"La revedere"<<"\n";
    return 0;
}
