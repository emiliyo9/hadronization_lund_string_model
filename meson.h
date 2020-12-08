#ifndef MESON
#define MESON 

#include "quark.h"
#include "antiquark.h"
#include <string>

class Meson
{
    public:
        Meson(double mass, double frac, double x_plus, double x_min, double t, double z, double E, double p_z, Quark quark, Antiquark antiquark);
        double getMass(){ return this->mass; };
        double getFrac(){ return this->frac; };
        double getXPlus(){ return this->x_plus; };
        double getXMin(){ return this->x_min; };
        double getTime(){ return this->t; };
        double getZ(){ return this->z; };
        double getE(){ return this->E; };
        double getPz(){ return this->p_z; };
        int getCharge(){ return this->charge; };
        Quark getQuark(){ return this->quark; };
        Antiquark getAntiquark(){ return this->antiquark; };
        void info();
    private:
        double mass, frac;
        double x_plus, x_min, t, z, E, p_z;
        int charge;
        Quark quark;
        Antiquark antiquark;
};

#endif /* ifndef MESON */
