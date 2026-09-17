#!/usr/bin/env python

from ROOT import *
import numpy as np
import array
import re


# ============================================================
# Configuration
# ============================================================

INPUT_FILE = "limits_mDCH1.txt"

OUTPUT_PNG  = "limit_mDCH1.png"
OUTPUT_PDF  = "limit_mDCH1.pdf"
OUTPUT_ROOT = "limit_mDCH1.root"

LUMI = "138 fb^{-1} (13 TeV)"

SHOW_GRID = True
# ============================================================
# Read limits.txt
#
# Expected format:
#
# 500
# Observed Limit: r < 0.0578
# Expected  2.5%: r < 0.0230
# Expected 16.0%: r < 0.0351
# Expected 50.0%: r < 0.0576
# Expected 84.0%: r < 0.0971
# Expected 97.5%: r < 0.1539
#
# ============================================================

def read_limits(filename):

    masses = []
    observed = []

    exp_m2 = []
    exp_m1 = []
    exp_med = []
    exp_p1 = []
    exp_p2 = []

    with open(filename, "r") as f:
        lines = [line.strip() for line in f if line.strip()]

    i = 0

    while i < len(lines):

        # ----------------------------------------------------
        # Mass
        # ----------------------------------------------------

        try:
            mass = float(lines[i])
        except ValueError:
            print("ERROR: Expected mass, got:")
            print(lines[i])
            i += 1
            continue

        # Need six foHowing lines
        if i + 6 >= len(lines):
            print("WARNING: Incomplete limit block for mass", mass)
            break

        # ----------------------------------------------------
        # Extract numerical value from each line
        # ----------------------------------------------------

        def get_value(line):

            match = re.search(
                r"r\s*<\s*([-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?)",
                line
            )

            if match is None:
                raise ValueError(
                    "Could not extract limit from:\n" + line
                )

            return float(match.group(1))


        try:

            obs_value = get_value(lines[i + 1])
            m2_value  = get_value(lines[i + 2])
            m1_value  = get_value(lines[i + 3])
            med_value = get_value(lines[i + 4])
            p1_value  = get_value(lines[i + 5])
            p2_value  = get_value(lines[i + 6])

        except ValueError as error:

            print("ERROR while reading mass", mass)
            print(error)
            raise


        # ----------------------------------------------------
        # Store
        # ----------------------------------------------------

        masses.append(mass)

        observed.append(obs_value)

        exp_m2.append(m2_value)
        exp_m1.append(m1_value)
        exp_med.append(med_value)
        exp_p1.append(p1_value)
        exp_p2.append(p2_value)


        # Move to next mass block
        i += 7


    # --------------------------------------------------------
    # Convert to numpy arrays
    # --------------------------------------------------------

    masses   = np.array(masses)
    observed = np.array(observed)

    exp_m2  = np.array(exp_m2)
    exp_m1  = np.array(exp_m1)
    exp_med = np.array(exp_med)
    exp_p1  = np.array(exp_p1)
    exp_p2  = np.array(exp_p2)


    # --------------------------------------------------------
    # Sort by mass
    # --------------------------------------------------------

    order = np.argsort(masses)

    masses   = masses[order]
    observed = observed[order]

    exp_m2  = exp_m2[order]
    exp_m1  = exp_m1[order]
    exp_med = exp_med[order]
    exp_p1  = exp_p1[order]
    exp_p2  = exp_p2[order]


    return (
        masses,
        observed,
        exp_m2,
        exp_m1,
        exp_med,
        exp_p1,
        exp_p2
    )


# ============================================================
# Read input
# ============================================================

(
    mass,
    obs,
    exp_m2,
    exp_m1,
    exp,
    exp_p1,
    exp_p2
) = read_limits(INPUT_FILE)


print("")
print("Read limits:")
print("")

for i in range(len(mass)):

    print(
        "%4.0f  obs = %.4f  "
        "exp = %.4f  "
        "[-1,+1] = [%.4f, %.4f]  "
        "[-2,+2] = [%.4f, %.4f]"
        %
        (
            mass[i],
            obs[i],
            exp[i],
            exp_m1[i],
            exp_p1[i],
            exp_m2[i],
            exp_p2[i]
        )
    )


# ============================================================
# Convert numpy arrays to ROOT arrays
# ============================================================

mass_root = array.array(
    'd',
    mass
)


# ============================================================
# Expected median
# ============================================================

expg = TGraph(
    len(mass),
    mass_root,
    array.array('d', exp)
)

expg.SetLineColor(kBlack)
expg.SetLineWidth(3)
expg.SetLineStyle(2)


# ============================================================
# Observed
# ============================================================

obsg = TGraph(
    len(mass),
    mass_root,
    array.array('d', obs)
)

obsg.SetLineColor(kBlack)
obsg.SetLineWidth(3)

