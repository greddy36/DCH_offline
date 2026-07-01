#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>

#include <TFile.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "include/Xsections.C"
#include "include/cat.h"

// ============================================================
// Analysis channels
// ============================================================

static const std::vector<std::string> kChannels = {
    "VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
    "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
    "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
    "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
    "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
    "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
    "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt",
    "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_emm", "v_mmm", "v_mmt",
    "v_ett", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
    "v_eett", "v_emmt", "v_emtt", "v_ettt", "v_mmmt", "v_mmtt", "v_mttt"
};

static const std::unordered_set<std::string> kChannelSet(kChannels.begin(), kChannels.end());

// ============================================================
// Physics containers
// ============================================================

struct Lepton {
    double pt = 0.;
    double eta = 0.;
    double phi = 0.;
    double mass = 0.;
    int charge = 0;
    double d0 = 0.;
    double dZ = 0.;
    double iso = 0.;

    Lepton() = default;
    Lepton(double ipt, double ieta, double iphi, double imass, int icharge,
           double id0, double idZ, double iiso)
        : pt(ipt), eta(ieta), phi(iphi), mass(imass), charge(icharge),
          d0(id0), dZ(idZ), iso(iiso) {}
};

struct EventData {
    std::string cat;
    double met = 0.;
    double metphi = 0.;

    double pt[4]   = {0.,0.,0.,0.};
    double eta[4]  = {0.,0.,0.,0.};
    double phi[4]  = {0.,0.,0.,0.};
    double m[4]    = {0.,0.,0.,0.};
    int    q[4]    = {0,0,0,0};
    double d0[4]   = {0.,0.,0.,0.};
    double dZ[4]   = {0.,0.,0.,0.};
    double iso[4]  = {0.,0.,0.,0.};
    double tauES[4]= {1.,1.,1.,1.};
};

struct EventResult {
    bool keep = false;

    std::string tau_channel = "";
    std::string lep_channel = "";

    double evtwt = 0.;
    double met = -999.;
    double LT  = -999.;
    double mT  = -999.;

    double mZ1 = -999.;
    double mZ2 = -999.;
    double mH1 = -999.;
    double mH2 = -999.;

    double pt1 = -999., pt2 = -999., pt3 = -999., pt4 = -999.;
    double eta1 = -999., eta2 = -999., eta3 = -999., eta4 = -999.;
    double phi1 = -999., phi2 = -999., phi3 = -999., phi4 = -999.;
    double dRll = -999.;
};

// ============================================================
// Utilities
// ============================================================

std::vector<std::string> ListInputFiles(const char *ext = "root") {
    std::vector<std::string> out;

    const char *inDir = ".";
    char *dir = gSystem->ExpandPathName(inDir);
    void *dirp = gSystem->OpenDirectory(dir);
    const char *entry = nullptr;

    while ((entry = (char*)gSystem->GetDirEntry(dirp))) {
        TString str = entry;
        if (str.EndsWith(ext)) {
            out.emplace_back(gSystem->ConcatFileName(dir, entry));
        }
    }

    gSystem->FreeDirectory(dirp);
    delete [] dir;
    return out;
}

TLorentzVector MakeP4(double pt, double eta, double phi, double m) {
    TLorentzVector v;
    v.SetPtEtaPhiM(pt, eta, phi, m);
    return v;
}

TLorentzVector LepV(const EventData &ev, int n) {
    TLorentzVector lepV;
    if (n < 1 || n > 4) {
        lepV.SetPtEtaPhiM(0,0,0,0);
        return lepV;
    }
    const int i = n - 1;
    // Preserving your old behavior: massless leptons in LepV
    lepV.SetPtEtaPhiM(ev.pt[i], ev.eta[i], ev.phi[i], 0.0);
    return lepV;
}

double dPhi(double phi1, double phi2) {
    const double pi = TMath::Pi();
    return std::fmin(std::fabs(phi2 - phi1), 2.0 * pi - std::fabs(phi2 - phi1));
}

double getDR(double eta1, double phi1, double eta2, double phi2) {
    return std::sqrt(std::pow(dPhi(phi1, phi2), 2) + std::pow(eta2 - eta1, 2));
}

double deltaR(const TLorentzVector& v1, const TLorentzVector& v2) {
    return getDR(v1.Eta(), v1.Phi(), v2.Eta(), v2.Phi());
}

