#!/usr/bin/env python3
import os
import re
import math
from array import array
import ROOT

# ==================== Configuration ====================
INPUT_FILES = [
    'limits_mll1.txt',
    'limits_LT.txt',
    'limits_LTmet.txt',
    'limits_mDCH1.txt',
    #'limits_mDCH2.txt',
    #'limits_mll1_4tau.txt',
    #'limits_mll1_noTau.txt',
    #'limits_mll1_onlyTau.txt',
    #'limits_mDCH1_onlyTau.txt',
]
LABELS = [
    'mll1',
    'LT',
    'LT+MET',
    'mDCH1',
    #'mDCH2',
    #'mll1 for 0-gentau and LT for others',
    #'(4l,0#tau) and (3l,0#tau) channels',
    #'(4l,0-3#tau) channels',
    #'H^{#pm#pm}->ee,#mu#mu,e#mu only',
    #'H^{#pm#pm}->#tau#tau only',
    #'#splitline{Br(H^{#pm#pm}->#tau#tau) = 1 using mDCH}{from #nu-reco algorithm}',
]
OUTPUT_PNG = 'expected_limits_comparison_var.png'
OUTPUT_PDF = 'expected_limits_comparison_var.pdf'
LUMI = '138 fb^{-1} (13 TeV)'
SHOW_GRID = True
SHOW_BANDS = False
BAND_ALPHA_1SIGMA = 0.15
BAND_ALPHA_2SIGMA = 0.05
# Note: input values are assumed already in the units indicated by the y-axis.
Y_AXIS_TITLE = 'Expected cross section limit [fb]'
X_AXIS_TITLE = 'm_{H^{#pm#pm}} [GeV]'

COLORS = [ROOT.kBlack, ROOT.kBlue+1,
          ROOT.kGreen+2, ROOT.kMagenta+1, ROOT.kOrange+7,
          ROOT.kCyan+1, ROOT.kViolet+1]
STYLES = [1, 1, 1, 1, 1, 1, 1, 1]

# ==================== Read limits ====================
LIMIT_PATTERN = re.compile(r'r\s*<\s*([-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?)')

def extract_limit(line):
    match = LIMIT_PATTERN.search(line)
    if not match:
        raise ValueError('Cannot extract limit from: ' + line)
    return float(match.group(1))

def read_limits(filename):
    with open(filename, encoding='utf-8') as f:
        lines = [line.strip() for line in f if line.strip()]
    records = []
    i = 0
    while i < len(lines):
        try:
            mass = float(lines[i])
        except ValueError:
            print('WARNING: Skipping non-mass line:', lines[i])
            i += 1
            continue
        if i + 6 >= len(lines):
            print('WARNING: Incomplete limit block at mass', mass, 'in', filename)
            break
        vals = [extract_limit(line) for line in lines[i+1:i+7]]
        obs, m2, m1, med, p1, p2 = vals
        if not (m2 <= m1 <= med <= p1 <= p2):
            print(f'WARNING: Non-monotonic expected quantiles at mass {mass:g} in {filename}')
        records.append((mass, obs, m2, m1, med, p1, p2))
        i += 7
    records.sort(key=lambda r: r[0])
    return records

if len(INPUT_FILES) != len(LABELS):
    raise RuntimeError('INPUT_FILES and LABELS must have the same length.')

all_limits = []
for filename, label in zip(INPUT_FILES, LABELS):
    if not os.path.exists(filename):
        print('WARNING: File does not exist:', filename)
        continue
    records = read_limits(filename)
    if not records:
        print('WARNING: No limit points in', filename)
        continue
    all_limits.append({'filename': filename, 'label': label, 'records': records})
    print('Read', filename, 'with', len(records), 'mass points')

if not all_limits:
    raise RuntimeError('No valid limit files were found.')
# ==================== Theory cross section [fb] ====================
theory_mass = array('d', [
    500, 600, 700, 800, 900, 1000,
    1100, 1200, 1300, 1400, 1500
])

theory_xsec = array('d', [
    1.93, 8.30e-1, 3.75e-1, 1.80e-1, 9.35e-2,
    4.94e-2, 2.74e-2, 1.50e-2, 8.49e-3,
    4.91e-3, 2.80e-3
])

theory_graph = ROOT.TGraph(
    len(theory_mass), theory_mass, theory_xsec
)
theory_graph.SetLineColor(ROOT.kRed)
theory_graph.SetLineWidth(3)
theory_graph.SetLineStyle(2)
# ==================== ROOT setup ====================
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
canvas = ROOT.TCanvas('c_expected_comparison', 'Expected Limits Comparison', 900, 700)
canvas.SetLeftMargin(0.12)
canvas.SetRightMargin(0.05)
canvas.SetBottomMargin(0.12)
canvas.SetTopMargin(0.09)
canvas.SetLogy()
canvas.SetTicky(1)

all_masses = [r[0] for item in all_limits for r in item['records']]
all_positive = [r[j] for item in all_limits for r in item['records']
                for j in (2, 3, 4, 5, 6) if r[j] > 0]
