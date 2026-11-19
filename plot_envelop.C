#include <TFile.h>
#include <TKey.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TSystem.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

void plot_envelop(
    const char* filename = "combined_hist_.root",
    const char* variable = "LT",
    const char* outputDir = "syst_plots")
{
    TFile file(filename, "READ");
    if (file.IsZombie()) {
        std::cerr << "Cannot open " << filename << '\n';
        return;
    }

	vector<string> CHANNELS = {
		"tau0",
		"tau1",
		"tau2",
		"tau3",
		"lep3tau0",
		"lep3tau1",
		"lep3tau2",
	};
	vector<string> SAMPLES = { "M1000",
	    "DY",
		"VV",
		"VVV",
		"ttV",
		"WJ",
		"ZZ",
		"ST",
		"TTbar",
		"other",
	};
	for (auto& channel : CHANNELS){
	for (auto& sample : SAMPLES){
		const std::string prefix =
		    std::string("h_") + variable + "_" + channel + "_";
		const std::string suffix = std::string("_") + sample;
		const std::string nominalName = prefix + sample;

		TH1* nominal = nullptr;
		file.GetObject(nominalName.c_str(), nominal);

		if (!nominal) {
		    std::cerr << "Missing nominal: " << nominalName << '\n';
		    return;
		}

		// Discover systematic names from both Up and Down variations.
		std::set<std::string> systematics;
		TIter next(file.GetListOfKeys());

		while (auto key = static_cast<TKey*>(next())) {
		    const std::string name = key->GetName();

		    if (name.size() <= prefix.size() + suffix.size())
		        continue;

		    if (name.compare(0, prefix.size(), prefix) != 0 ||
		        name.compare(name.size() - suffix.size(),
		                     suffix.size(), suffix) != 0)
		        continue;

		    const std::string middle = name.substr(
		        prefix.size(),
		        name.size() - prefix.size() - suffix.size());

		    for (const std::string direction : {"Up", "Down"}) {
		        if (middle.size() > direction.size() &&
		            middle.compare(middle.size() - direction.size(),
		                           direction.size(), direction) == 0) {
		            systematics.insert(
		                middle.substr(0, middle.size() - direction.size()));
		        }
		    }
		}

		gSystem->mkdir(outputDir, true);

		for (const auto& syst : systematics) {
		    const std::string upName = prefix + syst + "Up" + suffix;
		    const std::string downName = prefix + syst + "Down" + suffix;

		    TH1 *up = nullptr, *down = nullptr;
		    file.GetObject(upName.c_str(), up);
		    file.GetObject(downName.c_str(), down);

		    if (!up || !down) {
		        std::cerr << "Skipping " << syst << ": missing "
		                  << (!up ? upName : downName) << '\n';
		        continue;
		    }

		    TH1* histograms[] = {nominal, up, down};
		    const int colors[] = {kBlack, kRed, kBlue};

		    // Find the full range directly from bin contents.
		    double ymin = 0., ymax = 0.;
		    for (int i = 0; i < 3; ++i) {
		        TH1* h = histograms[i];
		        h->SetLineColor(colors[i]);
		        h->SetLineWidth(2);
		        h->SetFillStyle(0);
		        h->SetStats(false);

		        for (int bin = 1; bin <= h->GetNbinsX(); ++bin) {
		            ymin = std::min(ymin, h->GetBinContent(bin));
		            ymax = std::max(ymax, h->GetBinContent(bin));
		        }
		    }

		    const double span = ymax > ymin ? ymax - ymin : 1.;
		    nominal->SetMinimum(ymin < 0 ? ymin - 0.1 * span : 0.);
		    nominal->SetMaximum(ymax + 0.2 * span);

		    const std::string title =
		        std::string(variable) + " / " + channel + " / " +
		        sample + " / " + syst;
		    nominal->SetTitle(title.c_str());

		    TCanvas canvas("overlay", "Systematic templates", 900, 700);
		    nominal->Draw("HIST");
		    up->Draw("HIST SAME");
		    down->Draw("HIST SAME");
		    nominal->Draw("HIST SAME");

		    TLegend legend(0.58, 0.72, 0.89, 0.89);
		    legend.SetBorderSize(0);
		    legend.SetFillStyle(0);
		    legend.AddEntry(nominal, "Nominal", "l");
		    legend.AddEntry(up, (syst + " Up").c_str(), "l");
		    legend.AddEntry(down, (syst + " Down").c_str(), "l");
		    legend.Draw();

		    const std::string output =
		        std::string(outputDir) + "/" + nominalName +
		        "_" + syst + ".png";
		    canvas.SaveAs(output.c_str());

		    std::cout << syst
		              << ": nominal=" << nominal->Integral()
		              << ", Up=" << up->Integral()
		              << ", Down=" << down->Integral() << '\n';
		}

		if (systematics.empty())
		    std::cerr << "No systematic variations found for "
		              << nominalName << '\n';
	}}//for CHANNELS and SAMPLES
}