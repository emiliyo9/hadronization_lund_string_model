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
    TApplication * myApp = new TApplication("Test", &argc, argv);
    TCanvas *c1 = new TCanvas("c");

    std::ifstream in;
    in.open("./output_mesons.txt");

    std::tuple<double, double, double, double, double, double, double, double, int, char, char, double, char, char, double> line = readMesonLine(in);
    std::vector<double> y;
    std::vector<double> y_tau;
    while(!in.eof()){
        y.push_back(std::log10((std::get<6>(line)+std::get<7>(line))/(std::get<6>(line)-std::get<7>(line)))/2.);
        y_tau.push_back(std::log10((std::get<4>(line)+std::get<5>(line))/(std::get<4>(line)-std::get<5>(line)))/2.);
        std::cout << y.back() << ", " << y_tau.back() << std::endl;
        
        if(std::isinf(y.back()) || std::isinf(y_tau.back())){
            y.pop_back();
            y_tau.pop_back();
        }
        
        //y.push_back(std::get<4>(line));
        //y_tau.push_back(std::get<5>(line));
        line = readMesonLine(in);
    }

    TGraph* g = new TGraph(y.size(), &y_tau[0], &y[0]);
    
    g->SetMarkerColor(4);
    g->SetMarkerStyle(21);
    g->Draw("AP");
    myApp->Run();
}
