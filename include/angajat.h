#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <iostream>
#include "hotel.h"

class Angajat{
    protected:
    std::string nume;
    std::string username;
    std::string parola;
    double salariu;
    public:
    Angajat(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    Angajat(const Angajat& other);
    Angajat& operator=(const Angajat& other);
    virtual ~Angajat()=default;

    bool verificaParola(const std::string& p) const;
    const std::string& getUsername() const;
    const std::string& getNume() const;
    double getSalariu() const;

    virtual std::string getRol() const = 0;
    virtual void afiseazaMeniu(hotel* h)=0;

    friend std::ostream& operator<<(std::ostream& os,const Angajat& a);
    friend std::istream& operator>>(std::istream& is, Angajat& a);

};

class AngajatFrontDesk: public Angajat {
    int nrCheckinuri;
    public:
    AngajatFrontDesk(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    AngajatFrontDesk(const AngajatFrontDesk& other);
    AngajatFrontDesk& operator=(const AngajatFrontDesk& other);

    std::string getRol() const override{ return "Front Desk";}
    void afiseazaMeniu(hotel *h) override;
    void inregistreazaCheckin() {++nrCheckinuri;}
    int getNrCheckinuri() const { return nrCheckinuri;}
};

class AngajatHousekeeping : public Angajat{
    int nrCamereAsignate;
    public:
    AngajatHousekeeping(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    AngajatHousekeeping(const AngajatHousekeeping& other);
    AngajatHousekeeping& operator=(const AngajatHousekeeping& other);
    std::string getRol() const override {return "Housekeeping";}
    void afiseazaMeniu(hotel* h) override;
    void marcheazaInCuratenie(hotel* h, int nrCamera);
    int getNrCamereAsignate() const {return nrCamereAsignate;}
};

class Manager: public Angajat{
    int nrAngajatiSupervizati;
    public:
    Manager(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    Manager& operator=(const Manager& other);

    std::string getRol() const override {return "Manager";}
    void afiseazaMeniu(hotel* h) override;
    void setNrAngajati(int n) {nrAngajatiSupervizati=n;}
    int getNrAngajati() const {return nrAngajatiSupervizati;}
};


class Admin:public Angajat{
    void creeazaCameraInteractiv(hotel* h);
    void creeazaAngajatInteractiv(hotel* h);
    public:
    Admin(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    Admin& operator=(const Admin& other);

    std::string getRol() const override {return "Admin";}
    void afiseazaMeniu(hotel* h) override;
};



#endif