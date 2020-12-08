#include "shower.h"
#include "quark.h"
#include "antiquark.h"
#include "meson.h"
#include <fstream>
#include <TRandom3.h>
#include <iostream>
#include <vector>

int main()
{
    //double E_cm = 0.317;
    double E_cm = 306;

    TRandom3 *r = new TRandom3();
    
    std::vector<char> fl = {'u', 'd'};
    std::vector<char> cl = {'g', 'b', 'r'};
    
    std::ofstream out_m;
    out_m.open("output_mesons.txt");
    std::ofstream out_b;
    out_b.open("output_breakpoints.txt");

    Shower* s;
    for (int i = 0; i < 100; i++) {
        std::cout << i << std::endl;
        int fl_rand = r->Integer(fl.size());
        int cl_rand = r->Integer(cl.size());
        Quark q(fl[fl_rand], cl[cl_rand]);
        Antiquark aq(fl[fl_rand], cl[cl_rand]);

        s = new Shower(E_cm, q, aq, r);
        s->saveMesons(out_m);
        s->saveBreakpoints(out_b);
        delete(s);
    }
    return 0;
}
