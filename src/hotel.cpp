#include "hotel.h"
#include "exceptii.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "camera.h"


hotel* hotel::instanta=nullptr;

hotel* hotel::getInstanta(){
    if(!instanta)
        instanta=new hotel();
    return instanta;
}

void hotel::afisareCamereLibere() const{
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

void hotel::afisareCamereFiltrat(double pretMax) const{
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

void hotel::afisareTarife() const{
    std::cout<<"\nTARIFE - PRET CRESCATOR\n";
    auto sortate=camereOrdonateDupaPret();
    for(const auto& c : sortate)
        std::cout<<"Camera "<<c->getNr()<<" - "<<c->getPret()<<" RON\n";
}

void hotel::afisareStatistici() const{
    std::cout<<"\nSTATISTICI\n";
    std::cout<<"Total camere: "<<camere.size()<<"\n";
    long libere=std::count_if(camere.begin(), camere.end(), [](const std::shared_ptr<camera>&c) {return !c->esteOcupata();});
    std::cout<<"Camere libere: "<<libere<<"\n";
    std::cout<<"Total rezervari: "<<istoricRezervari.size()<<"\n";

    double venit=0;
    std::for_each(istoricRezervari.begin(),istoricRezervari.end(), [&venit](const rezervare& r){venit+=r.calculeazaTotal();});
    std::cout<<"Venit total: "<<venit<<" RON\n";
}

std::shared_ptr<camera> hotel::getCameraByNr(int nr) const{
    for(const auto& camPtr : camere)
        if(camPtr->getNr() == nr)
            return camPtr;
    return nullptr;
}

void hotel::rezervaCameraInSesiune(rezervare& rez, int nr){
    auto cam=getCameraByNr(nr);
    if(!cam){
        throw ExceptieCamera(nr, "nu exista in hotel");
    }
    if(cam->esteOcupata()){
        throw ExceptieCamera(nr, "este deja ocupata");
    }

    rez.adaugaCamera(cam);
    cam->setOcupata(true);
    std::cout<<"\nCamera "<<nr<<" adaugata in rezervare. \n";

}


void hotel::finalizeazaRezervare(rezervare &rez){
    if(rez.esteGoala()){
        throw ExceptieRezervareInvalida("Nu a fost selectata nicio camera");
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

std::vector<std::shared_ptr<camera>> hotel::camereOrdonateDupaPret() const {
    std::vector<std::shared_ptr<camera>> sortate(camere);
    std::sort(sortate.begin(), sortate.end(), [](const std::shared_ptr<camera>& a,const std::shared_ptr<camera>& b) {
        return a->getNr() < b->getNr();

    } );
    return sortate;
}