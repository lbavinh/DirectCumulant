void RebinHistCumu()
{
    TFile* f = new TFile(Form("%s/100k_test_genAnalyzeHist.root", getenv("OUTPUTDIR")), "read");
    f->ls();
    //KEY: TH1I    hmult;1    hmult
    //KEY: TH1D    hpt;1    hpt
    //KEY: TH1D    heta;1    heta
    //KEY: TH1D    hphi;1    hphi
    //KEY: TH1D    hV22std;1
    //KEY: TH1D    hV22stdx;1
    //KEY: TH1D    hV22std_den;1
    //KEY: TH1D    hV22std_num;1
    //KEY: TH1D    hV22gap;1
    //KEY: TH1D    hV22gapx;1
    //KEY: TH1D    hV22gap_den;1
    //KEY: TH1D    hV22gap_num;1
    //KEY: TH1D    hV24std;1
    //KEY: TH1D    hV24stdx;1
    //KEY: TH1D    hV24std_den;1
    //KEY: TH1D    hV24std_num;1
    //KEY: TH1D    hV24gap;1
    //KEY: TH1D    hV24gapx;1
    //KEY: TH1D    hV24gap_den;1
    //KEY: TH1D    hV24gap_num;1

    TH1D* hV24n = dynamic_cast<TH1D*>(f->Get("hV24std_num"));
    TH1D* hV24d = dynamic_cast<TH1D*>(f->Get("hV24std_den"));

    TH1D* hV24 = dynamic_cast<TH1D*>(hV24n->Clone());
    hV24->Divide(hV24, hV24d);
    hV24->Draw("hist");
    return;
}
