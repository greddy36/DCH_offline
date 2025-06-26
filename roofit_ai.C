For each histogram ’sef.hist’ I create these variables

       # RooFit quantities:
        self.SF = RooRealVar(name+"SF", name+"SF", 1., 0., 100.)
        self.norm = RooRealVar(name+"Norm", name+"Norm", self.hist.Integral())
        self.N = RooFormulaVar(name+"N", name+"SF*" +
                               name+"Norm", RooArgList(self.norm, self.SF))
        self.set = RooDataHist(name+"Set", name+"Set",
                               RooArgList(var), self.hist)
        self.pdf = RooHistPdf(name+"Pdf", name+"Pdf", RooArgSet(var), self.set)



# =====================================================
# ================  HF FIT =======================
# =====================================================

if options.hffit:
    sum_pdf = RooAddPdf("SumPdf", "SumPdf", RooArgList(
        wlf.pdf, whf.pdf, osm.pdf), RooArgList(wlf.N, whf.N, osm.N))
    osm_constr = RooGaussian("osm_constr", "osm_constr",
                             osm.SF, RooFit.RooConst(1.), RooFit.RooConst(0.05))

    tot_pdf = RooProdPdf("TotPdf", "TotPdf", RooArgList(
        sum_pdf, osm_constr))

    r = tot_pdf.fitTo(data.set, RooFit.Constrain(
        RooArgSet(osm.SF)), RooFit.Extended(kTRUE), RooFit.Save())
    params = tot_pdf.getVariables()
    params.Print("v")

    for idist in templates[1:]:
        idist.hist.Scale(params.find(idist.name+"SF").getVal())