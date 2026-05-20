#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <iostream>
#include <memory>
class hotel;

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
    // cppcheck-suppress unusedFunction
    double getSalariu() const;

    // cppcheck-suppress unusedFunction
    const std::string& getParola() const { return parola;}

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
    // cppcheck-suppress unusedFunction
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
    // cppcheck-suppress unusedFunction
    int getNrCamereAsignate() const {return nrCamereAsignate;}
};

class Manager: public Angajat{
    int nrAngajatiSupervizati;
    public:
    Manager(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    Manager& operator=(const Manager& other);
    Manager(const Manager& other);

    std::string getRol() const override {return "Manager";}
    void afiseazaMeniu(hotel* h) override;
    // cppcheck-suppress unusedFunction
    void setNrAngajati(int n) {nrAngajatiSupervizati=n;}
    // cppcheck-suppress unusedFunction
    int getNrAngajati() const {return nrAngajatiSupervizati;}
};


class Admin:public Angajat{
    void creeazaCameraInteractiv(hotel* h);
    void creeazaAngajatInteractiv(hotel* h);
    public:
    Admin(const std::string& nume, const std::string& user, const std::string& parola, double salariu);
    Admin& operator=(const Admin& other);
    Admin(const Admin& other);

    std::string getRol() const override {return "Admin";}
    void afiseazaMeniu(hotel* h) override;
};



#endif