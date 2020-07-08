void v2QCplot(){
    TFile *file = new TFile("v2QC.root");

    float v2[3];
    float v2e[3];
    float hmethod[3];
    float hmethode[3];
    char hname[800];
    char title1[800];
    sprintf(title1," ");


    TProfile *pr = (TProfile*) file->Get("flow");
    for(int i=0; i<3; i++){
        v2[i] = pr -> GetBinContent(i+1);
        cout << "v2 = " << v2[i] << endl;
        hmethod[i]=i+1;
        hmethode[i]=0.;
    }
    
    for(int i=0; i<3; i++){
        (void) sprintf(hname,"v2_%i",i);
        TH1D *hv2 = (TH1D*) file->Get(hname);
        v2e[i] = hv2->GetRMS()/sqrt(hv2->GetEntries());
        //v2e[i] = hv2->GetRMS();
        cout << "Err v2 = " << v2e[i] << endl;
    }


    auto c1 = new TCanvas("c1","Flow analysis results",200,10,800,600);
    
    c1->GetFrame()->SetBorderSize(12);

    c1->cd(); 
        
    gStyle->SetOptStat(0);

    c1->GetFrame()->SetFillColor(19);



    gStyle->SetPalette(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetHistFillColor(10);
    gStyle->SetHistFillStyle(0);
    gStyle->SetOptTitle(1);

    c1->SetBorderMode(0);

    c1->SetFillColor(0);
    float xmin1=0.5;
    float xmax1=3.5;
    float ymin1=0.0735;
    float ymax1=0.0745;

    TH2F *hr2 = new TH2F("hr2",title1, 2,xmin1,xmax1,2,ymin1,ymax1);

    //hr2->SetXTitle("p_{T}, GeV/c");
    hr2->SetYTitle("v_{n}");

    hr2->Draw();

    TGraph *grshade = new TGraph(8);
    for (Int_t i=0; i<4; i++) {
        grshade->SetPoint(i,i+0.5,v2[0]+v2e[0]);
        grshade->SetPoint(4+i,3.5-i,v2[0]-v2e[0]);
    }
    grshade -> SetFillStyle(1001);
    grshade -> SetFillColor(18);
    grshade -> Draw("f");

    // const int npt=7;
    auto gr1 = new TGraphErrors(3,hmethod,v2,hmethode,v2e);
    gr1->SetTitle("TGraphErrors Example ");
    gr1->SetMarkerColor(kRed);
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(1.3);
    gr1->Draw("P");
}