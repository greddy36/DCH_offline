import ROOT
import os
import sys

# ============================================================
# SIGNAL MASS FROM COMMAND LINE
# ============================================================

if len(sys.argv) != 2:
    print("Usage: python make_datacard.py MASS")
    print("Example: python make_datacard.py 1500")
    sys.exit(1)

SIGNAL_MASS = sys.argv[1]
SIGNAL = "M" + SIGNAL_MASS

INPUT_FILE = "combined_hist_onlyTau.root"
OUTPUT_FILE = f"datacard_{SIGNAL}_onlyTau.txt"

# ============================================================
# DISCRIMINATING VARIABLE FOR EACH CHANNEL
# ============================================================
'''CHANNEL_VARIABLES = {
    "tau0N":     "LTmet",
    "tau0Y":     "LT",
    "tau1":		"LT",
    "tau2N":     "LT",
    "tau2Y":     "mH1",
    "tau3":		"LT",
    "lep3tau0": "LT",
    "lep3tau1": "LT",
    "lep3tau2": "LT"
}

CHANNELS = [
    "tau0N",
    "tau0Y",
    "tau1",
    "tau2N",
    "tau2Y",
    "tau3",
    "lep3tau0",
    "lep3tau1",
    "lep3tau2",
]
'''
CHANNEL_VARIABLES = {
    "tau0":     "LTmet",
    "tau1":     "LTmet",
    "tau2":     "LTmet",
    "tau3":     "LTmet",
    "lep3tau0": "LTmet",
    "lep3tau1": "LTmet",
    "lep3tau2": "LTmet",
}

CHANNELS = [
    "tau0",
    "tau1",
    "tau2",
    "tau3",
    "lep3tau0",
    "lep3tau1",
    "lep3tau2",
]

# Samples/processes in the ROOT file
SAMPLES = [
    SIGNAL,
    "DY",
    "VV",
    "VVV",
    "ttV",
    "WJ",
    "ZZ",
    "ST",
    "TTbar",
    "other",
]

# Signal samples
SIGNALS = [
    SIGNAL,
]

# Shape systematics
# The histogram names must contain:
#   ..._<SYSTEMATIC>Up_<SAMPLE>
#   ..._<SYSTEMATIC>Down_<SAMPLE>
SHAPE_SYSTEMATICS = [
		"eIdIso",
		"eReco",
		"eTrig",
		"l1Prefire",
		"muId",
		"muIso",
		"muTrig",
		"pu",
		"tauES", 
		"tauVsEle",
		"tauVsJet",
		"tauVsMu",
		"roccor",
		"zpt",
		"chargeFlip",
		"xsec"
		
]

# Normalization systematics
# Format:
#   "systematic_name": {
#       "sample": uncertainty
#   }
#
# Example: 10% uncertainty -> 1.10
LNN_SYSTEMATICS = {
    "lumi": {
        SIGNAL: 1.025,
        "DY":      1.025,
        "VV":      1.025,
        "VVV":      1.025,
        "ttV":      1.025,
        "WJ":      1.025,
        "ZZ":      1.025,
        "ST":      1.025,
        "TTbar":      1.025,
        "other":      1.025,
    },

    # "fake": {
    #     "DY": 1.20,
    #     "TT": 1.20,
    # },
}

FLAT_FAKES = {
	"3lep":{
        "DY":      1.3,
        "WJ":      1.424,
        "ST":      1.424,
        "TTbar":   1.3,
	},
	"4lep":{
        "DY":      1.424,
        "VV":      1.3,
        "TTbar":   1.424,
	},
	
}

# ============================================================
# OPEN ROOT FILE
# ============================================================

f = ROOT.TFile.Open(INPUT_FILE)

if not f or f.IsZombie():
    raise RuntimeError("Could not open " + INPUT_FILE)


# ============================================================
# PROCESS IDs
# ============================================================

# Combine convention:
# signal = 0, -1, -2, ...
# background = 1, 2, 3, ...

PROCESS_IDS = {}

signal_id = 0
background_id = 1

for sample in SAMPLES:

    if sample in SIGNALS:
        PROCESS_IDS[sample] = signal_id
        signal_id -= 1

    else:
        PROCESS_IDS[sample] = background_id
        background_id += 1


# ============================================================
# HISTOGRAM NAME
# ============================================================

def hist_name(channel, sample):

    variable = CHANNEL_VARIABLES[channel]

    return f"h_{variable}_{channel}_{sample}"