bool isDuplicate(const Lepton &lepton1, const Lepton &lepton2) {
    return getDR(lepton1.eta, lepton1.phi, lepton2.eta, lepton2.phi) <= 0.4;
}

EventData MakeEventData(
    int cat,
    double met, double metphi,

    double pt_1, double eta_1, double phi_1, double m_1, double q_1, double d0_1, double dZ_1, double iso_1,
    double pt_2, double eta_2, double phi_2, double m_2, double q_2, double d0_2, double dZ_2, double iso_2,
    double pt_3, double eta_3, double phi_3, double m_3, double q_3, double d0_3, double dZ_3, double iso_3,
    double pt_4, double eta_4, double phi_4, double m_4, double q_4, double d0_4, double dZ_4, double iso_4,

    double TauES_1, double TauES_2, double TauES_3, double TauES_4
) {
    EventData ev;
    ev.cat = numberToCat(cat);
    ev.met = met;
    ev.metphi = metphi;

    ev.pt[0]  = pt_1;  ev.eta[0] = eta_1; ev.phi[0] = phi_1; ev.m[0] = m_1; ev.q[0] = (int)q_1; ev.d0[0] = d0_1; ev.dZ[0] = dZ_1; ev.iso[0] = iso_1;
    ev.pt[1]  = pt_2;  ev.eta[1] = eta_2; ev.phi[1] = phi_2; ev.m[1] = m_2; ev.q[1] = (int)q_2; ev.d0[1] = d0_2; ev.dZ[1] = dZ_2; ev.iso[1] = iso_2;
    ev.pt[2]  = pt_3;  ev.eta[2] = eta_3; ev.phi[2] = phi_3; ev.m[2] = m_3; ev.q[2] = (int)q_3; ev.d0[2] = d0_3; ev.dZ[2] = dZ_3; ev.iso[2] = iso_3;
    ev.pt[3]  = pt_4;  ev.eta[3] = eta_4; ev.phi[3] = phi_4; ev.m[3] = m_4; ev.q[3] = (int)q_4; ev.d0[3] = d0_4; ev.dZ[3] = dZ_4; ev.iso[3] = iso_4;

    ev.tauES[0] = TauES_1;
    ev.tauES[1] = TauES_2;
    ev.tauES[2] = TauES_3;
    ev.tauES[3] = TauES_4;

    return ev;
}

EventData ApplyTauES(EventData ev) {
    for (size_t i = 0; i < ev.cat.size() && i < 4; ++i) {
        if (ev.cat[i] == 't') {
            ev.pt[i] *= ev.tauES[i];
            ev.m[i]  *= ev.tauES[i];
        }
    }
    return ev;
}

std::string applyHEMveto(const EventData& ev) {
    for (size_t i = 0; i < ev.cat.size() && i < 4; ++i) {
        if (ev.cat[i] == 'e' &&
            ev.eta[i] > -3.0 && ev.eta[i] < -1.3 &&
            ev.phi[i] > -1.57 && ev.phi[i] < -0.87 &&
            ev.pt[i] > 15.) {
            return "yes";
        }
    }
    return "no";
}

std::string pairFunc(int m, int n, const EventData& ev, double Zwindow) {
    TLorentzVector lep1 = LepV(ev, m);
    TLorentzVector lep2 = LepV(ev, n);

    int c1 = ev.q[m - 1];
    int c2 = ev.q[n - 1];

    if (c1 == c2) return "SSpair";

    if (c1 == -c2) {
        if (ev.cat[m - 1] == ev.cat[n - 1]) {
            if (ev.cat[m - 1] == 'e' || ev.cat[m - 1] == 'm') {
                return (std::abs((lep1 + lep2).M() - 91.2) < Zwindow) ? "Zwindow" : "Zv";
            } else if (ev.cat[m - 1] == 't') {
                return "ZttPair";
            }
        } else {
            return "OSDFpair";
        }
    }

    return "messed up";
}

