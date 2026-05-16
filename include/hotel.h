#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <memory>
#include <iostream>
#include "camera.h"
#include "rezervare.h"
 
class hotel {
    static hotel* instanta;
    std::vector<std::shared_ptr<camera>> camere;
    std::vector<rezervare> istoricRezervari;

    hotel() {}
public:
    static hotel* getInstanta();

    void afisareCamereLibere();
    void afisareCamereFiltrat(double pretMax);
    void rezervaCamera(int nr);
    void afisareTarife();

    std::shared_ptr<camera> getCameraByNr(int nr);
    void rezervaCameraInSesiune(rezervare&rez, int nr);
    void finalizeazaRezervare(rezervare& rez);

    void afisareIstoricRezervari() const;

    template <typename T, typename... Args>
    void creeazaCamera(Args&&... args){
        auto cameraNoua=std::make_shared<T>(args...);
        camere.push_back(cameraNoua);
    }
};

#endif