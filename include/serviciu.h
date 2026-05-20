#ifndef SERVICIU_H
#define SERVICIU_H
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Serviciu{
protected:
    std::string denumire;
    double pretServiciu;

    static std::vector<std::function<void(const std::string&)>> observatori;
public:
    Serviciu(const std::string& den, double pret);
    virtual ~Serviciu()=default;

    virtual void executa() const=0;
    virtual double calculeazaCost() const;
    virtual std::string getTip() const=0;

    const std::string& getDenumire() const { return denumire;}
    double getPret() const { return pretServiciu;}

    static void inregistreazaObservator(std::function<void(const std::string&)>obs);
    static void notificaObservatori(const std::string& mesaj);

    bool operator==(const Serviciu& other)const;
    friend std::ostream& operator<<(std::ostream& os, const Serviciu& s);
};


class ServiciuLaundry:public Serviciu{
    int nrPiese;
    public:
    ServiciuLaundry(int nrPiese, double pretPerPiesa=15.0);

    ServiciuLaundry(const ServiciuLaundry& other);
    ServiciuLaundry& operator=(const ServiciuLaundry& other);
    ~ServiciuLaundry() override=default;

    void executa() const override;
    double calculeazaCost() const override;
    std::string getTip() const override {return "Laundry";}
    int getNrPiese() const{ return nrPiese;}
};

class ServiciuRoomService:public Serviciu{
    std::string comanda;
    bool urgent;
    public:
    ServiciuRoomService(const std::string& comanda, bool urgent=false, double pret=50.0);
    ServiciuRoomService(const ServiciuRoomService& other);
    ServiciuRoomService& operator=(const ServiciuRoomService& other);
    ~ServiciuRoomService() override =default;

    void executa() const override;
    double calculeazaCost() const override;
    std::string getTip() const override{ return "Room Service";}

    bool esteUrgent() const { return urgent;}
};

class ServiciuSpa :public Serviciu{
    int durataMasaj;
    public:
    ServiciuSpa(int durata, double pretPerMinut=3.0);
    ServiciuSpa(const ServiciuSpa& other);
    ServiciuSpa& operator=(const ServiciuSpa& other);
    ~ServiciuSpa() override = default;

    void executa() const override;
    double calculeazaCost() const override;
    std::string getTip() const override { return "Spa";}

    int getDurata() const { return durataMasaj;}
};


#endif