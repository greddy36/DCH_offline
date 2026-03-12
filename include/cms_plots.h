void DrawCMSLabel() {

    TLatex latex;
    latex.SetNDC(); // use normalized coordinates
    latex.SetTextFont(42);
    latex.SetTextSize(0.04);

    // Luminosity text (top right)
    latex.SetTextAlign(31);
    latex.DrawLatex(0.92, 0.95, "138 fb^{-1} (13 TeV)");

    // CMS text (top left)
    latex.SetTextFont(62); // bold
    latex.SetTextAlign(11);
    latex.DrawLatex(0.09, 0.95, "CMS");

    // Preliminary text
    latex.SetTextFont(52); // italic
    latex.SetTextSize(0.035);
    latex.DrawLatex(0.16, 0.95, "Preliminary");
}

void PlotDescription(const char* description) {

    TLatex latex;
    latex.SetNDC(); // use normalized coordinates
    latex.SetTextFont(62);
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.45, 0.85, description);
}
