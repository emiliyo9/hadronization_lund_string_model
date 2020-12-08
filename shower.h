#ifndef SHOWER
#define SHOWER 

#include "quark.h"
#include "antiquark.h"
#include "meson.h"
#include "breakpoint.h"
#include <TRandom3.h>
#include <vector>
#include <fstream>

class Shower
{
    public:
        Shower(double E_cm, Quark start_quark, Antiquark strart_antiquark, TRandom3* r);
        void info();
        void saveMesons(std::ofstream& out);
        void saveBreakpoints(std::ofstream& out);
    private:
        double E_cm, m_sq_av;
        std::vector<Breakpoint*> breakpoints;
        std::vector<Meson*> mesons;
        TRandom3* r;
        bool startFromQuark;
        double distribution(double a, double b, double m, double z);
        double getNextFraction(double a, double b, double m);
        void hadronize();
        void hadronizeQuark();
        void hadronizeAntiquark();
};

#endif /* ifndef SHOWER */
