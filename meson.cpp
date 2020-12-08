#include "meson.h"
#include <iostream>
#include <cmath>

Meson::Meson(double mass, double frac, double x_plus, double x_min, double t, double z, double E, double p_z, Quark quark, Antiquark antiquark):
    mass(mass),
    frac(frac),
    x_plus(x_plus),
    x_min(x_min),
    t(t),
    z(z),
    E(E),
    p_z(p_z),
    quark(quark),
    antiquark(antiquark)
{
    if (mass < 0) {
        throw "Mass of meson can not be negative";
    }
    if (quark.getColor() != antiquark.getColor()) {
        throw "Mesons need to have a net white color";
    }
    this->charge = (int)std::round(this->quark.getCharge() + this->antiquark.getCharge());
}

void Meson::info()
{
    std::cout << "Meson" << std::endl;
    std::cout << "=====" << std::endl;
    std::cout << "mass: " << this->mass << "GeV" << std::endl;
    std::cout << "charge: " << this->charge << std::endl;
    std::cout << "z: " << this->frac << std::endl;
    std::cout << "x_+: " << this->x_plus << std::endl;
    std::cout << "x_-: " << this->x_min << std::endl;
    quark.info();
    antiquark.info();
}
