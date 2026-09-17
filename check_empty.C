void check_empty() {
    TFile *f = TFile::Open("combined_hist.root");

    TIter next(f->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)next())) {
        TObject *obj = key->ReadObj();
        TH1 *h = dynamic_cast<TH1*>(obj);

        if (h && h->GetEntries() == 0)
            std::cout << h->GetName() << std::endl;
    }

    f->Close();
}