void processPairs(const EventData& ev,
                  std::vector<std::pair<int, int>>& Z_pair,
                  std::vector<std::pair<int, int>>& Zv_pair,
                  std::vector<std::pair<int, int>>& Ztt_pair,
                  std::vector<std::pair<int, int>>& SS_pair,
                  std::vector<std::pair<int, int>>& OSDF_pair)
{
    const int len = ev.cat.size();
    std::vector<bool> used(len + 1, false);

    struct Zcand {
        int i, j;
        double diff;
    };
    std::vector<Zcand> Zcands;

    for (int m = 1; m <= len; ++m) {
        for (int n = m + 1; n <= len; ++n) {
            std::string pname = pairFunc(m, n, ev, 10.0);

            if (pname == "Zwindow") {
                double mass = (LepV(ev, m) + LepV(ev, n)).M();
                double diff = std::fabs(mass - 91.2);
                Zcands.push_back({m, n, diff});
            }
            else if (pname == "ZttPair")  Ztt_pair.push_back({m, n});
            else if (pname == "OSDFpair") OSDF_pair.push_back({m, n});
            else if (pname == "SSpair")   SS_pair.push_back({m, n});
        }
    }

    std::sort(Zcands.begin(), Zcands.end(),
              [](const Zcand& a, const Zcand& b) { return a.diff < b.diff; });

    for (auto &zcand : Zcands) {
        if (!used[zcand.i] && !used[zcand.j]) {
            Z_pair.push_back({zcand.i, zcand.j});
            used[zcand.i] = true;
            used[zcand.j] = true;
        }
    }

    for (int m = 1; m <= len; ++m) {
        if (used[m]) continue;
        for (int n = m + 1; n <= len; ++n) {
            if (used[n]) continue;
            std::string pname = pairFunc(m, n, ev, 10.0);
            if (pname == "Zv") {
                Zv_pair.push_back({m, n});
                used[m] = true;
                used[n] = true;
            }
        }
    }
}

std::vector<std::pair<int,int>> removeOverlap(const std::vector<std::pair<int,int>>& pairs, int nLep) {
    std::vector<std::pair<int,int>> clean;
    std::vector<bool> used(nLep + 1, false);

    for (const auto& p : pairs) {
        if (!used[p.first] && !used[p.second]) {
            clean.push_back(p);
            used[p.first]  = true;
            used[p.second] = true;
        }
    }
    return clean;
}

std::string classifyTauRegion(const EventData& ev, double LT, const std::vector<std::pair<int, int>>& OS_pair) {
    int Ntau = ev.cat.size() - cat_lepCount(ev.cat, 'e', 'm');
    double Zwindow = 10.0;
    double Zmass = 91.2;
    int numZ = 0;

    for (size_t i = 0; i < OS_pair.size(); i++) {
        int ia = OS_pair[i].first;
        int ib = OS_pair[i].second;
        if (ev.cat[ia - 1] == 't' || ev.cat[ia - 1] != ev.cat[ib - 1]) continue;
        double mPair = (LepV(ev, ia) + LepV(ev, ib)).M();
        if (std::abs(mPair - Zmass) <= Zwindow) numZ += 1;
    }

    if (ev.cat.size() == 2) {
        if (Ntau == 0) return (numZ == 1) ? "DYCR_0tau" : "DYveto_0tau";
        else if (Ntau == 1) return (numZ == 1) ? "DYCR_1tau" : "DYveto_1tau";
    }

    if (numZ == 0 && ev.cat.size() == 4) {
        if (Ntau == 0) return (LT < 400) ? "VR_0tau" : "SR_0tau";
        else if (Ntau == 1) return (LT < 400) ? "VR_1tau" : "SR_1tau";
        else if (Ntau == 2) return (LT < 400) ? "VR_2tau" : "SR_2tau";
        else if (Ntau == 3) return (LT < 100) ? "VR_3tau" : "SR_3tau";
    }
    else if (numZ == 0 && ev.cat.size() == 3) {
        if (Ntau == 0) return (LT < 300) ? "VR_3lep0tau" : "SR_3lep0tau";
        else if (Ntau == 1) return (LT < 200) ? "VR_3lep1tau" : "SR_3lep1tau";
        else if (Ntau == 2) return (LT < 100) ? "VR_3lep2tau" : "SR_3lep2tau";
    }
    else if (numZ > 0 && ev.cat.size() == 3) {
        if (Ntau == 0) return "CR_3lep0tau";
        else if (Ntau == 1) return "CR_3lep1tau";
        else if (Ntau == 2) return "CR_3lep2tau";
    }
    else if (numZ > 0 && ev.cat.size() == 4) {
        if (Ntau == 0) return "CR_0tau";
        else if (Ntau == 1) return "CR_1tau";
        else if (Ntau == 2) return "CR_2tau";
        else if (Ntau == 3) return "CR_3tau";
    }

    return "crap";
}

