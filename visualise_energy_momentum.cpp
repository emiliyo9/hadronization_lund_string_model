#include "read.h"
#include <TGApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <tuple>
#include <vector>
#include <cmath>
#include <iostream>

int main(int argc, char *argv[])
{
    TApplication * menergyApp = new TApplication("Test", &argc, argv);
    TCanvas *c1 = new TCanvas("c");

    std::ifstream in;
    in.open("./output_breakpoints.txt");

    std::tuple<double, double, double, double, double, char, char, double, char, char, double> line = readBreakpointLine(in);
    std::vector<double> energy;
    std::vector<double> p_z;
    while(!in.eof()){
        energy.push_back(std::get<0>(line));
        p_z.push_back(std::get<1>(line));
        std::cout << energy.back() << ", " << p_z.back() << std::endl;
        if(std::isinf(energy.back()) || std::isinf(p_z.back())){
            energy.pop_back();
            p_z.pop_back();
        }
        //energy.push_back(std::get<4>(line));
        //p_z.push_back(std::get<5>(line));
        line = readBreakpointLine(in);
    }

    TGraph* g = new TGraph(energy.size(), &p_z[0], &energy[0]);
    
    g->SetMarkerColor(4);
    g->SetMarkerStyle(21);
    g->Draw("AP");
    menergyApp->Run();
}
