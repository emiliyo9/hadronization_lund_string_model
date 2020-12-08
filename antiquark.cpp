#include "antiquark.h"
#include <algorithm>
#include <list>
#include <iostream>

Antiquark::Antiquark(char flavor, char color)
{
    std::list<char> flavors({ 'u', 'd', 's', 'c', 't', 'b' });
    if ((std::find(flavors.begin(), flavors.end(), flavor)) == flavors.end()) {
        throw "The flavor of antiquarks can only be u, d, s, c, t or b";
    } else {
        this->flavor = flavor;
    }
    std::list<char> colors({ 'b', 'g', 'r' });
    if ((std::find(colors.begin(), colors.end(), color)) == colors.end()) {
        throw "The color of antiquarks can only be negative b, g or r";
    } else {
        this->color = color;
    }
    if (flavor == 'u' || flavor == 's' || flavor == 't') {
        this->charge = -2./3;
    } else {
        this->charge = 1./3;
    }
}

void Antiquark::info()
{
    std::cout << "Antiquark" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "flavor: " << this->flavor << std::endl;
    std::cout << "color: " << this->color << std::endl;
    std::cout << "charge: " << this->charge << std::endl;
}