std::string classifyLepRegion(const std::string& cat_name, const std::vector<std::pair<int, int>>& pairVec) {
    std::string lepRegion = "";
    int cat_size = cat_name.size();

    int nPairs = pairVec.size();
    if (nPairs == 0) return cat_name;
    if (cat_size == 2) return cat_name;

    std::vector<bool> used(cat_name.size(), false);

    for (auto &p : pairVec) {
        lepRegion += cat_name[p.first - 1];
        lepRegion += cat_name[p.second - 1];
        used[p.first - 1] = true;
        used[p.second - 1] = true;
    }

    std::string extra = "";
    for (int i = 0; i < (int)cat_name.size(); i++) {
        if (used[i]) continue;
        extra += cat_name[i];
    }

    if (extra == "me") extra = "em";
    else if (extra == "te") extra = "et";
    else if (extra == "tm") extra = "mt";

    lepRegion += extra;
    return lepRegion;
}

EventResult ComputeEventResult(
    const std::string &fname,
    int run,
    const EventData &ev_in,

    double brWeight,
    double Generator_weight,
    double L1PreFiringWeight_Nom,
    double weightPUtruejson,

    double IDSF_1, double IDSF_2, double IDSF_3, double IDSF_4,
    double ISOSF_1, double ISOSF_2, double ISOSF_3, double ISOSF_4,
    double TauVsEleIDSF_1, double TauVsEleIDSF_2, double TauVsEleIDSF_3, double TauVsEleIDSF_4,
    double TauVsMuIDSF_1,  double TauVsMuIDSF_2,  double TauVsMuIDSF_3,  double TauVsMuIDSF_4,
    double TauVsJetIDSF_1, double TauVsJetIDSF_2, double TauVsJetIDSF_3, double TauVsJetIDSF_4,
    double TrigSF_1, double TrigSF_2, double TrigSF_3, double TrigSF_4
) {
    EventResult r;
    EventData ev = ev_in;

    const std::string cat_string = ev.cat;
    const char *cat_name = cat_string.c_str();

    int Nlep = cat_lepCount(cat_string, 'e', 'm');
    int Ntau = cat_string.size() - Nlep;

    // Keep your active event preselection logic
    // Note: q logic preserved for 4l/3l categories even though later you keep only size==2
    if (cat_string.size() <= 4) {
        int qsum4 = ev.q[0] + ev.q[1] + ev.q[2] + ev.q[3];
        int qsum3 = ev.q[0] + ev.q[1] + ev.q[2];
        //int cat_num = catStringToNumber(cat_string); // only if you have this helper; otherwise remove
        (void)qsum4;
        (void)qsum3;
        //(void)cat_num;
    }

    // Original logic used integer cat, so reproduce that check outside using RDF Filter before Define if needed.
    // Here we only keep the size==2 path you currently use.
    if (cat_string.size() != 2) return r;

    // Duplicate veto
    std::vector<Lepton> leptons = {
        Lepton(ev.pt[0], ev.eta[0], ev.phi[0], ev.m[0], ev.q[0], ev.d0[0], ev.dZ[0], ev.iso[0]),
        Lepton(ev.pt[1], ev.eta[1], ev.phi[1], ev.m[1], ev.q[1], ev.d0[1], ev.dZ[1], ev.iso[1]),
        Lepton(ev.pt[2], ev.eta[2], ev.phi[2], ev.m[2], ev.q[2], ev.d0[2], ev.dZ[2], ev.iso[2]),
        Lepton(ev.pt[3], ev.eta[3], ev.phi[3], ev.m[3], ev.q[3], ev.d0[3], ev.dZ[3], ev.iso[3])
    };

    bool foundDup = false;
    for (size_t w = 0; w < cat_string.size() && !foundDup; ++w) {
        for (size_t x = w + 1; x < cat_string.size(); ++x) {
            if (isDuplicate(leptons[w], leptons[x])) {
                foundDup = true;
                break;
            }
        }
    }
    if (foundDup) return r;

    // Event weight
    double evtwt_nom = brWeight * Generator_weight;

    if (fname.find("_2018.") != std::string::npos) {
        if (XSec(fname) == 1 && run >= 319077 && applyHEMveto(ev) == "yes") return r;
        if (XSec(fname) != 1 && applyHEMveto(ev) == "yes") evtwt_nom *= 0.35;
    }

    ev = ApplyTauES(ev);

    if (XSec(fname) != 1) {
        evtwt_nom *= L1PreFiringWeight_Nom * weightPUtruejson;

        if (cat_string.size() < 3) {
            evtwt_nom *= IDSF_1 * IDSF_2 * ISOSF_1 * ISOSF_2 *
                         TauVsEleIDSF_1 * TauVsEleIDSF_2 *
                         TauVsMuIDSF_1  * TauVsMuIDSF_2  *
                         TauVsJetIDSF_1 * TauVsJetIDSF_2;

            if (TrigSF_1 != 1.) evtwt_nom *= TrigSF_1;
            else if (TrigSF_2 != 1.) evtwt_nom *= TrigSF_2;
        }
        else if (cat_string.size() == 3) {
            evtwt_nom *= IDSF_1 * IDSF_2 * IDSF_3 *
                         ISOSF_1 * ISOSF_2 * ISOSF_3 *
                         TauVsEleIDSF_1 * TauVsEleIDSF_2 * TauVsEleIDSF_3 *
                         TauVsMuIDSF_1  * TauVsMuIDSF_2  * TauVsMuIDSF_3  *
                         TauVsJetIDSF_1 * TauVsJetIDSF_2 * TauVsJetIDSF_3;
        }
        else {
            evtwt_nom *= IDSF_1 * IDSF_2 * IDSF_3 * IDSF_4 *
                         ISOSF_1 * ISOSF_2 * ISOSF_3 * ISOSF_4 *
                         TauVsEleIDSF_1 * TauVsEleIDSF_2 * TauVsEleIDSF_3 * TauVsEleIDSF_4 *
                         TauVsMuIDSF_1  * TauVsMuIDSF_2  * TauVsMuIDSF_3  * TauVsMuIDSF_4  *
                         TauVsJetIDSF_1 * TauVsJetIDSF_2 * TauVsJetIDSF_3 * TauVsJetIDSF_4;
        }

        if (cat_string.size() >= 3) {
            if      (TrigSF_1 != 1.) evtwt_nom *= TrigSF_1;
            else if (TrigSF_2 != 1.) evtwt_nom *= TrigSF_2;
            else if (TrigSF_3 != 1.) evtwt_nom *= TrigSF_3;
            else if (TrigSF_4 != 1.) evtwt_nom *= TrigSF_4;
        }
    }

    TLorentzVector MET;
    MET.SetPtEtaPhiM(ev.met, 0., ev.metphi, 0.);

    double LT = 0.;
    for (size_t i = 0; i < cat_string.size(); ++i) {
        LT += LepV(ev, i + 1).Pt();
    }

    std::vector<std::pair<int, int>> Z_pair, Zv_pair, Ztt_pair, SS_pair;
    processPairs(ev, Z_pair, Zv_pair, Ztt_pair, SS_pair, Ztt_pair);

    Zv_pair = removeOverlap(Zv_pair, (int)cat_string.size());

    auto sortByPairPt = [&](std::vector<std::pair<int,int>> &pairs) {
        std::sort(pairs.begin(), pairs.end(),
            [&](const std::pair<int,int>& a, const std::pair<int,int>& b) {
                double pt_a = (LepV(ev, a.first) + LepV(ev, a.second)).Pt();
                double pt_b = (LepV(ev, b.first) + LepV(ev, b.second)).Pt();
                return pt_a > pt_b;
            });
    };

    sortByPairPt(SS_pair);
    sortByPairPt(Z_pair);
    sortByPairPt(Zv_pair);
    sortByPairPt(Ztt_pair);

    std::vector<std::pair<int,int>> OSSF_pair, OS_pair;
    OSSF_pair.insert(OSSF_pair.end(), Z_pair.begin(), Z_pair.end());
    OSSF_pair.insert(OSSF_pair.end(), Zv_pair.begin(), Zv_pair.end());
    OSSF_pair = removeOverlap(OSSF_pair, (int)cat_string.size());

    OS_pair.insert(OS_pair.end(), OSSF_pair.begin(), OSSF_pair.end());
    OS_pair.insert(OS_pair.end(), Ztt_pair.begin(), Ztt_pair.end());
    OS_pair = removeOverlap(OS_pair, (int)cat_string.size());

    std::string tau_channel = classifyTauRegion(ev, LT, OS_pair);
    if (!kChannelSet.count(tau_channel)) return r;

    std::string lep_channel = classifyLepRegion(cat_string, OS_pair);
    if (!kChannelSet.count(lep_channel)) return r;

    // Keep the currently active histogram-filling branch from your old macro
    if (Z_pair.size() == 1) {
        double mT = (LepV(ev, Z_pair[0].first) + LepV(ev, Z_pair[0].second) + MET).Mt();
        if (cat_string.size() == 3 && !(ev.met >= 40.)) return r;

        r.keep = true;
        r.tau_channel = tau_channel;
        r.lep_channel = lep_channel;
        r.evtwt = evtwt_nom;
        r.met = ev.met;
        r.LT = LT;
        r.mT = mT;

        if (OS_pair.size() > 0) {
            r.mZ1  = (LepV(ev, OS_pair[0].first) + LepV(ev, OS_pair[0].second)).M();
            r.pt1  = LepV(ev, OS_pair[0].first).Pt();
            r.pt2  = LepV(ev, OS_pair[0].second).Pt();
            r.eta1 = LepV(ev, OS_pair[0].first).Eta();
            r.eta2 = LepV(ev, OS_pair[0].second).Eta();
            r.phi1 = LepV(ev, OS_pair[0].first).Phi();
            r.phi2 = LepV(ev, OS_pair[0].second).Phi();
            r.dRll = deltaR(LepV(ev, OS_pair[0].first), LepV(ev, OS_pair[0].second));
        }
        if (OS_pair.size() > 1) {
            r.mZ2  = (LepV(ev, OS_pair[1].first) + LepV(ev, OS_pair[1].second)).M();
            r.pt3  = LepV(ev, OS_pair[1].first).Pt();
            r.pt4  = LepV(ev, OS_pair[1].second).Pt();
            r.eta3 = LepV(ev, OS_pair[1].first).Eta();
            r.eta4 = LepV(ev, OS_pair[1].second).Eta();
            r.phi3 = LepV(ev, OS_pair[1].first).Phi();
            r.phi4 = LepV(ev, OS_pair[1].second).Phi();
        }
        if (SS_pair.size() > 0) r.mH1 = (LepV(ev, SS_pair[0].first) + LepV(ev, SS_pair[0].second)).M();
        if (SS_pair.size() > 1) r.mH2 = (LepV(ev, SS_pair[1].first) + LepV(ev, SS_pair[1].second)).M();
    }

    return r;
}

