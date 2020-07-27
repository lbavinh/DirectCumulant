{
    TFile *f1 = new TFile("TGraph_Dim.root","read");
    TGraphErrors *gr[2][3];
    gr[0][0] = (TGraphErrors*)f1->Get("grMc");
    gr[0][1] = (TGraphErrors*)f1->Get("grV2");
    gr[0][2] = (TGraphErrors*)f1->Get("grV4");
    TFile *f2 = new TFile("TGraph.root","read");
    char name[500];
    for (int i=0; i<3; i++){
        sprintf(name,"gr_%i",i);
        gr[1][i] = (TGraphErrors*)f2->Get(name);
    }
    TCanvas *c = new TCanvas("c","c",200,10,1600,900);
    TH2F *h = new TH2F("h","Result comparison",10,0.,2.1,10,0.,0.13);
    h -> Draw();
    gStyle->SetOptStat(0);
    for(int i=0; i<2; i++){
        gr[i][0] -> SetMarkerStyle(25);
        gr[i][0] -> SetMarkerColor(kRed+1+2*i);
        
        gr[i][1] -> SetMarkerStyle(20);
        gr[i][1] -> SetMarkerColor(kGreen+1+2*i);
        
        gr[i][2] -> SetMarkerStyle(22);
        gr[i][2] -> SetMarkerColor(kAzure+2+2*i);
        
        for (int j=0;j<2;j++){
            gr[i][j] -> SetMarkerSize(1.5);
            gr[i][j] -> SetLineWidth(1);
            gr[i][j] -> SetLineColor(2);
        }
        gr[i][0] -> Draw("P");
        gr[i][1] -> Draw("P");
        gr[i][2] -> Draw("P");
    }
    TLegend *leg = new TLegend(0.1,.9,0.5,.6);
    leg -> AddEntry(gr[0][0],"v_{2}{MC-Dim}","p");
    leg -> AddEntry(gr[0][1],"v_{2}{2,QC-Dim}","p");
    leg -> AddEntry(gr[0][2],"v_{2}{4,QC-Dim}","p");
    leg -> AddEntry(gr[1][0],"v_{2}{MC-Vinh}","p");
    leg -> AddEntry(gr[1][1],"v_{2}{2,QC-Vinh}","p");
    leg -> AddEntry(gr[1][2],"v_{2}{4,QC-Vinh}","p");
    leg -> SetFillColor(0);
    leg -> SetTextSize(0.04);
    leg -> SetTextFont(62);
    leg -> SetBorderSize(0);
    leg -> Draw();
}