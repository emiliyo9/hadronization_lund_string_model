#ifndef UTILS
#define UTILS 

#include <TRandom3.h>
#include <vector>
#include <tuple>

std::vector<std::tuple<double, char>> u = {{0.1349768, 'u'}, {0.13957039, 'd'}};
//std::vector<std::tuple<double, char>> u = {{0.1349768, 'u'}};
std::vector<std::tuple<double, char>> d = {{0.1349768, 'd'}, {0.13957039, 'u'}};

std::tuple<double, char> getMassFlavor(char flavor, TRandom3* r)
{
    switch (flavor)
    {
        case 'u':
            return u[r->Integer(u.size())];
        case 'd':
            return d[r->Integer(d.size())];
        default:
            throw "Flavor does not exist";
    }
}

#endif /* ifndef UTILS */
