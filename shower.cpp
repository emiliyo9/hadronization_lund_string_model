#include "shower.h"
#include "utils.h"
#include <TMath.h>
#include <fstream>
#include <iostream>

Shower::Shower(double E_cm, Quark start_quark, Antiquark start_antiquark, TRandom3* r):
    E_cm(E_cm),
    m_sq_av(TMath::Power(this->E_cm, 2)),
    r(r)
{
    this->startFromQuark = r->Integer(2);
    if(this->startFromQuark){
        this->breakpoints.push_back(new Breakpoint(1, 0, 0, 0, 0, start_quark, start_antiquark));
    } else {
        this->breakpoints.push_back(new Breakpoint(0, 1, 0, 0, 0, start_quark, start_antiquark));
    }
    this->hadronize();
}

double Shower::distribution(double a, double b, double m, double z)
{
    return TMath::Power(1-z, a)/z * TMath::Exp(-b*TMath::Power(m, 2) / z);
}

double Shower::getNextFraction(double a, double b, double m)
{
    double x = this->r->Uniform(0,1);
    double y = this->r->Uniform(0,20);
    while (y > this->distribution(a, b, m, x))
    {
        x = r->Uniform(0,1);
        y = r->Uniform(0,20);
    }
    return x;
}

void Shower::hadronize()
{
    if (this->startFromQuark) {
        this->hadronizeQuark();
    } else {
        this->hadronizeAntiquark();
    }
    this->breakpoints.pop_back();
}

void Shower::hadronizeQuark()
{
    std::tuple<double, char> nextConf = getMassFlavor(this->breakpoints[0]->getQuark().getFlavor(), this->r);
    while(this->m_sq_av >= TMath::Power(std::get<0>(nextConf), 2))
    {
        double frac = this->getNextFraction(1,1,std::get<0>(nextConf));

        double x_plus_m = frac*this->breakpoints.back()->getXPlus();
        double x_min_m = TMath::Power(std::get<0>(nextConf), 2) / (x_plus_m*TMath::Power(this->E_cm, 2));

        double x_plus_b = (1-frac)*this->breakpoints.back()->getXPlus();
        double x_min_b = this->breakpoints.back()->getXMin() + x_min_m;

        double gamma = (1-frac)*(this->breakpoints.back()->getGamma() + TMath::Power(std::get<0>(nextConf), 2)/frac);

        double E = (x_plus_m+x_min_m) * this->E_cm / 2.;
        double p_z = (x_plus_m-x_min_m) * this->E_cm / 2.;

        double t_b = (x_plus_b+x_min_b) * this->E_cm / 2.;
        double z_b = (x_plus_b-x_min_b) * this->E_cm / 2.;

        double t_m = (this->breakpoints.back()->getTime()+t_b) / 2.;
        double z_m = (this->breakpoints.back()->getZ()+z_b) / 2.;

        Quark q(std::get<1>(nextConf), this->breakpoints.back()->getQuark().getColor());
        Antiquark aq(std::get<1>(nextConf), this->breakpoints.back()->getQuark().getColor());

        Meson *m = new Meson(std::get<0>(nextConf), frac, x_plus_m, x_min_m, t_m, z_m, E, p_z, this->breakpoints.back()->getQuark(), aq);
        this->mesons.push_back(m);

        Breakpoint *b = new Breakpoint(x_plus_b, x_min_b, t_b, z_b, gamma, q, aq);
        this->breakpoints.push_back(b);

        //m_sq_av-=TMath::Power(std::get<0>(nextConf),2);
        m_sq_av = x_plus_b*(1-x_min_b) * TMath::Power(this->E_cm/2,2);
        nextConf = getMassFlavor(this->breakpoints.back()->getAntiquark().getFlavor(), this->r);
    }
}

