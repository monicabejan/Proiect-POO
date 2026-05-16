#ifndef REZERVARE_H
#define REZERVARE_H
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "camera.h"
 
class rezervare{
    std::string numeClient;
    std::vector<std::shared_ptr<camera>>camereRezervate;
public:
    explicit rezervare(const std::string& nume);

    
    void adaugaCamera(std::shared_ptr<camera> camPtr);
    bool esteGoala() const;

    double calculeazaTotal() const;
    void afiseazaSumar() const ;
};


#endif
