#include "TMath.h"
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TFile.h"

void tmp(){
	TFile *_file1 = TFile::Open("hist_2D/HppM500.root");
	TFile *_file2 = TFile::Open("hist_2D/bkg.root");
	TH2D *hist1 = (TH2D*)_file1->Get("0tau/h2");
	TH2D *hist2 = (TH2D*)_file2->Get("3tau/h2");
	hist1->Draw("colz");
	hist2->SetStats(0);
	hist1->SetLineColor(kBlack);
	
	//hist1->Draw("same");
	
	/*// Compute weighted mean
    double sum_w = 0, mean_x = 0, mean_y = 0;
    for (int i = 1; i <= hist2->GetNbinsX(); ++i) {
        for (int j = 1; j <= hist2->GetNbinsY(); ++j) {
            double w = hist2->GetBinContent(i, j);
            double x = hist2->GetXaxis()->GetBinCenter(i);
            double y = hist2->GetYaxis()->GetBinCenter(j);
            sum_w += w;
            mean_x += x * w;
            mean_y += y * w;
        }
    }
    mean_x /= sum_w;
    mean_y /= sum_w;

    // Compute covariance matrix
    double cov_xx = 0, cov_yy = 0, cov_xy = 0;
    for (int i = 1; i <= hist2->GetNbinsX(); ++i) {
        for (int j = 1; j <= hist2->GetNbinsY(); ++j) {
            double w = hist2->GetBinContent(i, j);
            double x = hist2->GetXaxis()->GetBinCenter(i);
            double y = hist2->GetYaxis()->GetBinCenter(j);
            cov_xx += w * (x - mean_x) * (x - mean_x);
            cov_yy += w * (y - mean_y) * (y - mean_y);
            cov_xy += w * (x - mean_x) * (y - mean_y);
        }
    }
    cov_xx /= sum_w;
    cov_yy /= sum_w;
    cov_xy /= sum_w;

    // Eigenvalues for ellipse axes (semi-major and semi-minor)
    double trace = cov_xx + cov_yy;
    double det = cov_xx * cov_yy - cov_xy * cov_xy;
    double lambda1 = trace / 2 + sqrt( (trace * trace) / 4 - det );
    double lambda2 = trace / 2 - sqrt( (trace * trace) / 4 - det );

    double a = sqrt(lambda1); // semi-major
    double b = sqrt(lambda2); // semi-minor

    // Angle of rotation
    double angle = 0.5 * atan2(2 * cov_xy, cov_xx - cov_yy);

    // Create ellipse points (e.g., 1σ contour)
    const int N = 100;
    TGraph* ellipse = new TGraph(N + 1);
    for (int i = 0; i <= N; ++i) {
        double t = 2 * TMath::Pi() * i / N;
        double xe = a * cos(t);
        double ye = b * sin(t);
        double xr = xe * cos(angle) - ye * sin(angle);
        double yr = xe * sin(angle) + ye * cos(angle);
        ellipse->SetPoint(i, mean_x + xr, mean_y + yr);
    }

    // Plot
    TCanvas* c = new TCanvas("c", "2D Histogram + Ellipse", 800, 600);
    hist2->Draw("COLZ");
    ellipse->SetLineColor(kRed);
    ellipse->SetLineWidth(2);
    ellipse->Draw("L SAME");*/
}



