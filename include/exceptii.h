#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <stdexcept>
#include <string>

class ExceptieHotel : public std::exception{
    std::string mesaj;
public:
    explicit ExceptieHotel(const std::string& msg) : mesaj(msg) {}
    const char* what() const noexcept override { return mesaj.c_str();}
};

class ExceptieCamera:public ExceptieHotel{
    int nrCamera;
public:
    ExceptieCamera(int nr, const std::string& detaliu) : ExceptieHotel("Camera "+std::to_string(nr)+": "+detaliu), nrCamera(nr) {}
    int getNrCamera() const {return nrCamera;}

};

class ExceptiePretInvalid: public ExceptieHotel{
    double pretIntrodus;
public:
    explicit ExceptiePretInvalid(double p):ExceptieHotel("Pret invalid: "+std::to_string(p)), pretIntrodus(p) {}
    double getPretIntrodus() const { return pretIntrodus;}
};


class ExceptieRezervareInvalida: public ExceptieHotel{
    public:
    explicit ExceptieRezervareInvalida(const std::string& motiv) : ExceptieHotel("Rezervare invalida: "+motiv){}
};

class ExceptieOptiuneInvalida: public ExceptieHotel{
    public:
    ExceptieOptiuneInvalida(): ExceptieHotel("Optiune invalida"){}
};
#endif