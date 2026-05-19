#include "camera.h"
#include "exceptii.h"

camera::camera(int nr, int et, double p) : nrCamera(nr), etaj(et), pret(p), status(false) {}
camera::camera(const camera& other) : nrCamera(other.nrCamera), etaj(other.etaj), pret(other.pret), status(other.status) {}
camera& camera::operator=(const camera& other){
    if(this!=&other){
        nrCamera=other.nrCamera;
        etaj=other.etaj;
        pret=other.pret;
        status=other.status;
    }
    return *this;
}
camera::~camera() {}

bool camera::operator==(const camera& other) const{
    return this->nrCamera==other.nrCamera;
}


std::ostream& operator<<(std::ostream& os, const camera& c) {
    os<<"\nNr: "<<c.nrCamera
      <<" Etaj: "<<c.etaj;
    c.afisareDetalii(os);
    return os;

} 

std::istream& operator>>(std::istream& is, camera& c){
    std::cout<<"Noul pret: ";
    double p;
    is>>p;
   // if(p<=0) throw ExceptiePretInvalid(p);
    c.pret=p;
    return is;
}
double operator+(const camera& a, const camera& b){
    return a.getPret() + b.getPret();
}



cameraSingle::cameraSingle(int nr, int et, double p) : camera(nr, et, p) {}
cameraSingle::cameraSingle(const cameraSingle & other) : camera(other) {}
cameraSingle& cameraSingle::operator=(const cameraSingle& other){
    if(this !=&other)
        camera::operator=(other);
    return *this;
}
cameraSingle::~cameraSingle() {}

void cameraSingle::afisareDetalii(std::ostream& os) const {
    os<<" Single";
}
void cameraSingle::citesteDetalii(std::istream& is) {}


cameraDouble::cameraDouble(int nr, int et, const std::string& config, double p) : camera(nr, et, p), tipConfiguratie(config) {}
cameraDouble::cameraDouble(const cameraDouble& other):camera(other), tipConfiguratie(other.tipConfiguratie) {}
cameraDouble& cameraDouble::operator =(const cameraDouble& other){
    if(this!=&other){
        camera::operator=(other);
        tipConfiguratie=other.tipConfiguratie;
    }
    return *this;
}
cameraDouble::~cameraDouble(){}


void cameraDouble::afisareDetalii (std::ostream& os) const{
    os<<" Double "
      <<"configuratie: "<<tipConfiguratie;
}
void cameraDouble::citesteDetalii(std::istream& is) {}

penthouse::penthouse(int nr, int et, int nrDorm, double p) : camera(nr, et, p), nrDormitoare(nrDorm) {}
penthouse::penthouse(const penthouse& other) : camera(other), nrDormitoare(other.nrDormitoare){}
penthouse& penthouse::operator=(const penthouse& other) {
    if(this!=&other){
        camera::operator=(other);
        nrDormitoare=other.nrDormitoare;
    }
    return *this;
}
penthouse::~penthouse() {}

void penthouse::afisareDetalii(std::ostream& os) const {
    os<<" Penthouse "
      <<nrDormitoare<<" dormitoare";
}
void penthouse::citesteDetalii(std::istream& is) {}