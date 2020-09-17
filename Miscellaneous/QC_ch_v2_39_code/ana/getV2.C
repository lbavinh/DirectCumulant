void getV2(const Char_t* inFileName = "test.flow.root") {
    gROOT->ProcessLine(".L flowRebinMaker.cxx+");
    
    TFile* inFile = new TFile(inFileName);
    if (NULL == inFile) {
        cerr << "Error: Can not open input file: " << inFileName << endl;
        return;
    }

    enum POITypes {
        chargedParticle = 0, piPlus, piMinus,
        nPOIs = 3
    };

    const Int_t nCentBins             = 9;
    const Char_t* centBins[nCentBins] = {"70_80", "60_70", "50_60",
                                         "40_50", "30_40", "20_30",
                                         "10_20", "5_10",  "0_5"};

    const Int_t nPtBins     = 20;
    double ptBin[nPtBins+1] = {0.0, 0.2, 0.4, 0.6, 0.8,
                               1.0, 1.2, 1.4, 1.6, 1.8,
                               2.0, 2.2, 2.4, 2.6, 2.8,
                               3.2, 3.6, 4.0, 4.4, 4.8, 5.2};

    flowRebinMaker* fMaker[nCentBins];
    for (Int_t iCent = 0; iCent < nCentBins; ++iCent) {
        fMaker[iCent] = new flowRebinMaker();
        TString pfix("_cent"); pfix += iCent;
        fMaker[iCent]->readHists(inFile, pfix.Data());
        fMaker[iCent]->integrateEta(-1.0, 1.0);
        fMaker[iCent]->rebinPt(nPtBins, ptBin);
    }

    TH1D* myChV22[nCentBins] = {NULL};
    for (Int_t iCent = 0; iCent < nCentBins; ++iCent) {
        TString hName("ChV22_cent");
        hName += centBins[iCent];
        myChV22[iCent] = fMaker[iCent]->v22POIPtRebin->ProjectionY(hName.Data(), chargedParticle+1, chargedParticle+1,"e");
        myChV22[iCent]->SetTitle("");
        myChV22[iCent]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        myChV22[iCent]->GetYaxis()->SetTitle("v_2");
        myChV22[iCent]->SetMarkerStyle(20);
        myChV22[iCent]->SetMarkerColor(kRed);
        myChV22[iCent]->SetLineColor(kRed);
    }

    TH1D* myChV24[nCentBins] = {NULL};
    for (Int_t iCent = 0; iCent < nCentBins; ++iCent) {
        TString hName("ChV24_cent");
        hName += centBins[iCent];
        myChV24[iCent] = fMaker[iCent]->v24POIPtRebin->ProjectionY(hName.Data(), chargedParticle+1, chargedParticle+1, "e");
        myChV24[iCent]->SetTitle("");
        myChV24[iCent]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
        myChV24[iCent]->GetYaxis()->SetTitle("v_{2}");
        myChV24[iCent]->SetMarkerStyle(21);
        myChV24[iCent]->SetMarkerColor(kRed);
        myChV24[iCent]->SetLineColor(kRed);
    }
}
