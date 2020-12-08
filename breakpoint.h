#ifndef BREAKPOINT
#define BREAKPOINT 

#include "quark.h"
#include "antiquark.h"
#include <string>

class Breakpoint
{
    public:
        Breakpoint(double x_plus, double x_min, double t, double z, double gamma, Quark quark, Antiquark antiquark);
        double getXPlus(){ return this->x_plus; };
        double getXMin(){ return this->x_min; };
        double getTime(){ return this->t; };
        double getZ(){ return this->z; };
        double getGamma(){ return this->gamma; };
        Quark getQuark(){ return this->quark; };
        Antiquark getAntiquark(){ return this->antiquark; };
        void info();
    private:
        double x_plus, x_min, t, z;
        double gamma;
        Quark quark;
        Antiquark antiquark;
};

#endif /* ifndef BREAKPOINT */
