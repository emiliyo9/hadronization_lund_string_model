#include "read.h"
#include <TH1.h>
#include <TF1.h>
#include <TGApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <tuple>
#include <iostream>
#include <fstream>
#include <TMath.h>

double fDistribution(double *x, double *par)
{
    return par[0] * TMath::Power(1-x[0], par[1])/x[0] * TMath::Exp(-par[2]*TMath::Power(par[3], 2) / x[0]);
}

int main(int argc, char *argv[])
{
    TApplication * myApp = new TApplication("Test", &argc, argv);
    TCanvas *c1 = new TCanvas("c");

    TH1D* h = new TH1D("h", "test", 1000, 0, 1);

    std::ifstream in;
    in.open("output.txt");

    std::tuple<double, double, long double, long double, double, int, char, char, double, char, char, double> line = readLine(in);
    while(!in.eof())
    {
        h->Fill(std::get<1>(line));
        line = readLine(in);
    }
    in.close();

    TF1* fdist = new TF1("fdist", fDistribution, 0, 1, 4);
    fdist->SetParameters(10, 1.,1.,0.13);
    fdist->FixParameter(3, 0.1349768);
    fdist->SetParNames("scale fact", "a", "b", "mass");
    fdist->SetNpx(1000);
    h->Fit(fdist);
    
    h->Draw();
    fdist->Draw("same");
    //fdist->Draw();
    myApp->Run();
}
