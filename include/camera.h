#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <string>

class camera{
protected:
    int nrCamera;
    int etaj;
    double pret;
    bool status;
public:
    camera( int nr, int et, double p);
    virtual ~camera();

    virtual void afisareDetalii (std::ostream& os) const =0; 

     int getNr() const { return nrCamera;}
     double getPret() const { return pret;}
     bool esteOcupata() const { return status;}
     void setOcupata(bool i) { status=i;}

     bool operator==(const camera& other) const;
     friend std::ostream& operator<<(std::ostream& os, const camera& c); 
};

class cameraSingle : public camera{

public:
    cameraSingle(int nr, int et, double p=150.0);
    void afisareDetalii(std::ostream& os) const override;
     
};

class cameraDouble : public camera {
    std::string tipConfiguratie;
public:
    cameraDouble(int nr, int et, const std::string& config, double p=250.0);
    void afisareDetalii(std::ostream& os) const override;
};

class penthouse : public camera {
    int nrDormitoare;
public:
    penthouse(int nr, int et, int nrDorm, double p=500.0);
    void afisareDetalii(std::ostream& os) const override;
}; 

#endif