if not all_positive:
    raise RuntimeError('Logarithmic axis requires positive expected limits.')
xmin, xmax = min(all_masses), max(all_masses)
ymin, ymax = min(all_positive), max(all_positive)
padding = max(50., 0.04*(xmax-xmin))
frame = ROOT.TH1F('frame_expected_comparison', '', 100, xmin-padding, xmax+padding)

# Include both limits and theory when choosing axis ranges.
plot_masses = all_masses + list(theory_mass)
plot_positive = all_positive + list(theory_xsec)

xmin, xmax = min(plot_masses), max(plot_masses)
ymin, ymax = min(plot_positive), max(plot_positive)

padding = max(50., 0.04 * (xmax - xmin))

frame = ROOT.TH1F(
    'frame_expected_comparison', '',
    100, xmin - padding, xmax + padding
)
frame.SetDirectory(0)
frame.SetMaximum(ymax * 2.0)
frame.SetMinimum(ymin * 1.0)
frame.SetMaximum(.2)
frame.SetMinimum(.03)

frame.GetXaxis().SetTitle(X_AXIS_TITLE)
frame.GetXaxis().SetTitleSize(0.045)
frame.GetXaxis().SetLabelSize(0.040)
frame.GetYaxis().SetTitle(Y_AXIS_TITLE)
frame.GetYaxis().SetTitleSize(0.045)
frame.GetYaxis().SetTitleOffset(1.2)
frame.GetYaxis().SetLabelSize(0.040)
frame.Draw('AXIS')

# Create all graphs first. 
for idx, item in enumerate(all_limits):
    records = item['records']
    n = len(records)
    color = COLORS[idx % len(COLORS)]
    style = STYLES[idx % len(STYLES)]
    med_graph = ROOT.TGraph(n)
    band1 = ROOT.TGraphAsymmErrors(n)
    band2 = ROOT.TGraphAsymmErrors(n)
    for i, (mass, obs, m2, m1, med, p1, p2) in enumerate(records):
        med_graph.SetPoint(i, mass, med)
        band1.SetPoint(i, mass, med)
        band2.SetPoint(i, mass, med)
        band1.SetPointError(i, 0., 0., max(0., med-m1), max(0., p1-med))
        band2.SetPointError(i, 0., 0., max(0., med-m2), max(0., p2-med))
    med_graph.SetLineColor(color)
    med_graph.SetLineWidth(3)
    med_graph.SetLineStyle(style)
    med_graph.SetMarkerColor(color)
    med_graph.SetMarkerStyle(20)
    med_graph.SetMarkerSize(0.7)
    band1.SetFillColorAlpha(color, BAND_ALPHA_1SIGMA)
    band1.SetLineColor(color)
    band1.SetLineWidth(0)
    band2.SetFillColorAlpha(color, BAND_ALPHA_2SIGMA)
    band2.SetLineColor(color)
    band2.SetLineWidth(0)
    item['median_graph'] = med_graph
    item['band1_graph'] = band1
    item['band2_graph'] = band2

# Draw wider bands first, then narrower bands, then all median curves on top.
if SHOW_BANDS:
    for item in all_limits:
        item['band2_graph'].Draw('3 SAME')
        item['band1_graph'].Draw('3 SAME')
        
for item in all_limits:
    item['median_graph'].Draw('L SAME')

theory_graph.Draw('L SAME')

if SHOW_GRID:
    canvas.SetGridx(False)
    canvas.SetGridy(True)
    canvas.RedrawAxis()

# Keep legend outside crowded curve region as much as possible.
leg = ROOT.TLegend(0.60, 0.62, 0.89, 0.88)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetTextFont(42)
leg.SetTextSize(0.025)
for item in all_limits:
    leg.AddEntry(item['median_graph'], item['label'], 'l')
leg.AddEntry(theory_graph, 'Theory', 'l')
leg.Draw()

# Legend explanation for band opacity (colors match the curves).
legend_note = ROOT.TLatex()
legend_note.SetNDC()
legend_note.SetTextFont(42)
legend_note.SetTextSize(0.025)
#legend_note.DrawLatex(0.50, 0.575, 'Dark/light bands: 68% / 95% expected')

tex1 = ROOT.TLatex(0.13, 0.85, 'CMS')
tex1.SetNDC(); tex1.SetTextFont(62); tex1.SetTextSize(0.055); tex1.Draw()
tex2 = ROOT.TLatex(0.22, 0.85, 'Preliminary')
tex2.SetNDC(); tex2.SetTextFont(52); tex2.SetTextSize(0.045); tex2.Draw()
tex3 = ROOT.TLatex(0.72, 0.92, LUMI)
tex3.SetNDC(); tex3.SetTextFont(42); tex3.SetTextSize(0.040); tex3.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(OUTPUT_PNG)
canvas.SaveAs(OUTPUT_PDF)
for idx, item in enumerate(all_limits):
    stem = re.sub(r'[^A-Za-z0-9_]', '_', os.path.splitext(os.path.basename(item['filename']))[0])
print('Saved:', OUTPUT_PNG, OUTPUT_PDF)
