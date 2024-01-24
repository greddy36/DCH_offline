#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>

void XsecLimit_2023() {
    const int nPoints = 9;

    double mass[nPoints] = {500, 600, 700, 800, 900, 1000, 1100, 1200, 1300};
    double xsec[nPoints] = {2.720, 1.950, 0.982, 0.716, 0.540, 0.408, 0.305, 0.289, 0.260};

    double c1 = 0.25;
    double xsec1[nPoints];
    for (int i = 0; i < nPoints; ++i) {
        xsec1[i] = xsec[i] * c1 * c1;
    }

    double c2 = 0.2;
    double xsec2[nPoints];
    for (int i = 0; i < nPoints; ++i) {
        xsec2[i] = xsec[i] * c2 * c2;
    }

    double c3 = 0.15;
    double xsec3[nPoints];
    for (int i = 0; i < nPoints; ++i) {
        xsec3[i] = xsec[i] * c3 * c3;
    }

    TGraph *tg1 = new TGraph(nPoints, mass, xsec1);
    tg1->SetLineColor(4);
    tg1->SetMarkerColor(4);
    tg1->SetMarkerStyle(7);
    tg1->SetLineWidth(3);
    tg1->SetLineStyle(9);

    TGraph *tg2 = new TGraph(nPoints, mass, xsec2);
    tg2->SetLineColor(6);
    tg2->SetMarkerColor(6);
    tg2->SetMarkerStyle(7);
    tg2->SetLineWidth(3);
    tg2->SetLineStyle(7);

    TGraph *tg3 = new TGraph(nPoints, mass, xsec3);
    tg3->SetLineColor(2);
    tg3->SetMarkerColor(2);
    tg3->SetMarkerStyle(7);
    tg3->SetLineWidth(3);
    tg3->SetLineStyle(5);

    // Previous Limits
    /*double prevL[nPoints] = {2.03, 1.20, 0.54, 0.26, 0.18, 0.16, 0.13};
    TGraph *tgp = new TGraph(nPoints, mass, prevL);
    tgp->SetLineWidth(3);*/

    // Observed cross sections
    double obs[nPoints] = {0.3095, 0.1690, 0.0587, 0.0435, 0.0300, 0.0126, 0.0096};
    TGraph *obsg = new TGraph(nPoints, mass, obs);
    obsg->SetMarkerColor(1);
    obsg->SetMarkerStyle(7);
    obsg->SetLineWidth(4);

    // Expected bands
    double exp_bands[nPoints][6] = {
        {700, 0.3047, 0.1512, 0.6427, 0.2087, 0.4516},
        // ... (fill in the rest of the values)
    };

    TGraphAsymmErrors *exp1g = new TGraphAsymmErrors(nPoints, mass, exp_bands[0], 0, 0, exp_bands[4], exp_bands[5]);
    exp1g->SetFillColor(3);

    TGraphAsymmErrors *exp2g = new TGraphAsymmErrors(nPoints, mass, exp_bands[0], 0, 0, exp_bands[2], exp_bands[3]);
    exp2g->SetFillColor(5);

    // Create and draw the canvas
    TCanvas *canvas = new TCanvas("canvas", "Limit Plot", 800, 600);
    exp2g->Draw("AF");
    exp1g->Draw("F");
    obsg->Draw("LP");
    tg1->Draw("LP");
    tg2->Draw("LP");
    tg3->Draw("LP");
    //tgp->Draw("L");

    // Customize the axes, title, and legend (as needed)

    // Save the plot as an image or display it
    // canvas->SaveAs("limit_plot.png");
}
