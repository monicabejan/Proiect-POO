#include "camera.h"

camera::camera(int nr, int et, double p) : nrCamera(nr), etaj(et), pret(p), status(false) {}
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

cameraSingle::cameraSingle(int nr, int et, double p) : camera(nr, et, p) {}
void cameraSingle::afisareDetalii(std::ostream& os) const {
    os<<" Single";
}

cameraDouble::cameraDouble(int nr, int et, std::string config, double p) : camera(nr, et, p), tipConfiguratie(config) {}
void cameraDouble::afisareDetalii (std::ostream& os) const{
    os<<" Double "
      <<"configuratie: "<<tipConfiguratie;
}

penthouse::penthouse(int nr, int et, int nrDorm, double p) : camera(nr, et, p), nrDormitoare(nrDorm) {}
void penthouse::afisareDetalii(std::ostream& os) const {
    os<<" Penthouse "
      <<nrDormitoare<<" dormitoare";
}