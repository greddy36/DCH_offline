#!/usr/bin/env python

from ROOT import *
import numpy as np
import array as array

mass = [500, 600, 800, 900, 1000, 1100, 1200, 1300]
xsec = [1.487,0.6080, 0.1300, 0.0682,0.03477,0.01929,0.01086,0.006182]

#mass = [900, 1000, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2200, 2300, 2400]
#xsec = [2.720,1.950,0.982,0.716,0.540,0.408,0.305,0.230,0.174,0.136,0.102,0.0608,0.0473,0.0370]


'''
c1 = 0.25
xsec1 = [x*c1*c1 for x in xsec]
tg1 = TGraph(len(mass), array.array('d', mass), array.array('d',xsec1))
tg1.SetLineColor(4)
tg1.SetMarkerColor(4)
tg1.SetMarkerStyle(7)
tg1.SetLineWidth(3)
tg1.SetLineStyle(9)

c2= 0.2
xsec2 = [x*c2*c2 for x in xsec]
tg2 = TGraph(len(mass), array.array('d', mass), array.array('d',xsec2))
tg2.SetLineColor(6)
tg2.SetMarkerColor(6)
tg2.SetMarkerStyle(7)
tg2.SetLineWidth(3)
tg2.SetLineStyle(7)


c3= 0.15
xsec3 = [x*c3*c3 for x in xsec]
tg3 = TGraph(len(mass), array.array('d', mass), array.array('d',xsec3))
tg3.SetLineColor(2)
tg3.SetMarkerColor(2)
tg3.SetMarkerStyle(7)
tg3.SetLineWidth(3)
tg3.SetLineStyle(5)


prevL = [2.03, 1.20, 0.54, 0.26, 0.18, 0.16, 0.13, 0.11, 0.10, 0.10, 0.11] 
tgp = TGraph(len(prevL), array.array('d', mass), array.array('d',prevL))
tgp.SetLineWidth(3)
'''


#HC-TopTagVeto_Syst.txt, Asymptotic, uncorrelated pdf uncertainties, added shape pdf and scale uncetainties for SM backgrouns
limit_bands = np.array([#use make_limitBand.sh script to make the below table
		# mass, obs, exp -2sigma, exp -1sigma, exp nom, exp +1sigma, exp +2sigma
[500, 0.1549, 0.0643, 0.0977, 0.1553, 0.2450, 0.3604 ],
[600, 0.1247, 0.0498, 0.0774, 0.1250, 0.1997, 0.2970 ],
[800, 0.0710, 0.0286, 0.0438, 0.0710, 0.1158, 0.1777 ],
[900, 0.0508, 0.0202, 0.0310, 0.0508, 0.0844, 0.1314 ],
[1000, 0.0417, 0.0160, 0.0248, 0.0417, 0.0707, 0.1133 ],
[1100, 0.0336, 0.0121, 0.0195, 0.0336, 0.0587, 0.0963 ],
[1200, 0.0310, 0.0107, 0.0177, 0.0310, 0.0550, 0.0909 ],
[1300, 0.0169, 0.0057, 0.0094, 0.0168, 0.0304, 0.0511]])

mass2 = limit_bands[:,0]
mass2r = np.flip(mass2)
massL = np.append(mass2, mass2r)

# observed cross sections:
obs = limit_bands[:,1]
obsg = TGraph(len(mass), array.array('d', mass), np.array(obs))	
obsg.SetMarkerColor(1)
obsg.SetMarkerStyle(7)
obsg.SetLineWidth(2)

exp = limit_bands[:,4] #exp_xsec[]
expg = TGraph(len(mass), array.array('d', mass), np.array(exp))
expg.SetLineWidth(3)
expg.SetLineStyle(2)

exp1sigmaH = limit_bands[:,5]
exp1sigmaL = np.flip(limit_bands[:,3])
exp1sigma = np.append(exp1sigmaH,exp1sigmaL)

exp2sigmaH = limit_bands[:,6]
exp2sigmaL = np.flip(limit_bands[:,2])
exp2sigma = np.append(exp2sigmaH,exp2sigmaL)

exp1g = TGraph(len(massL),massL,exp1sigma)
exp1g.SetFillColor(3)
exp2g = TGraph(len(massL),massL,exp2sigma)
exp2g.SetFillColor(5)

xaxis = exp2g.GetXaxis()
xaxis.SetTitle("DCH Mass (GeV)")
xaxis.SetTitleSize(0.045)
xaxis.SetLimits(mass[0]-1,mass[-1]+1)

yaxis = exp2g.GetYaxis()
yaxis.SetTitle("Cross Section [fb]")
yaxis.SetTitleSize(0.045)
yaxis.SetRangeUser(0.01,15)
	
exp2g.SetTitle("")
exp2g.Draw("AF")
exp1g.Draw("F")
expg.Draw("LP")
obsg.Draw("LP")
#tg1.Draw("LP")
#tg2.Draw("LP")
#tg3.Draw("LP")
#tgp.Draw("L")

tex1 = TLatex(0.16,0.92,"CMS Work in Progress")
tex1.SetNDC()
tex1.SetTextFont(42)
tex1.SetTextSize(0.05)
tex1.SetLineWidth(2)
tex1.Draw()

tex2 = TLatex(0.67,0.92,"139 fb^{-1} (13 TeV)")
tex2.SetNDC()
tex2.SetTextFont(42)
tex2.SetLineWidth(2)
tex2.Draw()
	
gPad.RedrawAxis()

leg = TLegend(0.65,0.65,0.895,0.89)
leg.AddEntry(expg,"Median expected limit","pl")
leg.AddEntry(exp1g,"68% expected limit","f")
leg.AddEntry(exp2g,"95% expected limit","f")
leg.AddEntry(obsg,"Observed limit","pl")
#leg.AddEntry(tg1,"Ybq prod. (c^{bW} = 0.25)","pl")
#leg.AddEntry(tg2,"Ybq prod. (c^{bW} = 0.2)","pl")
#leg.AddEntry(tg3,"Ybq prod. (c^{bW} = 0.15)","pl")
#leg.AddEntry(tgp,"CMS limit, PLB(2017) B 772","pl")
leg.SetBorderSize(0)
leg.Draw()

pt = TPaveText(0.3073066,0.9189474,0.6926934,0.9673684,"blNDC")
pt.SetName("title")
pt.SetBorderSize(0)
pt.SetFillColor(10)
pt.SetFillStyle(0)
pt.SetTextFont(42)
AText = pt.AddText("CMS Preliminary, 138 fb^{-1} (13 TeV)")
pt.Draw()

gPad.SetLogy()

gPad.SaveAs("limit.png")
