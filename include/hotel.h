#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include "camera.h"
#include "rezervare.h"
 
class hotel {
    static hotel* instanta;
    std::vector<std::shared_ptr<camera>> camere;
    std::vector<rezervare> istoricRezervari;

    hotel() {}
public:
    static hotel* getInstanta();

    void afisareCamereLibere() const;
    void afisareCamereFiltrat(double pretMax) const;
    void rezervaCamera(int nr);
    void afisareTarife() const;
    void afisareStatistici() const;

    std::shared_ptr<camera> getCameraByNr(int nr) const;
    void rezervaCameraInSesiune(rezervare&rez, int nr);
    void finalizeazaRezervare(rezervare& rez);

    void afisareIstoricRezervari() const;



    template <typename T, typename... Args>
    void creeazaCamera(Args&&... args){
        auto cameraNoua=std::make_shared<T>(args...);
        camere.push_back(cameraNoua);
    }
    std::vector<std::shared_ptr<camera>> camereOrdonateDupaPret() const;
};

#endif