#ifndef REZERVARE_H
#define REZERVARE_H
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "camera.h"
#include "serviciu.h"
 
class rezervare{
    std::string numeClient;
    std::vector<std::shared_ptr<camera>>camereRezervate;
    std::vector<std::shared_ptr<Serviciu>> serviciiAditionale;
public:
    explicit rezervare(const std::string& nume);
    rezervare(const rezervare& other);
    rezervare& operator=(const rezervare& other);
    ~rezervare();

    const std::string& getNumeClient() const;

    
    void adaugaCamera(std::shared_ptr<camera> camPtr);
    void adaugaServiciu(std::shared_ptr<Serviciu> srv);
    bool esteGoala() const;

    double calculeazaTotal() const;
    void afiseazaSumar() const ;

    bool operator==(const rezervare& other) const;
    friend std::ostream& operator<<(std::ostream& os,const rezervare& r);
};


#endif
