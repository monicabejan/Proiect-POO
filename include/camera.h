#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <string>
#include <memory>

class camera{
protected:
    int nrCamera;
    int etaj;
    double pret;
    bool status;
public:
    camera( int nr, int et, double p);
    camera(const camera& other);
    camera& operator=(const camera& other);
    virtual ~camera();


    virtual std::string getTipString() const = 0;
    

    virtual void afisareDetalii (std::ostream& os) const =0;
    virtual void citesteDetalii (std::istream& is)=0; 

     int getNr() const { return nrCamera;}
     [[maybe_unused]] int getEtaj() const {return etaj;}
     double getPret() const { return pret;}
     bool esteOcupata() const { return status;}
     void setOcupata(bool i) { status=i;}
     

     bool operator==(const camera& other) const;
     friend std::ostream& operator<<(std::ostream& os, const camera& c); 
     friend std::istream& operator>>(std::istream& is, camera& c);

};

class cameraSingle : public camera{
public:
    cameraSingle(int nr, int et, double p=150.0);
    cameraSingle(const cameraSingle& other);
    cameraSingle& operator=(const cameraSingle& other);
    ~cameraSingle() override = default;

    std::string getTipString() const override { return "Single";}

    void afisareDetalii(std::ostream& os) const override;
    void citesteDetalii(std::istream& is) override;
     
};

class cameraDouble : public camera {
    std::string tipConfiguratie;
public:
    cameraDouble(int nr, int et, const std::string& config, double p =250.0);
    cameraDouble(const cameraDouble& other);
    cameraDouble& operator=(const cameraDouble& other);
    ~cameraDouble() override = default;

    [[maybe_unused]] std::string getTipString() const override { return "Double";}

    [[maybe_unused]] std::string getTipConfiguratie() const {return tipConfiguratie;}

    void afisareDetalii(std::ostream& os) const override;
    void citesteDetalii(std::istream& is) override;
};


class penthouse : public camera {
    int nrDormitoare;
public:
    penthouse(int nr, int et, int nrDorm, double p =500.0);
    penthouse(const penthouse& other);
    penthouse& operator=(const penthouse& other);
    ~penthouse() override = default;

    std::string getTipString() const override { return "Penthouse";}

    [[maybe_unused]] int getNrDormitoare() const{ return nrDormitoare;}

    void afisareDetalii(std::ostream& os) const override;
    void citesteDetalii(std::istream& is) override;
}; 

#endif
