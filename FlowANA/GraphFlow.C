struct coord
{
    float xlow;
    float ylow;
    float xup;
    float yup;
};

void GraphFlow(const char *inFileName)
{
    // Setting up global variables for the plot
    gROOT->SetStyle("Pub");
    gROOT->ForceStyle();
    gStyle->SetPalette(kDarkRainBow);
    gStyle->SetErrorX(0);
    gStyle->SetTitleSize(0.05);

    const double binpt [11] = {0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.8,2.3,2.8,4.0};
    const TString hName [4] = {TString("h^{#pm}"),TString("#pi^{#pm}"),TString("K^{#pm}"),TString("p+#bar{p}")};
    const TString hCent [6] = {TString("0-10%"),TString("10-20%"),TString("20-30%"),TString("30-40%"),TString("40-50%"),TString("50-60%")};
    const std::pair<Double_t,Double_t> v2range[6][4] = {{{-0.023,0.06},{-0.023,0.06},{-0.023,0.06},{-0.023,0.06}},
                                                        {{-0.005,0.09},{-0.005,0.09},{-0.005,0.09},{-0.005,0.09}},
                                                        {{-0.023,0.09},{-0.023,0.09},{-0.023,0.09},{-0.023,0.09}},
                                                        {{-0.051,0.16},{-0.051,0.16},{-0.051,0.16},{-0.051,0.16}},
                                                        {{-0.023,0.16},{-0.023,0.16},{-0.023,0.16},{-0.023,0.16}},
                                                        {{-0.023,0.16},{-0.023,0.16},{-0.023,0.16},{-0.023,0.16}}};
    const int ndet = 5;
    const int ncent = 6;
    const int npt = 9;
    const int npid = 4;

    TFile *fi = new TFile(inFileName,"read");
    TH1F *hv2[ndet][ncent][npt][npid]; //idet-icent-ipt-ipid
    TH1F *hv22[ndet][npt][npid];
    TH1F *hpt[ncent][npt][npid];

    for (int idet=0;idet<ndet;idet++)
    {
        for (int icent=0;icent<ncent;icent++)
        {
            for (int ipt=0; ipt<npt; ipt++)
            {
                for (int ipid=0;ipid<npid;ipid++)
                {
                    if (idet == 0)
                    {
                        hpt[icent][ipt][ipid] = (TH1F*) fi->Get(Form("hpt_%i_%i_%i",icent,ipt,ipid));
                        if (!hpt[icent][ipt][ipid]) std::cout << "WARNING: hpt is null (" << icent << " " << ipt << " " << ipid << ")" << std::endl;
                    }
                    if (icent==0)
                    {
                        hv22[idet][ipt][ipid] = (TH1F*) fi->Get(Form("hv22_%i_%i_%i",idet,ipt,ipid));
                    }
                    hv2[idet][icent][ipt][ipid] = (TH1F*) fi->Get(Form("hv2_%i_%i_%i_%i",idet,icent,ipt,ipid));
                }
            }
        }
    }
    std::vector<Double_t> vPt, vV2tpc, vV2fhcal, vV2RP;
    std::vector<Double_t> ePt, eV2tpc, eV2fhcal, eV2RP;
    int det1 = 0, det2 = 3, det0 = 4;
    TGraphErrors *grv2tpc[ncent][npid], *grv2fhcal[ncent][npid], *grv2RP[ncent][npid]; //icent-ipid

    for (int icent=0;icent<ncent;icent++)
    {
        for (int ipid=0;ipid<npid;ipid++)
        {
            for (int ipt=0;ipt<npt;ipt++)
            {
                std::cout << "icent " << icent << " ipid " << ipid << " ipt " << ipt << std::endl;
                vPt.push_back(hpt[icent][ipt][ipid]->GetMean());
                ePt.push_back(0.);
                vV2tpc.push_back(hv2[det1][icent][ipt][ipid]->GetMean());
                eV2tpc.push_back(hv2[det1][icent][ipt][ipid]->GetMeanError());
                vV2fhcal.push_back(hv2[det2][icent][ipt][ipid]->GetMean());
                eV2fhcal.push_back(hv2[det2][icent][ipt][ipid]->GetMeanError());
                vV2RP.push_back(hv2[det0][icent][ipt][ipid]->GetMean());
                eV2RP.push_back(hv2[det0][icent][ipt][ipid]->GetMeanError());
            }
            grv2tpc[icent][ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2tpc[0],&ePt[0],&eV2tpc[0]);
            grv2tpc[icent][ipid]->SetName(Form("grv2tpc_%i_%i",icent,ipid));
            grv2fhcal[icent][ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2fhcal[0],&ePt[0],&eV2fhcal[0]);
            grv2fhcal[icent][ipid]->SetName(Form("grv2fhcal_%i_%i",icent,ipid));
            grv2RP[icent][ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2RP[0],&ePt[0],&eV2RP[0]);
            grv2RP[icent][ipid]->SetName(Form("grv2RP_%i_%i",icent,ipid));

            grv2tpc[icent][ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
            grv2tpc[icent][ipid]->GetYaxis()->SetTitle("v_{2}");
            grv2fhcal[icent][ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
            grv2fhcal[icent][ipid]->GetYaxis()->SetTitle("v_{2}");
            grv2RP[icent][ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
            grv2RP[icent][ipid]->GetYaxis()->SetTitle("v_{2}");

            grv2tpc[icent][ipid]  ->SetMarkerStyle(20);
            grv2fhcal[icent][ipid]->SetMarkerStyle(26);
            grv2RP[icent][ipid]->SetMarkerStyle(21);
            
            grv2tpc[icent][ipid]  ->GetYaxis()->SetRangeUser(v2range[icent][ipid].first,v2range[icent][ipid].second);
            grv2fhcal[icent][ipid]->GetYaxis()->SetRangeUser(v2range[icent][ipid].first,v2range[icent][ipid].second);
            grv2RP[icent][ipid]->GetYaxis()->SetRangeUser(v2range[icent][ipid].first,v2range[icent][ipid].second);

            grv2tpc[icent][ipid]  ->GetXaxis()->SetLimits(0.,3.49);
            grv2fhcal[icent][ipid]->GetXaxis()->SetLimits(0.,3.49);
            grv2RP[icent][ipid]->GetXaxis()->SetLimits(0.,3.49);

            grv2tpc[icent][ipid]  ->SetMarkerSize(1.6);
            grv2fhcal[icent][ipid]->SetMarkerSize(1.6);
            grv2RP[icent][ipid]->SetMarkerSize(1.6);

            vPt.clear(); ePt.clear();
            vV2tpc.clear(); eV2tpc.clear();
            vV2fhcal.clear(); eV2fhcal.clear();
            vV2RP.clear(); eV2RP.clear();
        }
    }

    TH1F *hptTmp;
    TGraphErrors *grv22tpc[npid], *grv22fhcal[npid], *grv22RP[npid];
    for (int ipid=0;ipid<npid;ipid++) {
        for (int ipt = 0; ipt < npt; ipt++) {
            hptTmp = (TH1F*) hpt[1][ipt][ipid]->Clone();
            hptTmp->Add(hpt[2][ipt][ipid]);
            hptTmp->Add(hpt[3][ipt][ipid]);
            vPt.push_back(hptTmp->GetMean());
            ePt.push_back(0.);
            vV2tpc.push_back(hv22[det1][ipt][ipid]->GetMean());
            eV2tpc.push_back(hv22[det1][ipt][ipid]->GetMeanError());
            vV2fhcal.push_back(hv22[det2][ipt][ipid]->GetMean());
            eV2fhcal.push_back(hv22[det2][ipt][ipid]->GetMeanError());
            vV2RP.push_back(hv22[det0][ipt][ipid]->GetMean());
            eV2RP.push_back(hv22[det0][ipt][ipid]->GetMeanError());
            delete hptTmp;
        }
        grv22tpc[ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2tpc[0],&ePt[0],&eV2tpc[0]);
        grv22tpc[ipid]->SetName(Form("grv22tpc_%i",ipid));
        grv22fhcal[ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2fhcal[0],&ePt[0],&eV2fhcal[0]);
        grv22fhcal[ipid]->SetName(Form("grv22fhcal_%i",ipid));
        grv22RP[ipid] = new TGraphErrors(vPt.size(),&vPt[0],&vV2RP[0],&ePt[0],&eV2RP[0]);
        grv22RP[ipid]->SetName(Form("grv22RP_%i",ipid));

        grv22tpc[ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
        grv22tpc[ipid]->GetYaxis()->SetTitle("v_{2}");
        grv22fhcal[ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
        grv22fhcal[ipid]->GetYaxis()->SetTitle("v_{2}");
        grv22RP[ipid]->GetXaxis()->SetTitle("p_{T}, [GeV/c]");
        grv22RP[ipid]->GetYaxis()->SetTitle("v_{2}");

        grv22tpc[ipid]  ->SetMarkerStyle(20);
        grv22fhcal[ipid]->SetMarkerStyle(26);
        grv22RP[ipid]->SetMarkerStyle(21);

        grv22tpc[ipid]  ->GetYaxis()->SetRangeUser(v2range[1][ipid].first,v2range[1][ipid].second);
        grv22fhcal[ipid]->GetYaxis()->SetRangeUser(v2range[1][ipid].first,v2range[1][ipid].second);
        grv22RP[ipid]->GetYaxis()->SetRangeUser(v2range[1][ipid].first,v2range[1][ipid].second);

        grv22tpc[ipid]  ->GetXaxis()->SetLimits(0.,3.49);
        grv22fhcal[ipid]->GetXaxis()->SetLimits(0.,3.49);
        grv22RP[ipid]->GetXaxis()->SetLimits(0.,3.49);

        grv22tpc[ipid]  ->SetMarkerSize(1.6);
        grv22fhcal[ipid]->SetMarkerSize(1.6);
        grv22RP[ipid]->SetMarkerSize(1.6);

        vPt.clear(); ePt.clear();
        vV2tpc.clear(); eV2tpc.clear();
        vV2fhcal.clear(); eV2fhcal.clear();
        vV2RP.clear(); eV2RP.clear();
    }

    
    TFile *fo = new TFile("./v2_graphs.root","recreate");
    fo->cd();
   
    for (int icent=0; icent<ncent; icent++)
    {
        for (int ipid=0;ipid<npid;ipid++)
        {
            grv2tpc[icent][ipid]->Write();
            grv2RP[icent][ipid]->Write();
            grv2fhcal[icent][ipid]->Write();
        }
    } 
    for (int ipid=0;ipid<npid;ipid++)
    {
        grv22tpc[ipid]->Write();
        grv22RP[ipid]->Write();
        grv22fhcal[ipid]->Write();
    }
    fo->Close();
}
