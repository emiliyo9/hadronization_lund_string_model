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

double gammaDistribution(double *x, double *par)
{
    return par[0] * TMath::Power(x[0], par[1]) * TMath::Exp(-par[2]*x[0]);
}

int main(int argc, char *argv[])
{
    TApplication * myApp = new TApplication("Test", &argc, argv);
    TCanvas *c1 = new TCanvas("c");

    TH1D* h = new TH1D("h", "test", 1000, 0, 10);

    std::ifstream in;
    in.open("./output_breakpoints.txt");

    std::tuple<double, double, double, double, double, char, char, double, char, char, double> line = readBreakpointLine(in);
    while(!in.eof())
    {
        h->Fill(std::get<4>(line));
        line = readBreakpointLine(in);
    }

    TF1* gammadist = new TF1("gammadist", gammaDistribution, 0, 10, 3);
    gammadist->SetParameters(5, 1.,1.);
    gammadist->SetParNames("scale fact", "a", "b");
    gammadist->SetNpx(1000);
    h->Fit(gammadist);
    
    h->Draw();
    gammadist->Draw("same");
    //fdist->Draw();
    myApp->Run();
}
