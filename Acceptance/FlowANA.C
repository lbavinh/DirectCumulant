#define FlowANA_cxx
#include "FlowANA.h"
#include "function.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TMath.h"
#include "TH1.h"
#include "TString.h"

#include <iostream>
#include <fstream>
using namespace std;

const  float A = TMath::Pi()/3.;
const  float B = TMath::Pi()/2.;
const  float C = TMath::Pi();
const  float D = 5.*TMath::Pi()/4.;

void FlowANA::Booking(TString outFile)
{
  d_outfile = new TFile(outFile.Data(), "recreate");
  cout << "Output file \"" << outFile.Data() << "\" has been initialized" << endl;

  hPsiRawMB = new TH1F("hPsiRawMB","", 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
  hPsiRecMB = new TH1F("hPsiRecMB","", 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
  hPsiFlatMB = new TH1F("hPsiFlatMB","", 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );

  // Acceptance correction
  hcos2phi1 = new TProfile("hcos2phi1","hcos2phi1",ncent,0.,ncent);
  hsin2phi1 = new TProfile("hsin2phi1","hsin2phi1",ncent,0.,ncent);
  hcos2phi12 = new TProfile("hcos2phi12","hcos2phi12",ncent,0.,ncent);
  hsin2phi12 = new TProfile("hsin2phi12","hsin2phi12",ncent,0.,ncent);
  hcos2phi123 = new TProfile("hcos2phi123","hcos2phi123",ncent,0.,ncent);
  hsin2phi123 = new TProfile("hsin2phi123","hsin2phi123",ncent,0.,ncent);
  pRes = new TProfile("pRes","pRes", ncent,0.,ncent);
  pResRAW = new TProfile("pResRAW","pResRAW", ncent,0.,ncent);

  pV2etasub = new TProfile2D("pV2etasub","", ncent, 0. ,ncent, npt, &bin_pT[0]);
  pV2etasubRAW = new TProfile2D("pV2etasubRAW","", ncent, 0. ,ncent, npt, &bin_pT[0]);
  pV2MC = new TProfile2D("pV2MC","", ncent, 0. ,ncent, npt, &bin_pT[0]);

  for( int ieta=0; ieta<neta; ieta++ ){
    pQx[ieta] = new TProfile(Form("pQx_%i", ieta), Form("Qx_%i before recentering. Centrality", ieta), ncent, 0., ncent);
    pQy[ieta] = new TProfile(Form("pQy_%i", ieta), Form("Qy_%i before recentering. Centrality", ieta), ncent, 0., ncent);
    for (int iharm=0; iharm<nharm; iharm++){
      pSinNPsi[ieta][iharm] = new TProfile(Form("pSinNPsi_%i_%i_rec", ieta,iharm), Form("<sin(2n#Psi_{2#eta%i})> recentered, harm_%i", ieta,iharm), ncent, 0., ncent);
      pCosNPsi[ieta][iharm] = new TProfile(Form("pCosNPsi_%i_%i_rec", ieta,iharm), Form("<cos(2n#Psi_{2#eta%i})> recentered, harm_%i", ieta,iharm), ncent, 0., ncent);
    }
    for (int icent=0;icent<ncent;icent++){
      hQMultRaw[icent][ieta] = new TH1F(Form("hQMultRaw_%i_%i",icent,ieta),Form("hQMultRaw_%i_%i",icent,ieta), 100, 0, 1000);
      hQvecRaw[icent][ieta] = new TH1F(Form("hQvecRaw_%i_%i",icent,ieta),Form("hQvecRaw_%i_%i",icent,ieta), 100, -1.2, 1.2 );
      hQvecRec[icent][ieta] = new TH1F(Form("hQvecRec_%i_%i",icent,ieta),Form("hQvecRec_%i_%i",icent,ieta), 100, -1.2, 1.2 );
      hPsiRaw[icent][ieta] = new TH1F(Form("hPsiRaw_%i_%i",icent,ieta),Form("hPsiRaw_%i_%i",icent,ieta), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
      hPsiRecentered[icent][ieta] = new TH1F(Form("hPsiRecentered_%i_%i",icent,ieta), Form("Recentered #Psi_{2%i}, cent%i-%i",ieta,icent*10,(icent+1)*10), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
      hPsiFlattened[icent][ieta] = new TH1F(Form("hPsiFlattened_%i_%i",icent,ieta), Form("Flattened #Psi_{2%i}, cent%i-%i",ieta,icent*10,(icent+1)*10), 100, -TMath::Pi()/2.-0.1, TMath::Pi()/2.+0.1 );
    }
  }

  for (int ipt=0;ipt<npt;ipt++){
    hPT[ipt] = new TProfile(Form("hPT_%i", ipt), Form("p_{T} distr, %2.1f<pt<%2.1f GeV/c", bin_pT[ipt], bin_pT[ipt + 1]), 1, 0., 1.);
    hcos2psi1[ipt] = new TProfile(Form("hcos2psi1_%i", ipt),Form("hcos2psi1_%i", ipt),ncent,0.,ncent);
    hsin2psi1[ipt] = new TProfile(Form("hsin2psi1_%i", ipt),Form("hsin2psi1_%i", ipt),ncent,0.,ncent);
    hcos2psi1phi2[ipt] = new TProfile(Form("hcos2psi1phi2_%i", ipt),Form("hcos2psi1phi2_%i", ipt),ncent,0.,ncent);
    hsin2psi1phi2[ipt] = new TProfile(Form("hsin2psi1phi2_%i", ipt),Form("hsin2psi1phi2_%i", ipt),ncent,0.,ncent);
    hcos2psi1pphi23[ipt] = new TProfile(Form("hcos2psi1pphi23_%i", ipt),Form("hcos2psi1pphi23_%i", ipt),ncent,0.,ncent);
    hsin2psi1pphi23[ipt] = new TProfile(Form("hsin2psi1pphi23_%i", ipt),Form("hsin2psi1pphi23_%i", ipt),ncent,0.,ncent);
    hcos2psi1mphi23[ipt] = new TProfile(Form("hcos2psi1mphi23_%i", ipt),Form("hcos2psi1mphi23_%i", ipt),ncent,0.,ncent);
    hsin2psi1mphi23[ipt] = new TProfile(Form("hsin2psi1mphi23_%i", ipt),Form("hsin2psi1mphi23_%i", ipt),ncent,0.,ncent);
  }

  for (int icent=0;icent<ncent;icent++){
    hv22[icent] = new TProfile(Form("hv22_%i", icent), Form("hv22_%i", icent), 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), Form("hv24_%i", icent), 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), Form("hcov24_%i", icent), 1, 0., 1.);

    for (int ipt=0;ipt<npt;ipt++){
      hv22pt[icent][ipt] = new TProfile(Form("hv22pt_%i_%i", icent, ipt), Form("hv22pt_%i_%i", icent, ipt), 1, 0., 1.);
      hv24pt[icent][ipt] = new TProfile(Form("hv24pt_%i_%i", icent, ipt), Form("hv24pt_%i_%i", icent, ipt), 1, 0., 1.);
      hcov22prime[icent][ipt] = new TProfile(Form("hcov22prime_%i_%i", icent, ipt), Form("hcov22prime_%i_%i", icent, ipt), 1, 0., 1.);
      hcov24prime[icent][ipt] = new TProfile(Form("hcov24prime_%i_%i", icent, ipt), Form("hcov24prime_%i_%i", icent, ipt), 1, 0., 1.);
      hcov42prime[icent][ipt] = new TProfile(Form("hcov42prime_%i_%i", icent, ipt), Form("hcov42prime_%i_%i", icent, ipt), 1, 0., 1.);
      hcov44prime[icent][ipt] = new TProfile(Form("hcov44prime_%i_%i", icent, ipt), Form("hcov44prime_%i_%i", icent, ipt), 1, 0., 1.);
      hcov2prime4prime[icent][ipt] = new TProfile(Form("hcov2prime4prime_%i_%i", icent, ipt), Form("hcov2prime4prime_%i_%i", icent, ipt), 1, 0., 1.);
    }
  }
  cout << "Histograms have been initialized" << endl;
}

void FlowANA::Loop_a_file(TString file)
{
  if (fRunNum>0) { FinishRecentering(); }
  if (fRunNum>1) { FinishFlattening(); }
  if (fRunNum>2) { FinishResolution(); }
  TFile *treefile = TFile::Open(file.Data());
  TTree *tree = (TTree *)treefile->Get("tree");
  if (tree == 0)
  {
    cout << "htree is not found in " << file << endl;
    treefile->Close();
    return;
  }
  cout << file << " is opened" << endl;
  Init(tree);
  if (!fChain) return;
  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  { // loop over all entries (nentries) of chain

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (ientry % 100000 == 0) cout << ientry << endl;
    centrality = -1;
    for (int i = 0; i < ncent; i++) if (CentB(b) == bin_cent[i]) centrality = i;
    if (centrality < 0) continue;
    for (Int_t ieta = 0; ieta<neta; ieta++)
    {
      multQv[ieta] = 0;
      for (Int_t i=0; i<2; i++)
      {
        sumQxy[ieta][i] = 0;
      }
    }
    for (int i = 0; i < nh; i++)
    { // track loop
      if( pt0[i]<minpt  || pt0[i]>maxpt || TMath::Abs(eta0[i])>eta_cut) continue;
      if ( (phi0[i]>A && phi0[i]<B) || (phi0[i]>C && phi0[i]<D) ) continue; // acceptance filter
      int fEta = -1;
      if (eta0[i] <-0.05 && eta0[i] >-eta_cut) fEta = 0;
      if (eta0[i] > 0.05 && eta0[i] < eta_cut) fEta = 1;

      if ( fEta>-1 ){
        sumQxy[fEta][0] += pt0[i] * cos( 2.0 * phi0[i] );
        sumQxy[fEta][1] += pt0[i] * sin( 2.0 * phi0[i] );
        multQv[fEta]++;
      } // end of eta selection

    } // end of track loop
    if (fRunNum == 0) { Recentering(); } // cout << "Calculating Q-vector mean..." << endl;
    else if (fRunNum == 1) { Flattening(); } // cout << "Calculating cos/sin terms for Flattening Procedure..." << endl;
    else if (fRunNum >= 2)
    {
      for (int ieta=0; ieta<neta; ieta++){
        if( multQv[ieta]>mult_cut ){ // multiplicity > 5
          
          // Raw
          hQMultRaw[centrality][ieta]->Fill( multQv[ieta] );
          fPsiRaw[ieta] = TMath::ATan2(sumQxy[ieta][1], sumQxy[ieta][0]) / 2.0;
          hPsiRaw[centrality][ieta]->Fill( fPsiRaw[ieta] );
          hPsiRawMB->Fill( fPsiRaw[ieta] );
          fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0],2.0)+TMath::Power( sumQxy[ieta][1],2.0))/multQv[ieta];
          hQvecRaw[centrality][ieta]->Fill( fQv[ieta] );

          // Recentering
          fQv[ieta] = TMath::Sqrt(TMath::Power( sumQxy[ieta][0] - qxMean[centrality][ieta],2.0)+TMath::Power( sumQxy[ieta][1] - qyMean[centrality][ieta],2.0))/multQv[ieta];
          hQvecRec[centrality][ieta]->Fill( fQv[ieta] );
          fPsiRec[ieta] = TMath::ATan2(sumQxy[ieta][1]-qyMean[centrality][ieta], sumQxy[ieta][0]- qxMean[centrality][ieta]) / 2.0;
          hPsiRecentered[centrality][ieta] -> Fill(fPsiRec[ieta]);
          hPsiRecMB->Fill(fPsiRec[ieta]);
          // Flattening
          // L. Adamczyk et al. (STAR Collaboration). Phys. Rev. C 86, 054908 (2012)
          // formula (15)
          dPsi=0;
          for (int iharm=0;iharm<nharm;iharm++){
            dPsi += 2./(iharm+1) * (-sinNPhiMean[ieta][iharm][centrality]*cos(2*(iharm+1)*fPsiRec[ieta]) + cosNPhiMean[ieta][iharm][centrality]*sin(2*(iharm+1)*fPsiRec[ieta]));
          }
          fPsiFlat[ieta] = fPsiRec[ieta] + dPsi;
          hPsiFlattened[centrality][ieta] -> Fill(fPsiFlat[ieta]);
          hPsiFlatMB->Fill(fPsiFlat[ieta]);
        }else{
          fPsiFlat[ieta] = -9999;
        }
      }

      // Resolution

      if (fPsiFlat[0]<-9000 || fPsiFlat[1]<-9000) return;
      if (fRunNum == 2) 
      {
        pRes -> Fill(centrality+0.5, TMath::Cos(2. *(fPsiFlat[0] - fPsiFlat[1])) );
        pResRAW -> Fill(centrality+0.5, TMath::Cos(2. *(fPsiRaw[0] - fPsiRaw[1])) );
      }
      else
      {
        Double_t Qx2 = 0., Qy2 = 0., Qx4 = 0., Qy4 = 0.;
        TComplex Q2 = 0., Q4 = 0.;
        Double_t px2[npt] = {0.}, py2[npt] = {0.};
        TComplex p2[npt] = {0.}, p4[npt] = {0.}, q2[npt] = {0.}, q4[npt] = {0.};
        Double_t qx2[npt] = {0.}, qy2[npt] = {0.}, qx4[npt] = {0.}, qy4[npt] = {0.};
        Double_t M = 0.;
        Double_t mq[npt] = {0.}, mp[npt] = {0.};
        Double_t redCor22[npt] = {0.}, redCor24[npt] = {0.};
        Double_t w2 = 0., w4 = 0.;
        Double_t wred2[npt] = {0.}, wred4[npt] = {0.};
        Double_t cor22 = 0., cor24 = 0.;



        for(int itrk=0;itrk<nh;itrk++) {  //track loop
          Double_t pt = pt0[itrk];
          if( pt<minpt || pt>maxpt || TMath::Abs(eta0[itrk])>eta_cut) continue;
          Int_t ipt = 0;
          for (int j = 0; j < npt; j++)
          {
            if (pt >= bin_pT[j] && pt < bin_pT[j + 1])
              ipt = j;
          }

          // ======================= MC ======================= //
          if (bFlow[itrk]){ // Bool_t bFlow : flow particle flag
            Double_t v2 = TMath::Cos(2 * (phi0[itrk] - rp));
            // calculate reference v2 from MC toy
            // Calculate differential v2 from MC toy
            hPT[ipt]->Fill(0.5+centrality, pt, 1);
            pV2MC->Fill(0.5+centrality, pt, v2);
          }
          if ( (phi0[itrk]>A && phi0[itrk]<B) || (phi0[itrk]>C && phi0[itrk]<D) ) continue; // acceptance filter
          // ================= Direct cumulants ================= //
          // RFP
          if (eta0[itrk] < -eta_gap)
          {
            Qx2 += TMath::Cos(2. * phi0[itrk]);
            Qy2 += TMath::Sin(2. * phi0[itrk]);
            Qx4 += TMath::Cos(4. * phi0[itrk]);
            Qy4 += TMath::Sin(4. * phi0[itrk]);   
            M++;
          }
          // POI
          if (eta0[itrk] > eta_gap)
          {
            px2[ipt] += TMath::Cos(2. * phi0[itrk]);
            py2[ipt] += TMath::Sin(2. * phi0[itrk]); 
            mp[ipt]++;
          }

          float v2,v2RAW;
          
          if(eta0[itrk]>eta_gap){ // eta+
            v2 = cos(2.0 * (phi0[itrk]-fPsiFlat[0]) )/res2[centrality];
            v2RAW = cos(2.0 * (phi0[itrk]-fPsiRaw[0]) )/res2RAW[centrality];

          }
          if(eta0[itrk]<-eta_gap){ // eta-
            v2 = cos(2.0 * (phi0[itrk]-fPsiFlat[1]) )/res2[centrality];
            v2RAW = cos(2.0 * (phi0[itrk]-fPsiRaw[1]) )/res2RAW[centrality];

          }

          if (eta0[itrk] < -eta_gap) { // Reference flow
            pV2etasub->Fill(0.5+centrality, pt, v2);
            pV2etasubRAW->Fill(0.5+centrality, pt, v2RAW);
          }
          
          // } // end of |eta| < 1.0
        }// end of the track loop


        // ================= Direct cumulants ================= //
        
        if (M >= 2.)
        { // <2> definition condition
          Q2 = TComplex(Qx2, Qy2);
          w2 = M * (M - 1.);                 // w(<2>)
          cor22 = CalCor22(Q2, M, w2);       // <2>
          hv22[centrality]->Fill(0.5, cor22, w2); // <<2>>

          // Non-uniform acceptance correction
          hcos2phi1 -> Fill(0.5+centrality,Qx2/M,M);
          hsin2phi1 -> Fill(0.5+centrality,Qy2/M,M);
        } // end of <2> definition condition
        for (int ipt = 0; ipt < npt; ipt++)
        {
          if (mp[ipt] == 0 || M < 1)
            continue;

          p2[ipt] = TComplex(px2[ipt], py2[ipt]);
          q2[ipt] = TComplex(qx2[ipt], qy2[ipt]);
          wred2[ipt] = mp[ipt] * M - mq[ipt];                                        // w(<2'>)
          redCor22[ipt] = CalRedCor22(Q2, p2[ipt], M, mp[ipt], mq[ipt], wred2[ipt]); // <2'>
          hv22pt[centrality][ipt]->Fill(0.5, redCor22[ipt], wred2[ipt]);                  // <<2'>>

          // TProfile for covariance calculation in statistic error
          hcov22prime[centrality][ipt]->Fill(0.5, cor22 * redCor22[ipt], w2 * wred2[ipt]); // <2>*<2'>

          // Non-uniform acceptance correction
          hcos2psi1[ipt] -> Fill(0.5+centrality,px2[ipt]/mp[ipt],mp[ipt]);
          hsin2psi1[ipt] -> Fill(0.5+centrality,py2[ipt]/mp[ipt],mp[ipt]);
        }

        if (M >= 4.)
        { // <4> definition condition
          Q4 = TComplex(Qx4, Qy4);
          w4 = M * (M - 1.) * (M - 2.) * (M - 3.);  // w(<4>)
          cor24 = CalCor24(Q2, Q4, M, w4);          // <4>
          hv24[centrality]->Fill(0.5, cor24, w4);        // <<4>>

          // TProfile for covariance calculation in statistic error
          hcov24[centrality]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>

          // Non-uniform acceptance correction
          Double_t cos2phi12=(Q2 * Q2 - Q4).Re();
          Double_t sin2phi12=(Q2 * Q2 - Q4).Im();
          Double_t cos2phi123=((Q2 * Qstar(Q2) * Qstar(Q2) - Q2 * Qstar(Q4)).Re()) - 2. * (M - 1.) * (Qstar(Q2).Re());
          Double_t sin2phi123=((Q2 * Qstar(Q2) * Qstar(Q2) - Q2 * Qstar(Q4)).Im()) - 2. * (M - 1.) * (Qstar(Q2).Im());
          Double_t sumMMm1=M*(M-1);
          Double_t sumMMm1Mm2=M*(M-1)*(M-2);
          hcos2phi12  -> Fill( 0.5+centrality, cos2phi12/sumMMm1, sumMMm1);
          hsin2phi12  -> Fill( 0.5+centrality, sin2phi12/sumMMm1, sumMMm1);
          hcos2phi123 -> Fill( 0.5+centrality, cos2phi123/sumMMm1Mm2, sumMMm1Mm2);
          hsin2phi123 -> Fill( 0.5+centrality, sin2phi123/sumMMm1Mm2, sumMMm1Mm2);
        } // end of <4> definition condition
        for (int ipt = 0; ipt < npt; ipt++)
        {
          if (mp[ipt] == 0 || M < 3)
            continue;
          q4[ipt] = TComplex(qx4[ipt], qy4[ipt]);
          wred4[ipt] = (mp[ipt]*M-3*mq[ipt])*(M-1)*(M-2);                                 // w(<4'>)
          redCor24[ipt] = CalRedCor24(Q2, Q4, p2[ipt], q2[ipt], q4[ipt], M, mp[ipt], mq[ipt], wred4[ipt]);  // <4'>
          hv24pt[centrality][ipt]->Fill(0.5, redCor24[ipt], wred4[ipt]);                                          // <<4'>>

          // TProfile for covariance calculation in statistic error
          hcov24prime[centrality][ipt]->Fill(0.5, cor22 * redCor24[ipt], w2 * wred4[ipt]);
          hcov42prime[centrality][ipt]->Fill(0.5, cor24 * redCor22[ipt], w4 * wred2[ipt]);
          hcov44prime[centrality][ipt]->Fill(0.5, cor24 * redCor24[ipt], w4 * wred4[ipt]);
          hcov2prime4prime[centrality][ipt]->Fill(0.5, redCor22[ipt] * redCor24[ipt], wred2[ipt] * wred4[ipt]);

          // Non-uniform acceptance correction
          hcos2psi1phi2[ipt] -> Fill(0.5+centrality,(p2[ipt] * Q2 - q4[ipt]).Re()/(mp[ipt]*M-mq[ipt]),(mp[ipt]*M-mq[ipt]));
          hsin2psi1phi2[ipt] -> Fill(0.5+centrality,(p2[ipt] * Q2 - q4[ipt]).Im()/(mp[ipt]*M-mq[ipt]),(mp[ipt]*M-mq[ipt]));
          hcos2psi1pphi23[ipt] -> Fill(0.5+centrality,(((p2[ipt]*(Q2.Rho2()-M)).Re())-((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Re()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),(mp[ipt]*M-2*mq[ipt])*(M-1));
          hsin2psi1pphi23[ipt] -> Fill(0.5+centrality,(((p2[ipt]*(Q2.Rho2()-M)).Im())-((q4[ipt]*Qstar(Q2)+mq[ipt]*Q2-2.*q2[ipt]).Im()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),(mp[ipt]*M-2*mq[ipt])*(M-1));
          hcos2psi1mphi23[ipt] -> Fill(0.5+centrality,(((p2[ipt] * Qstar(Q2) * Qstar(Q2) - p2[ipt] * Qstar(Q4)).Re()) - ((2. * mq[ipt] * Qstar(Q2) - 2. * Qstar(q2[ipt])).Re()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),((mp[ipt]*M-2*mq[ipt])*(M-1)));
          hsin2psi1mphi23[ipt] -> Fill(0.5+centrality,(((p2[ipt] * Qstar(Q2) * Qstar(Q2) - p2[ipt] * Qstar(Q4)).Im()) - ((2. * mq[ipt] * Qstar(Q2) - 2. * Qstar(q2[ipt])).Im()))/((mp[ipt]*M-2*mq[ipt])*(M-1)),((mp[ipt]*M-2*mq[ipt])*(M-1)));
        }
      }


    } // end of if (fRunNum> =2 )
  } // end of  loop over all entries (nentries) of chain
  treefile->Close();
  cout <<"File \"" << file << "\" is processed" << endl;
}

void FlowANA::Ana_end()
{
  d_outfile->cd();
  // d_outfile->Write();
  if (fRunNum == 0)
  {
    for (Int_t ieta = 0; ieta<neta; ieta++)
    {
      pQy[ieta]->Write();
      pQx[ieta]->Write();
    }
  }
  else if (fRunNum == 1)
  {
    for( int ieta=0; ieta<neta; ieta++ ){
      for (int iharm=0;iharm<nharm;iharm++){
        pCosNPsi[ieta][iharm]->Write();
        pSinNPsi[ieta][iharm]->Write();
      }
    }
  }
  else if (fRunNum == 2)
  {
    for (Int_t icent = 0; icent<ncent; icent++)
    {
      for (Int_t ieta = 0; ieta<neta; ieta++)
      {
        hQMultRaw[icent][ieta]->Write();
        hQvecRaw[icent][ieta]->Write();
        hQvecRec[icent][ieta]->Write();
        hPsiRaw[icent][ieta]->Write();
        hPsiRecentered[icent][ieta]->Write();
        hPsiFlattened[icent][ieta]->Write();
      }
    }
    hPsiRawMB->Write();
    hPsiRecMB->Write();
    hPsiFlatMB->Write();
    pRes->Write();
    pResRAW->Write();

  }
  else
  {
    pV2etasubRAW->Write();
    pV2etasub->Write();
    pV2MC->Write();

    hcos2phi1->Write();
    hsin2phi1->Write();
    hcos2phi12->Write();
    hsin2phi12->Write();
    hcos2phi123->Write();
    hsin2phi123->Write();
    for (int ipt=0;ipt<npt;ipt++){
      hPT[ipt]->Write();
      hcos2psi1[ipt]->Write();
      hsin2psi1[ipt]->Write();
      hcos2psi1phi2[ipt]->Write();
      hsin2psi1phi2[ipt]->Write();
      hcos2psi1pphi23[ipt]->Write();
      hsin2psi1pphi23[ipt]->Write();
      hcos2psi1mphi23[ipt]->Write();
      hsin2psi1mphi23[ipt]->Write();
    }
    for (int icent=0;icent<ncent;icent++){
      hv22[icent]->Write();
      hv24[icent]->Write();
      hcov24[icent]->Write();
      for (int ipt=0;ipt<npt;ipt++){
        hv22pt[icent][ipt]->Write();
        hv24pt[icent][ipt]->Write();
        hcov22prime[icent][ipt]->Write();
        hcov24prime[icent][ipt]->Write();
        hcov42prime[icent][ipt]->Write();
        hcov44prime[icent][ipt]->Write();
        hcov2prime4prime[icent][ipt]->Write();
      }
    }
  }
  d_outfile->Close();
  cout << "Histfile has been written" << endl;
}

void FlowANA::Recentering()
{
  for (int ieta=0; ieta<neta; ieta++){
    if (sumQxy[ieta][0]==0 && sumQxy[ieta][1]==0) continue;
    pQx[ieta]->Fill(0.5+centrality, sumQxy[ieta][0]);
    pQy[ieta]->Fill(0.5+centrality, sumQxy[ieta][1]);
  }
}

void FlowANA::FinishRecentering()
{
  cout << "Recentering..." << endl;
  TFile *fi = new TFile("FirstRun.root","read");
  for( int ieta=0; ieta<neta; ieta++ ){
    TProfile *tmp1 = dynamic_cast<TProfile*> (fi->Get(Form("pQx_%i",ieta)));
    TProfile *tmp2 = dynamic_cast<TProfile*> (fi->Get(Form("pQy_%i",ieta)));
    for (int icent=0; icent<ncent; icent++){
      qxMean[icent][ieta] = tmp1->GetBinContent(icent + 1);
      qyMean[icent][ieta] = tmp2->GetBinContent(icent + 1);
    }
  }
  fi->Close();
}

void FlowANA::Flattening()
{
  // if (sumQxy[ieta][0]==0 && sumQxy[ieta][1]==0) continue;
  if (multQv[0]==0 || multQv[1] == 0) return;
  for( int ieta=0; ieta<neta; ieta++ ){
    qxRec = sumQxy[ieta][0] - qxMean[centrality][ieta];
    qyRec = sumQxy[ieta][1] - qyMean[centrality][ieta];
    psi2 = TMath::ATan2(qyRec, qxRec) / 2.;

    // Fill Flattening profiles
    for (int iharm=0;iharm<nharm;iharm++){
      pCosNPsi[ieta][iharm]->Fill(0.5+centrality, TMath::Cos( 2*(iharm+1)*psi2));
      pSinNPsi[ieta][iharm]->Fill(0.5+centrality, TMath::Sin( 2*(iharm+1)*psi2));
    }
  }
}
void FlowANA::FinishFlattening(){
  cout << "Flattening..." << endl;
  TFile *fi = new TFile("SecondRun.root","read");
  for( int ieta=0; ieta<neta; ieta++ ){
    for( int iharm=0; iharm<nharm; iharm++ ){

      TProfile *tmp1 = dynamic_cast<TProfile*> (fi->Get(Form("pCosNPsi_%i_%i_rec", ieta,iharm)));
      TProfile *tmp2 = dynamic_cast<TProfile*> (fi->Get(Form("pSinNPsi_%i_%i_rec", ieta,iharm)));
      for (int icent=0; icent<ncent; icent++){
        cosNPhiMean[ieta][iharm][icent] = tmp1->GetBinContent(icent + 1);
        sinNPhiMean[ieta][iharm][icent] = tmp2->GetBinContent(icent + 1);
      }
    }
  }
  fi->Close();
}

void FlowANA::Resolution()
{
}
void FlowANA::FinishResolution(){
  cout << "Resolution..." << endl;
  TFile *fi = new TFile("ThirdRun.root","read");
  TProfile *tmp1 = dynamic_cast<TProfile*> (fi->Get("pRes"));
  TProfile *tmp2 = dynamic_cast<TProfile*> (fi->Get("pResRAW"));

  cout << " Double_t res2[" << ncent <<"] = {";
  for (int icent=0; icent<ncent; icent++){
    res2[icent] = TMath::Sqrt(tmp1->GetBinContent(icent+1));
    res2RAW[icent] = TMath::Sqrt(tmp2->GetBinContent(icent+1));

    cout << res2[icent];
    if (icent!= (ncent-1)) cout << ", ";
  }
  cout << "};" <<endl;
  fi->Close();

}



void FlowANA::CalFlow()
{
}