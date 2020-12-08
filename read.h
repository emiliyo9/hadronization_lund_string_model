#ifndef READ
#define READ

#include <iostream>
#include <fstream>
#include <tuple>

std::tuple<double, double, double, double, double, double, double, double, int, char, char, double, char, char, double> readMesonLine(std::ifstream& in)
{
    /*
     * Does not check if file has reached the end
     */

    double mass, frac, e_q, e_aq;
    double x_plus, x_min, t, z, E, p_z;
    int e;
    char f_q, c_q, f_aq, c_aq;

    in >> mass >> frac >> x_plus >> x_min >> t >> z >> E >> p_z >> e >> f_q >> c_q >> e_q >> f_aq >> c_aq >> e_aq;
    return  std::tuple<double, double, double, double, double, double, double, double, int, char, char, double, char, char, double>{mass, frac, x_plus, x_min, t, z, E, p_z, e, f_q, c_q, e_q, f_aq, c_aq, e_aq};
}

std::tuple<double, double, double, double, double, char, char, double, char, char, double> readBreakpointLine(std::ifstream& in)
{
    /*
     * Does not check if file has reached the end
     */

    double x_plus, x_min, t, z;
    double gamma, e_q, e_aq;
    char f_q, c_q, f_aq, c_aq;

    in >> x_plus >> x_min >> t >> z >> gamma >> f_q >> c_q >> e_q >> f_aq >> c_aq >> e_aq;
    return std::tuple<double, double, double, double, double, char, char, double, char, char, double> {x_plus, x_min, t, z, gamma, f_q, c_q, e_q, f_aq, c_aq, e_aq};
}


#endif /* ifndef READ */
