#include <TRandom3.h>
#include <TF1.h>
#include <cmath>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraph.h>
#include <iostream>
#include <TMath.h>

/*
 * This is only an initial try to get an idea for the needed classes
*/

double probDistribution(double a, double b, double m, double z)
{
    return TMath::Power(1-z, a)/z * TMath::Exp(-b*TMath::Power(m, 2) / z);
}

double getRandom(double a, double b, double m, TRandom3* r)
{
    double x = r->Uniform(0,1);
    double y = r->Uniform(0,20);
    while (y > probDistribution(a, b, m, x))
    {
        x = r->Uniform(0,1);
        y = r->Uniform(0,20);
    }
    return x;
}

int main(int argc, char *argv[])
{
    // constants
    double kappa = 1.; //GeV/fm
    double c = 1.; //natural units
    double hbar = 1.;
    double a = 1;
    double b = 1;

    // settings of experiments
    double E_cm = 0.5; //GeV
    double m_h = 0.1349768; //GeV (pion -)

    // assume E_quark and E_antiquark are the same
    double m_sq_av = std::pow(E_cm, 2.);

    // setup random number generator
    TRandom3* r = new TRandom3();
    
    /*
    TApplication * myApp = new TApplication("Test", &argc, argv);
    TCanvas *c1 = new TCanvas("c");
    TH1D* h = new TH1D("h", "test", 100000, 0, 1);
    for (int i = 0; i < 10000000; i++) {
        h->Fill(getRandom(a,b,m_h,r));
    }
    h->Draw();
    myApp->Run();
    */
    
    double x_plus_prev = 1;
    double gamma_prev = 0;
    while(m_sq_av >= m_h)
    {
        double z_plus = getRandom(a,b,m_h,r);
        double x_plus = z_plus*x_plus_prev;
        double x_min = TMath::Power(m_h, 2) / (x_plus*TMath::Power(E_cm, 2));
        x_plus_prev*=1-z_plus;
        double gamma = (1-z_plus)*(gamma_prev + TMath::Power(m_h, 2)/z_plus);
        gamma_prev = gamma;
        m_sq_av-=TMath::Power(m_h,2);
        std::cout << z_plus << "," << x_plus_prev << "," << x_plus << "," << x_min << "," << gamma << std::endl;
    }
}
