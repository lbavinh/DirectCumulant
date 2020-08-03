{
    Float_t x[5] = {1,2,3,4,5};
    Float_t w[5] = {2,5,3,1,1};
    TProfile *pr = new TProfile("t","Test",1,0.,1.);
    pr -> Sumw2();
    for(Int_t i=0; i<5; i++){
        pr -> Fill(0.5,x[i],w[i]);
    }
    cout << "Mean of x: <x>= " << pr -> GetBinContent(1) << endl;
    pr -> SetErrorOption("");
    Float_t Neff = pr -> GetBinEffectiveEntries(1);
    Float_t stErr = pr -> GetBinError(1);
    cout << "Standard error on the mean <x> = " << stErr << endl;

    pr -> SetErrorOption("g");
    Float_t inverseSqrtSumw = pr -> GetBinError(1);
    cout << "1/sqrt(sum(w))=" << inverseSqrtSumw << endl;

    pr -> SetErrorOption("s");
    Float_t stDev = pr -> GetBinError(1);
    cout << "Standard deviation of random observable x = " << stDev << endl;
    
    cout << "Effective entries Neff = " << Neff << endl;
    cout << "Standard error on the mean <x> = " << stDev/TMath::Sqrt(Neff) << endl;
    // cout << "sumw = " << pr -> GetW() << endl;
    // cout << "sumw2 = " << pr -> GetW2() << endl;
    Double_t stats[6];
    pr -> GetStats(stats);
    cout << "sum(w) = " << stats[0] << endl;        // 2+5+3+1+1
    cout << "sum(w^2) = " << stats[1] << endl;      // 2*2+5*5+3*3+1*1+1*1
    cout << "sum(w*x) = " << stats[2] << endl;      // 2*0.5 + 5*0.5 + 3*0.5 + 1*0.5 +1*0.5
    cout << "sum(w*x^2) = " << stats[3] << endl;    // 2*0.5*0.5 + 5*0.5*0.5 + 3*0.5*0.5 + 1*0.5*0.5 +1*0.5*0.5
    cout << "sum(w*y) = " << stats[4] << endl;      // 2*1 + 5*2 + 3*3 +1*4 +1*5
    cout << "sum(w*y^2) = " << stats[5] << endl;    // 2*1*1 + 5*2*2 + 3*3*3 + 1*4*4 + 1*5*5

    cout << "Ymax = " << pr -> GetYmax() << endl;
    cout << "Ymin = " << pr -> GetYmin() << endl;
    // Float_t *bins = pr -> GetArray();
    // Double_t wtest = TArrayD::fArray[1];
    // cout << "w = " << wtest << endl;
     
}