void Shower::hadronizeAntiquark()
{
    std::tuple<double, char> nextConf = getMassFlavor(this->breakpoints[0]->getAntiquark().getFlavor(), this->r);
    while(this->m_sq_av >= TMath::Power(std::get<0>(nextConf), 2))
    {
        double frac = this->getNextFraction(1,1,std::get<0>(nextConf));

        double x_min_m = frac*this->breakpoints.back()->getXMin();
        double x_plus_m = TMath::Power(std::get<0>(nextConf), 2) / (x_min_m*TMath::Power(this->E_cm, 2));
        //double x_plus_m = TMath::Power(std::get<0>(nextConf), 2) / (x_min_m);

        double x_min_b = (1-frac)*this->breakpoints.back()->getXMin();
        double x_plus_b = this->breakpoints.back()->getXPlus() + x_plus_m;
        //double x_plus_b = this->breakpoints.back()->getXPlus() + x_plus_m;

        double gamma = (1-frac)*(this->breakpoints.back()->getGamma() + TMath::Power(std::get<0>(nextConf), 2)/frac);

        double E = (x_plus_m+x_min_m) * this->E_cm / 2.;
        double p_z = (x_plus_m-x_min_m) * this->E_cm / 2.;

        double t_b = (x_plus_b+x_min_b) * this->E_cm / 2.;
        double z_b = (x_plus_b-x_min_b) * this->E_cm / 2.;

        double t_m = (this->breakpoints.back()->getTime()+t_b) / 2.;
        double z_m = (this->breakpoints.back()->getZ()+z_b) / 2.;

        Quark q(std::get<1>(nextConf), this->breakpoints.back()->getAntiquark().getColor());
        Antiquark aq(std::get<1>(nextConf), this->breakpoints.back()->getAntiquark().getColor());

        Meson *m = new Meson(std::get<0>(nextConf), frac, x_plus_m, x_min_m, t_m, z_m, E, p_z, q, this->breakpoints.back()->getAntiquark());
        this->mesons.push_back(m);

        Breakpoint *b = new Breakpoint(x_plus_b, x_min_b, t_b, z_b, gamma, q, aq);
        this->breakpoints.push_back(b);

        //m_sq_av-=TMath::Power(std::get<0>(nextConf),2);
        m_sq_av = x_min_b*(1-x_plus_b) * TMath::Power(this->E_cm/2,2);
        nextConf = getMassFlavor(this->breakpoints.back()->getQuark().getFlavor(), this->r);
    }
}

void Shower::info()
{
    std::cout << "----------" << std::endl;
    std::cout << "| Shower |" << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << "Started hadronization from quark: " << this->startFromQuark << std::endl;

    for (auto i : this->mesons) {
        i->info();
    }
}

void Shower::saveMesons(std::ofstream& out)
{
    for (auto m : this->mesons) {
        out << m->getMass() << "\t";
        out << m->getFrac() << "\t";
        out << m->getXPlus() << "\t";
        out << m->getXMin() << "\t";
        out << m->getTime() << "\t";
        out << m->getZ() << "\t";
        out << m->getE() << "\t";
        out << m->getPz() << "\t";
        out << m->getCharge() << "\t";
        out << m->getQuark().getFlavor() << "\t";
        out << m->getQuark().getColor() << "\t";
        out << m->getQuark().getCharge() << "\t";
        out << m->getAntiquark().getFlavor() << "\t";
        out << m->getAntiquark().getColor() << "\t";
        out << m->getAntiquark().getCharge() << std::endl;
    }
}

void Shower::saveBreakpoints(std::ofstream& out)
{
    for (auto b : this->breakpoints) {
        out << b->getXPlus() << "\t";
        out << b->getXMin() << "\t";
        out << b->getTime() << "\t";
        out << b->getZ() << "\t";
        out << b->getGamma() << "\t";
        out << b->getQuark().getFlavor() << "\t";
        out << b->getQuark().getColor() << "\t";
        out << b->getQuark().getCharge() << "\t";
        out << b->getAntiquark().getFlavor() << "\t";
        out << b->getAntiquark().getColor() << "\t";
        out << b->getAntiquark().getCharge() << std::endl;
    }
}
