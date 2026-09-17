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
    latex.SetTextFont(52);
    latex.SetTextSize(0.04);
    latex.DrawLatex(0.45, 0.85, description);
}

std::string makeHistString(const std::string& channel)
{
    std::string hist_string = "";

    // ----- Tau category channels -----
    if (channel.find("tau") != std::string::npos) {

        if (channel.find("3lep") != std::string::npos)
            hist_string += "#it{3l,}";
        else
            hist_string += "#it{4l,}";

        if (channel.find("0tau") != std::string::npos)
            hist_string += "#it{0#tau}";
        else if (channel.find("1tau") != std::string::npos)
            hist_string += "#it{1#tau}";
        else if (channel.find("2tau") != std::string::npos)
            hist_string += "#it{2#tau}";
        else if (channel.find("3tau") != std::string::npos)
            hist_string += "#it{3#tau}";
    }

    // ----- Normal flavor channels -----
    else {

        int ne = 0, nm = 0, nt = 0;

        for(char c : channel){
            if(c=='e') ne++;
            else if(c=='m') nm++;
            else if(c=='t') nt++;
        }

        hist_string += "#it{";
        bool first = true;

        auto add = [&](std::string x){
            if(!first) hist_string += ",";
            hist_string += x;
            first = false;
        };

        while(ne >= 2){ add("ee"); ne -= 2; }
        while(nm >= 2){ add("#mu#mu"); nm -= 2; }
        while(nt >= 2){ add("#tau#tau"); nt -= 2; }

        if(ne) add("e");
        if(nm) add("#mu");
        if(nt) add("#tau");

        hist_string += "}";
    }

    return hist_string;
}