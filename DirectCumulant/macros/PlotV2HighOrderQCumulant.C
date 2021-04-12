#define PLOTV2HIGHORDERQCUMULANT
#include "PlotV2QCumulant.C"
std::vector<TGraphErrors*> PlotV2HighOrderQCumulant(TString inputFileName){
  TFile *fi = new TFile(inputFileName.Data(),"read");
  
  bool saveAsPNG = true;
  TString outDirName = "pics"; // save png pics to output directory
  // const int ncent = 9;
  // const int maxCorrelator = 8; // We will not go beyond 8-p correlations
  double binCent[]={2.5,7.5,15,25,35,45,55,65,75};
  double eBinCent[ncent];
  const int nMethod = 4; // v22,v24,v26,v28
  TString grTitle[]={"v_{2}{2}","v_{2}{4}","v_{2}{6}","v_{2}{8}"};
  TProfile *recursion[maxCorrelator][ncent];    // Correlations calculated from Q-vector components using recursive algorithm 
  for(int c=0;c<maxCorrelator;c++){
    for(int icent=0;icent<ncent;icent++){
      recursion[c][icent] = (TProfile*)fi->FindObjectAny(Form("recursion_%i_%i",c,icent));
    }
  }
  TProfile *pCovariance[6][ncent];
  for (int i=0;i<6;i++){
    for (int c=0;c<ncent;c++){
      pCovariance[i][c] = (TProfile*)fi->FindObjectAny(Form("pCovariance_%i_%i",i,c));
    }
  }
  double vV22[ncent], vV24[ncent], vV26[ncent], vV28[ncent];
  double veV22[ncent], veV24[ncent], veV26[ncent], veV28[ncent];
  std::vector<double> vecV22, vecEV22;
  for (int icent=0;icent<ncent;icent++){
    // 2QC
    term cor2 = term(recursion[0][icent]);
    double V22  = sqrt(cor2.mVal);
    double eV22 = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
    // 4QC
    term cor4 = term(recursion[2][icent]);
    double cov24 = Covariance(pCovariance[0][icent],recursion[0][icent],recursion[2][icent]);
    double V24 = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
    double eV24= sqrt( 1./pow(V24,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) ) ;
    // 6QC
    term cor6 = term(recursion[4][icent]);
    double cov26 = Covariance(pCovariance[1][icent],recursion[0][icent],recursion[4][icent]);
    double cov46 = Covariance(pCovariance[3][icent],recursion[2][icent],recursion[4][icent]);
    double V26 = pow(2,-1./3.)*pow(cor6.mVal-9*cor2.mVal*cor4.mVal+12*pow(cor2.mVal,3),1./6.);
    double eV26 = sqrt(1./(2*pow(2,4)*pow(V26,10))*(9./2.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor2.mMSE
                     + 9./2.*pow(cor2.mVal,2)*cor4.mMSE+1./18.*cor6.mMSE
                     - 9*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov24
                     +(4*pow(cor2.mVal,2)-cor4.mVal)*cov26
                     - cor2.mVal*cov46));
    // 8QC
    term cor8 = term(recursion[6][icent]);
    double cov28 = Covariance(pCovariance[2][icent],recursion[0][icent],recursion[6][icent]);
    double cov48 = Covariance(pCovariance[4][icent],recursion[2][icent],recursion[6][icent]);
    double cov68 = Covariance(pCovariance[5][icent],recursion[4][icent],recursion[6][icent]);
    double V28 = pow(33,-1./8.)*pow(-cor8.mVal+16*cor6.mVal*cor2.mVal+18*pow(cor4.mVal,2)-144*cor4.mVal*pow(cor2.mVal,2)+144*pow(cor2.mVal,4),1./8.);
    double eV28 = sqrt(4.*pow(33,-2)/pow(V28,14)
                *(pow(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal,2)*cor2.mMSE
                + 81./16.*pow(4*pow(cor2.mVal,2)-cor4.mVal,2)*cor4.mMSE
                + pow(cor2.mVal,2)*cor6.mMSE+1./256.*cor8.mMSE
                - 9./2.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*(4*pow(cor2.mVal,2)-cor4.mVal)
                * cov24
                + 2*cor2.mVal*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)
                * cov26
                - 1./8.*(36*pow(cor2.mVal,3)-18*cor4.mVal*cor2.mVal+cor6.mVal)*cov28
                - 9./2.*cor2.mVal*(4*pow(cor2.mVal,2)-cor4.mVal)*cov46
                + 9./32.*(4*pow(cor2.mVal,2)-cor4.mVal)*cov48
                - 1./8.*cor2.mVal*cov68));
  

  vV22[icent] = V22; vV24[icent] = V24; vV26[icent] = V26; vV28[icent] = V28;
  veV22[icent] = eV22; veV24[icent] = eV24; veV26[icent] = eV26; veV28[icent] = eV28;

  eBinCent[icent] = 0.;
  }
  // for (int icent=0;icent<ncent;icent++){
  //   cout << vV22[icent] <<" "<< vV24[icent] <<" "<< vV26[icent] <<" "<< vV28[icent] << endl;
  // }
  TGraphErrors *gr[nMethod];
  gr[0] = new TGraphErrors(ncent,binCent,vV22,eBinCent,veV22);
  gr[1] = new TGraphErrors(ncent,binCent,vV24,eBinCent,veV24);
  gr[2] = new TGraphErrors(ncent,binCent,vV26,eBinCent,veV26);
  gr[3] = new TGraphErrors(ncent,binCent,vV28,eBinCent,veV28);
  for (int m=0;m<nMethod;m++){
    gr[m]->SetMarkerStyle(20+m);
    gr[m]->SetMarkerSize(1.3);
  }
  for (int m=0;m<nMethod;m++){
    gr[m]->SetTitle(grTitle[m].Data());
    gr[m]->GetYaxis()->SetTitle("v_{2}");
    gr[m]->GetXaxis()->SetTitle("Centrality, %");
  }


  std::vector<TGraphErrors*> vecGr;
  vecGr.push_back(gr[0]);
  for (int imeth=1;imeth<nMethod;imeth++){
    vecGr.push_back(gr[imeth]);
  }
  TCanvas *can = (TCanvas*) DrawTGraph(vecGr,"",0.65, 1.11, 0, 60, -0.01, 0.1,
                                       0.18,0.5,0.45,0.889,
                                       "Au+Au #sqrt{s_{NN}} = 7.7 GeV", Form("h^{#pm}, 0.2<p_{T}<3.0 GeV/c"),
                                       true, Form("Ratio to %s",grTitle[0].Data()));
  can -> SetName("Reference flow");
  if (saveAsPNG) 
  {
    gSystem->Exec(Form("mkdir -p ./%s/",outDirName.Data()));
    can -> SaveAs(Form("./%s/IntegratedFlow_hadron_High_order_QCumulant.png",outDirName.Data()));
  }
  return vecGr;
}