// ============================================================
// Histogram booking helper
// ============================================================

template <typename RDFNode>
void BookAndWriteByChannel(RDFNode df,
                           TFile *ofile,
                           const std::string &channelColumn,
                           const std::string &var,
                           const std::string &prefix,
                           const std::string &title,
                           int bins, double low, double high)
{
    ofile->cd();

    for (const auto &channel : kChannels) {
        auto dch = df.Filter(
            [channel](const std::string &c) { return c == channel; },
            {channelColumn}
        );

        auto h = dch.Histo1D(
            {(prefix + "_" + channel).c_str(),
             (title + " " + channel).c_str(),
             bins, low, high},
            var, "evtwt");

        h->Write();
    }
}

// ============================================================
// Main RDF macro
// ============================================================

void DCH_CR_VR_test_rdf(const char* ext = "root") {
    ROOT::EnableImplicitMT();

    auto files = ListInputFiles(ext);

    for (const auto &fname : files) {
        std::cout << fname << std::endl;

        //if (fname.find("_2018.") == std::string::npos) continue;
        if (fname.find("Hpp") > fname.length()) continue;

        TFile ifile(fname.c_str(), "READ");
        if (ifile.IsZombie()) continue;

        std::string outdir = "hist_test_nopair_DY";
        std::string oname = outdir + "/" + std::string(gSystem->BaseName(fname.c_str()));
        TFile ofile(oname.c_str(), "RECREATE");

        TH1D *hNWEvts = nullptr;
        if (XSec(fname) != 1) hNWEvts = dynamic_cast<TH1D*>(ifile.Get("hNWEvts"));
        if (!hNWEvts) hNWEvts = dynamic_cast<TH1D*>(ifile.Get("hNEvts"));
        if (hNWEvts) {
            TH1D *htmp = (TH1D*)hNWEvts->Clone("hNWEvts");
            ofile.cd();
            htmp->Write();
            delete htmp;
        }

        ROOT::RDataFrame df("Events", fname);

        // You used integer cat checks before the size==2 requirement.
        // Keep that logic as an RDF filter.
        auto df0 = df.Filter(
            [](int cat, double q_1, double q_2, double q_3, double q_4) {
            	
                if (cat <= 21 && (q_1 + q_2 + q_3 + q_4) != 0) return false;
                if (cat > 21 && cat <= 39 && std::abs(q_1 + q_2 + q_3) == 3) return false;
                return true;
            },
            {"cat", "q_1", "q_2", "q_3", "q_4"}
        );

        auto df1 = df0
            .Define("ev_raw", MakeEventData,
                {
                    "cat","met","metphi",
                    "pt_1","eta_1","phi_1","m_1","q_1","d0_1","dZ_1","iso_1",
                    "pt_2","eta_2","phi_2","m_2","q_2","d0_2","dZ_2","iso_2",
                    "pt_3","eta_3","phi_3","m_3","q_3","d0_3","dZ_3","iso_3",
                    "pt_4","eta_4","phi_4","m_4","q_4","d0_4","dZ_4","iso_4",
                    "TauES_1","TauES_2","TauES_3","TauES_4"
                }
            )
            .Define("res",
                [fname](ULong64_t run,
                        const EventData &ev_raw,
                        double brWeight,
                        double Generator_weight,
                        double L1PreFiringWeight_Nom,
                        double weightPUtruejson,

                        double IDSF_1, double IDSF_2, double IDSF_3, double IDSF_4,
                        double ISOSF_1, double ISOSF_2, double ISOSF_3, double ISOSF_4,
                        double TauVsEleIDSF_1, double TauVsEleIDSF_2, double TauVsEleIDSF_3, double TauVsEleIDSF_4,
                        double TauVsMuIDSF_1,  double TauVsMuIDSF_2,  double TauVsMuIDSF_3,  double TauVsMuIDSF_4,
                        double TauVsJetIDSF_1, double TauVsJetIDSF_2, double TauVsJetIDSF_3, double TauVsJetIDSF_4,
                        double TrigSF_1, double TrigSF_2, double TrigSF_3, double TrigSF_4)
                {
                    return ComputeEventResult(
                        fname,
                        (int)run,
                        ev_raw,
                        brWeight,
                        Generator_weight,
                        L1PreFiringWeight_Nom,
                        weightPUtruejson,

                        IDSF_1, IDSF_2, IDSF_3, IDSF_4,
                        ISOSF_1, ISOSF_2, ISOSF_3, ISOSF_4,
                        TauVsEleIDSF_1, TauVsEleIDSF_2, TauVsEleIDSF_3, TauVsEleIDSF_4,
                        TauVsMuIDSF_1,  TauVsMuIDSF_2,  TauVsMuIDSF_3,  TauVsMuIDSF_4,
                        TauVsJetIDSF_1, TauVsJetIDSF_2, TauVsJetIDSF_3, TauVsJetIDSF_4,
                        TrigSF_1, TrigSF_2, TrigSF_3, TrigSF_4
                    );
                },
                {
                    "run",
                    "ev_raw",
                    "brWeight",
                    "Generator_weight",
                    "L1PreFiringWeight_Nom",
                    "weightPUtruejson",

                    "IDSF_1","IDSF_2","IDSF_3","IDSF_4",
                    "ISOSF_1","ISOSF_2","ISOSF_3","ISOSF_4",
                    "TauVsEleIDSF_1","TauVsEleIDSF_2","TauVsEleIDSF_3","TauVsEleIDSF_4",
                    "TauVsMuIDSF_1","TauVsMuIDSF_2","TauVsMuIDSF_3","TauVsMuIDSF_4",
                    "TauVsJetIDSF_1","TauVsJetIDSF_2","TauVsJetIDSF_3","TauVsJetIDSF_4",
                    "TrigSF_1","TrigSF_2","TrigSF_3","TrigSF_4"
                }
            );

        auto df2 = df1
            .Filter([](const EventResult &r) { return r.keep; }, {"res"})
            .Define("tau_channel", [](const EventResult &r) { return r.tau_channel; }, {"res"})
            .Define("lep_channel", [](const EventResult &r) { return r.lep_channel; }, {"res"})
            .Define("evtwt",       [](const EventResult &r) { return r.evtwt; },       {"res"})
            .Define("met_v",       [](const EventResult &r) { return r.met; },         {"res"})
            .Define("LT_v",        [](const EventResult &r) { return r.LT; },          {"res"})
            .Define("mT_v",        [](const EventResult &r) { return r.mT; },          {"res"})
            .Define("mZ1_v",       [](const EventResult &r) { return r.mZ1; },         {"res"})
            .Define("mZ2_v",       [](const EventResult &r) { return r.mZ2; },         {"res"})
            .Define("mH1_v",       [](const EventResult &r) { return r.mH1; },         {"res"})
            .Define("mH2_v",       [](const EventResult &r) { return r.mH2; },         {"res"})
            .Define("pt1_v",       [](const EventResult &r) { return r.pt1; },         {"res"})
            .Define("pt2_v",       [](const EventResult &r) { return r.pt2; },         {"res"})
            .Define("pt3_v",       [](const EventResult &r) { return r.pt3; },         {"res"})
            .Define("pt4_v",       [](const EventResult &r) { return r.pt4; },         {"res"})
            .Define("eta1_v",      [](const EventResult &r) { return r.eta1; },        {"res"})
            .Define("eta2_v",      [](const EventResult &r) { return r.eta2; },        {"res"})
            .Define("eta3_v",      [](const EventResult &r) { return r.eta3; },        {"res"})
            .Define("eta4_v",      [](const EventResult &r) { return r.eta4; },        {"res"})
            .Define("phi1_v",      [](const EventResult &r) { return r.phi1; },        {"res"})
            .Define("phi2_v",      [](const EventResult &r) { return r.phi2; },        {"res"})
            .Define("phi3_v",      [](const EventResult &r) { return r.phi3; },        {"res"})
            .Define("phi4_v",      [](const EventResult &r) { return r.phi4; },        {"res"})
            .Define("dRll_v",      [](const EventResult &r) { return r.dRll; },        {"res"});

        ofile.cd();

        // Tau-region histograms
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "mZ1_v",  "h_mZ1",  "mZ1",   5000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "mZ2_v",  "h_mZ2",  "mZ2",   5000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "mH1_v",  "h_mH1",  "mll1",  1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "mH2_v",  "h_mH2",  "mll2",  1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "met_v",  "h_met",  "MET",   100,  0, 500);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "LT_v",   "h_LT",   "LT",    1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "pt1_v",  "h_pt1",  "pT1",   1000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "pt2_v",  "h_pt2",  "pT2",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "pt3_v",  "h_pt3",  "pT3",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "pt4_v",  "h_pt4",  "pT4",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "eta1_v", "h_eta1", "Eta1",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "eta2_v", "h_eta2", "Eta2",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "eta3_v", "h_eta3", "Eta3",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "eta4_v", "h_eta4", "Eta4",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "phi1_v", "h_phi1", "Phi1",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "phi2_v", "h_phi2", "Phi2",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "phi3_v", "h_phi3", "Phi3",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "phi4_v", "h_phi4", "Phi4",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "dRll_v", "h_dRll", "dRll",  1000, 0, 4);
        BookAndWriteByChannel(df2, &ofile, "tau_channel", "mT_v",   "h_mT",   "mT",    1000, 0, 500);

        // Lepton-region histograms
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "mZ1_v",  "h_mZ1",  "mZ1",   5000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "mZ2_v",  "h_mZ2",  "mZ2",   5000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "mH1_v",  "h_mH1",  "mll1",  1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "mH2_v",  "h_mH2",  "mll2",  1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "met_v",  "h_met",  "MET",   100,  0, 500);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "LT_v",   "h_LT",   "LT",    1000, 0, 1000);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "pt1_v",  "h_pt1",  "pT1",   1000, 0, 500);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "pt2_v",  "h_pt2",  "pT2",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "pt3_v",  "h_pt3",  "pT3",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "pt4_v",  "h_pt4",  "pT4",   1000, 0, 250);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "eta1_v", "h_eta1", "Eta1",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "eta2_v", "h_eta2", "Eta2",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "eta3_v", "h_eta3", "Eta3",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "eta4_v", "h_eta4", "Eta4",  1000, -3, 3);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "phi1_v", "h_phi1", "Phi1",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "phi2_v", "h_phi2", "Phi2",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "phi3_v", "h_phi3", "Phi3",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "phi4_v", "h_phi4", "Phi4",  1000, -4, 4);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "dRll_v", "h_dRll", "dRll",  1000, 0, 4);
        BookAndWriteByChannel(df2, &ofile, "lep_channel", "mT_v",   "h_mT",   "mT",    1000, 0, 500);

        ofile.Close();
    }
}