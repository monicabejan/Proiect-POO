#include <iostream>
#include <thread>
#include <chrono> //pentru sleep()
#include "camera.h"
#include "hotel.h"
#include "rezervare.h"
int main()
{ 
    hotel* hotel=hotel::getInstanta();

    hotel->creeazaCamera<cameraSingle>(101, 1, 100);
    hotel->creeazaCamera<cameraSingle>(102, 1, 100);
    hotel->creeazaCamera<cameraSingle>(103, 1);

    hotel->creeazaCamera<cameraDouble>(105, 1, "Twin", 200);
    hotel->creeazaCamera<cameraDouble>(106, 2, "Matrimonial");

    hotel->creeazaCamera<penthouse>(201, 2, 3, 550);
    hotel->creeazaCamera<penthouse>(202, 2, 4);


    int optiune=0;
    while (std::cout << "Optiune: " && std::cin >> optiune){
        std::cout<<"MENIU INTERACTIV \n";
        std::cout<<"0. Exit \n";
        std::cout<<"1. Vizualizare camere disponibile \n";
        std::cout<<"2. Filtrare dupa pret \n";
        std::cout<<"3. Rezervare camere \n";
        std::cout<<"4. Istoric rezervari \n";

        std::cout<<"Optiune: ";
        std::cin>>optiune;

        try{
            switch(optiune){

                case 1:
                hotel->afisareCamereLibere();
                break;

                case 2:{
                double pretMax;
                std::cout<<"\nPret maxim: ";
                std::cin>>pretMax;
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
                        hotel->rezervaCameraInSesiune(sesiune, nrCam);
                } while(nrCam);
                hotel->finalizeazaRezervare(sesiune);
                
                break;
                }

                case 4:
                hotel->afisareIstoricRezervari();
                break;

                default:
                //throw ExceptieOptiuneInvalida();
                break;
                
            }
        } catch(...){}
        //catch (const ExceptiiHotel& e){
        //     std::cout<<e.what()<<"\n";
        // }
        if(optiune)
            std::this_thread::sleep_for(std::chrono::seconds(2));

        
    }
}
