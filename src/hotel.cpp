#include "hotel.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "camera.h"


hotel* hotel::instanta=nullptr;

hotel* hotel::getInstanta(){
    if(!instanta)
        instanta=new hotel();
    return instanta;
}

void hotel::afisareCamereLibere(){
    std::cout<<"\nCAMERE DISPONIBILE\n";

    bool existaLibere=false;
    for (const auto& camPtr : camere){
        if(! camPtr->esteOcupata()){
            std::cout<<*camPtr<<std::endl;
            existaLibere=true;
        }
    }

    if(!existaLibere)
        std::cout<<"Nicio camera disponibila\n";

}

void hotel::afisareCamereFiltrat(double pretMax){
    std::cout<<"\nCamere disponibile sub "<<pretMax<<" RON\n";

    bool gasit=false;
    for(const auto& camPtr : camere){
        if(!camPtr->esteOcupata() && camPtr->getPret() <=pretMax){
            std::cout<<*camPtr<<" "<<camPtr->getPret()<<" RON\n";
            gasit=true;
        }
    }
    if(!gasit)
        std::cout<<"Nicio camera disponibila sub acest pret. \n";
}

void hotel::rezervaCamera(int nr){
    bool gasit =false;
    for(auto& camPtr : camere){
        if(camPtr->getNr() == nr){
            gasit=true;
            if(!camPtr->esteOcupata())
                camPtr->setOcupata(true);
            else 
                std::cout<<"Camera "<<nr<<" nu este disponibila.\n";
            break;
        } 
        
    }
    if(!gasit)
        std::cout<<"Camera "<<nr<<" nu exista.\n";
}

std::shared_ptr<camera> hotel::getCameraByNr(int nr){
    for(auto& camPtr : camere)
        if(camPtr->getNr() == nr)
            return camPtr;
    return nullptr;
}

void hotel::rezervaCameraInSesiune(rezervare& rez, int nr){
    auto cam=getCameraByNr(nr);
    if(!cam){
        std::cout<<"Camera "<<nr<<" nu exista.\n";
        return;
    }
    if(cam->esteOcupata()){
        std::cout<<"Camera "<<nr<<" nu este disponibila. \n";
        return;
    }

    rez.adaugaCamera(cam);
    cam->setOcupata(true);
    std::cout<<"Camera "<<nr<<" adaugata in rezervare. \n";

}


void hotel::finalizeazaRezervare(rezervare &rez){
    if(rez.esteGoala()){
        std::cout<<"Nicio camera selectata.\n";
        return;
    }
    istoricRezervari.push_back(rez);
    std::cout<<"\nRerzervare confirmata\n";
    rez.afiseazaSumar();
} 

void hotel::afisareIstoricRezervari() const{
    if(istoricRezervari.empty()){
        std::cout<<"\nNicio rezervare inregistrata\n";
        return;
    }
    std::cout<<"\nISTORIC REZERVARI \n";

    int i=0;
    for(const auto& rez : istoricRezervari){
        std::cout<<"\nRezervare #"<<++i<<std::endl;
        rez.afiseazaSumar();
    }
}

