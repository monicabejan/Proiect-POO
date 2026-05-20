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
#include "meniu.h"


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

    hotel->creeazaCamera<penthouse>(201, 2, 3, 500);
    hotel->creeazaCamera<penthouse>(202, 2, 4);


    pornesteAplicatia(hotel);
    
    return 0;
}