obsg.SetMarkerColor(kBlack)
obsg.SetMarkerStyle(20)
obsg.SetMarkerSize(0.9)


# ============================================================
# Build band x-axis
#
# Forward:
#   500 -> 600 -> ... -> 1500
#
# Backward:
#   1500 -> ... -> 600 -> 500
#
# This closes the polygon.
# ============================================================

mass_reverse = np.flip(mass)

mass_band = np.append(
    mass,
    mass_reverse
)


# ============================================================
# 68% expected band
# ============================================================

exp1sigma = np.append(
    exp_p1,
    np.flip(exp_m1)
)


exp1g = TGraph(
    len(mass_band),
    array.array('d', mass_band),
    array.array('d', exp1sigma)
)

exp1g.SetFillColor(kGreen + 1)
exp1g.SetLineColor(kGreen + 1)


# ============================================================
# 95% expected band
# ============================================================

exp2sigma = np.append(
    exp_p2,
    np.flip(exp_m2)
)


exp2g = TGraph(
    len(mass_band),
    array.array('d', mass_band),
    array.array('d', exp2sigma)
)

exp2g.SetFillColor(kYellow)
exp2g.SetLineColor(kYellow)


# ============================================================
# Canvas
# ============================================================

c1 = TCanvas(
    "c1",
    "Doubly Charged Higgs Limits",
    900,
    700
)

c1.SetLeftMargin(0.12)
c1.SetRightMargin(0.05)
c1.SetBottomMargin(0.12)
c1.SetTopMargin(0.08)

c1.SetLogy()


# ============================================================
# Axes
# ============================================================

exp2g.SetTitle("")

xaxis = exp2g.GetXaxis()

xaxis.SetTitle("m_{ll^{#pm#pm}} [GeV]")
xaxis.SetTitleSize(0.045)
xaxis.SetLabelSize(0.040)

xaxis.SetLimits(
    mass[0] - 50,
    mass[-1] + 50
)


yaxis = exp2g.GetYaxis()

yaxis.SetTitle(
    "Cross Section [fb]"
)

yaxis.SetTitleSize(0.045)
yaxis.SetTitleOffset(1.15)
yaxis.SetLabelSize(0.040)

# AutomaticaHy choose sensible range
ymin = min(
    np.min(exp_m2),
    np.min(exp_m1)
)

ymax = max(
    np.max(exp_p2),
    np.max(obs)
)

yaxis.SetRangeUser(
    ymin * 0.6,
    ymax * 2.0
)


# ============================================================
# Draw
# ============================================================

exp2g.Draw("AF")

exp1g.Draw("F SAME")

expg.Draw("L SAME")

obsg.Draw("LP SAME")


gPad.RedrawAxis()

# ============================================================
# Grid
# ============================================================

if SHOW_GRID:
    gPad.SetGridx(False)
    gPad.SetGridy(True)

# ============================================================
# Legend
# ============================================================

leg = TLegend(
    0.62,
    0.66,
    0.89,
    0.88
)

leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetTextFont(42)
leg.SetTextSize(0.035)

leg.AddEntry(
    obsg,
    "Observed",
    "lp"
)

leg.AddEntry(
    expg,
    "Median expected",
    "l"
)

leg.AddEntry(
    exp1g,
    "68% expected",
    "f"
)

leg.AddEntry(
    exp2g,
    "95% expected",
    "f"
)

leg.Draw()


# ============================================================
# CMS
# ============================================================

tex1 = TLatex(
    0.13,
    0.92,
    "CMS"
)

tex1.SetNDC()
tex1.SetTextFont(62)
tex1.SetTextSize(0.055)
tex1.Draw()


tex2 = TLatex(
    0.22,
    0.92,
    "Preliminary"
)

tex2.SetNDC()
tex2.SetTextFont(52)
tex2.SetTextSize(0.045)
tex2.Draw()


# ============================================================
# Luminosity
# ============================================================

tex3 = TLatex(
    0.72,
    0.92,
    LUMI
)

tex3.SetNDC()
tex3.SetTextFont(42)
tex3.SetTextSize(0.040)
tex3.Draw()


# ============================================================
# Analysis label
# ============================================================

tex4 = TLatex(
    0.17,
    0.82,
    "H^{++}H^{--} #rightarrow 4#eH + E_{T}^{miss}"
)

tex4.SetNDC()
tex4.SetTextFont(42)
tex4.SetTextSize(0.035)
#tex4.Draw()


# ============================================================
# Save
# ============================================================

c1.SaveAs(OUTPUT_PNG)
c1.SaveAs(OUTPUT_PDF)
c1.SaveAs(OUTPUT_ROOT)

print("")
print("Saved:")
print("  ", OUTPUT_PNG)
print("  ", OUTPUT_PDF)
print("  ", OUTPUT_ROOT)
