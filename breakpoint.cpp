#include "breakpoint.h"
#include <iostream>
#include <cmath>

Breakpoint::Breakpoint(double x_plus, double x_min, double t, double z, double gamma, Quark quark, Antiquark antiquark):
    x_plus(x_plus),
    x_min(x_min),
    t(t),
    z(z),
    gamma(gamma),
    quark(quark),
    antiquark(antiquark)
{
    if (quark.getColor() != antiquark.getColor()) {
        throw "Breakpoint needs to have a net white color";
    }
}

void Breakpoint::info()
{
    std::cout << "Breakpoint" << std::endl;
    std::cout << "==========" << std::endl;
    std::cout << "x_+: " << this->x_plus << std::endl;
    std::cout << "x_-: " << this->x_min << std::endl;
    std::cout << "t: " << this->t << std::endl;
    std::cout << "z: " << this->z << std::endl;
    std::cout << "gamma: " << this->gamma << std::endl;
    quark.info();
    antiquark.info();
}
