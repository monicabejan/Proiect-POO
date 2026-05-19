#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include "camera.h"
#include "rezervare.h"
 class Angajat;
class hotel {
    std::vector<std::shared_ptr<camera>> camere;
    std::vector<rezervare> istoricRezervari;
    std::vector<std::shared_ptr<Angajat>> angajati;

    hotel() {}
    hotel(const hotel&) = delete;
    hotel& operator=(const hotel&) = delete;
public:
    static hotel* getInstanta();

    void afisareCamereLibere() const;
    void afisareToateCamerele() const;
    void afisareCamereFiltrat(double pretMax) const;
    void rezervaCamera(int nr);
    void elibereazaCamera(int nr);
    void afisareTarife() const;
    void afisareStatistici() const;

    std::shared_ptr<camera> getCameraByNr(int nr) const;
    void rezervaCameraInSesiune(rezervare&rez, int nr);
    void finalizeazaRezervare(rezervare& rez);

    void afisareIstoricRezervari() const;
    void afisareTotalIncasari() const;

    void adaugaAngajat(std::shared_ptr<Angajat> a);
    Angajat* gasesteAngajat(const std::string& username, const std::string& parola) const;
    void afisareAngajati() const;
    
    void incarcaDatele();
    void salveazaDatele() const;

    template <typename T, typename... Args>
    void creeazaCamera(Args&&... args){
        auto cameraNoua=std::make_shared<T>(args...);
        camere.push_back(cameraNoua);
    }
    std::vector<std::shared_ptr<camera>> camereOrdonateDupaPret() const;
};

#endif