def shape_hist_name(channel, systematic, direction, sample):

    variable = CHANNEL_VARIABLES[channel]

    return (
        f"h_{variable}_{channel}_"
        f"{systematic}{direction}_{sample}"
    )
# ============================================================
# CHECK HISTOGRAM
# ============================================================

def get_hist(name):

    h = f.Get(name)

    if not h:
        raise RuntimeError(
            f"Histogram '{name}' not found in {INPUT_FILE}"
        )

    return h


# ============================================================
# WRITE DATACARD
# ============================================================

with open(OUTPUT_FILE, "w") as card:

    # --------------------------------------------------------
    # Header
    # --------------------------------------------------------

    card.write("imax *\n")
    card.write("jmax *\n")
    card.write("kmax *\n")
    card.write("------------\n")

    # --------------------------------------------------------
    # Shapes
    # --------------------------------------------------------

    for channel in CHANNELS:
    
        variable = CHANNEL_VARIABLES[channel]
    
        nominal = f"h_{variable}_{channel}_$PROCESS"

        systematic = f"h_{variable}_{channel}_$SYSTEMATIC_$PROCESS"
    
        card.write(
            f"shapes * {channel} {INPUT_FILE} "
            f"{nominal} {systematic}\n"
        )

    card.write("------------\n")

    # --------------------------------------------------------
    # Observation
    # --------------------------------------------------------

    card.write("bin\t" + "\t".join(CHANNELS) + "\n")

    # Put -1 here if you are using an Asimov dataset.
    # Otherwise replace this with your observed data yields.
    card.write(
        "observation\t" +
        "\t".join(["-1"] * len(CHANNELS)) +
        "\n"
    )

    card.write("------------\n")

    # --------------------------------------------------------
    # Process names
    # --------------------------------------------------------

    card.write("bin\t")

    for channel in CHANNELS:
        for sample in SAMPLES:
            card.write(f"{channel:<15}")

    card.write("\n")

    card.write("process\t")

    for channel in CHANNELS:
        for sample in SAMPLES:
            card.write(f"{sample:<15}")

    card.write("\n")

    # --------------------------------------------------------
    # Process IDs
    # --------------------------------------------------------

    card.write("process\t")

    for channel in CHANNELS:
        for sample in SAMPLES:
            card.write(f"{PROCESS_IDS[sample]:<15}")

    card.write("\n")

    # --------------------------------------------------------
    # Rates
    # --------------------------------------------------------

    card.write("rate\t")

    for channel in CHANNELS:

        for sample in SAMPLES:

            h = get_hist(hist_name(channel, sample))

            rate = h.Integral()

            card.write(f"{rate:<15.6g}")

    card.write("\n")
    card.write("------------\n")

    # ========================================================
    # lnN SYSTEMATICS
    # ========================================================

    for systematic, uncertainties in LNN_SYSTEMATICS.items():

        card.write(f"{systematic:<15} lnN     ")

        for channel in CHANNELS:

            for sample in SAMPLES:

                if sample in uncertainties:
                    card.write(
                        f"{uncertainties[sample]:<15}"
                    )
                else:
                    card.write(f"{'-':<15}")

        card.write("\n")
    #=================
    # Flat fake-rate normalization uncertainties
    card.write(f"{'fake':<15} lnN     ")
    for channel in CHANNELS:
        for sample in SAMPLES:
            category = "3lep" if channel.startswith("lep3tau") else "4lep"
            value = FLAT_FAKES[category].get(sample, "-")
            card.write(f"{str(value):<15}")
    card.write("\n")
    # ========================================================
    # SHAPE SYSTEMATICS
    # ========================================================

    for systematic in SHAPE_SYSTEMATICS:

        card.write(f"{systematic:<15} shape   ")

        for channel in CHANNELS:

            for sample in SAMPLES:

                up_name = shape_hist_name(
                    channel,
                    systematic,
                    "Up",
                    sample
                )

                down_name = shape_hist_name(
                    channel,
                    systematic,
                    "Down",
                    sample
                )

                up = f.Get(up_name)
                down = f.Get(down_name)
                nominal = get_hist(hist_name(channel, sample))

                if (nominal.Integral() > 0.0 and up and down and up.Integral() > 0.0 and down.Integral() > 0.0):
                    card.write(f"{'1':<15}")
                else:
                    card.write(f"{'-':<15}")
        card.write("\n")

    # ========================================================
    # MC STATISTICS
    # ========================================================

    card.write("\n")
    card.write("* autoMCStats 0\n")


f.Close()

print(f"Created {OUTPUT_FILE}")
