#include <FlowAnalysisWithQCumulantGenericFramework.h>
ClassImp(FlowAnalysisWithQCumulantGenericFramework);
FlowAnalysisWithQCumulantGenericFramework::FlowAnalysisWithQCumulantGenericFramework() :
M(0),
fUseWeight(kFALSE)
{
  Zero();
}

FlowAnalysisWithQCumulantGenericFramework::~FlowAnalysisWithQCumulantGenericFramework()
{
}

void FlowAnalysisWithQCumulantGenericFramework::Init()
{
  for (Int_t icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv22[icent] = new TProfile(Form("hv22_%i", icent), Form("hv22_%i", icent), 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), Form("hv24_%i", icent), 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), Form("hcov24_%i", icent), 1, 0., 1.);
    hcov24Gap[icent] = new TProfile(Form("hcov24Gap_%i", icent), Form("hcov24Gap_%i", icent), 1, 0., 1.);
    hv22Gap[icent] = new TProfile(Form("hv22Gap_%i", icent), Form("hv22Gap_%i", icent), 1, 0., 1.);
    hv24Gap[icent] = new TProfile(Form("hv24Gap_%i", icent), Form("hv24Gap_%i", icent), 1, 0., 1.);
    for (Int_t id = 0; id < npid; id++)
    {
      for (Int_t ipt = 0; ipt < npt; ipt++)
      { // loop over pt bin
        hv22pt[icent][ipt][id] = new TProfile(Form("hv22pt_%i_%i_%i", icent, ipt, id), Form("hv22pt_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hv24pt[icent][ipt][id] = new TProfile(Form("hv24pt_%i_%i_%i", icent, ipt, id), Form("hv24pt_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov22prime[icent][ipt][id] = new TProfile(Form("hcov22prime_%i_%i_%i", icent, ipt, id), Form("hcov22prime_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov24prime[icent][ipt][id] = new TProfile(Form("hcov24prime_%i_%i_%i", icent, ipt, id), Form("hcov24prime_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov42prime[icent][ipt][id] = new TProfile(Form("hcov42prime_%i_%i_%i", icent, ipt, id), Form("hcov42prime_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov44prime[icent][ipt][id] = new TProfile(Form("hcov44prime_%i_%i_%i", icent, ipt, id), Form("hcov44prime_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov2prime4prime[icent][ipt][id] = new TProfile(Form("hcov2prime4prime_%i_%i_%i", icent, ipt, id), Form("hcov2prime4prime_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcounter[icent][ipt][id] = new TProfile(Form("hcounter_%i_%i_%i", icent, ipt, id), Form("hcounter_%i_%i_%i", icent, ipt, id), 3, 0., 3.);
        hv22ptGap[icent][ipt][id] = new TProfile(Form("hv22ptGap_%i_%i_%i", icent, ipt, id), Form("hv22ptGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hv24ptGap[icent][ipt][id] = new TProfile(Form("hv24ptGap_%i_%i_%i", icent, ipt, id), Form("hv24ptGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov22primeGap[icent][ipt][id] = new TProfile(Form("hcov22primeGap_%i_%i_%i", icent, ipt, id), Form("hcov22primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov24primeGap[icent][ipt][id] = new TProfile(Form("hcov24primeGap_%i_%i_%i", icent, ipt, id), Form("hcov24primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov42primeGap[icent][ipt][id] = new TProfile(Form("hcov42primeGap_%i_%i_%i", icent, ipt, id), Form("hcov42primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);      
        hcov44primeGap[icent][ipt][id] = new TProfile(Form("hcov44primeGap_%i_%i_%i", icent, ipt, id), Form("hcov44primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
        hcov2prime4primeGap[icent][ipt][id] = new TProfile(Form("hcov2prime4primeGap_%i_%i_%i", icent, ipt, id), Form("hcov2prime4primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
      } // end of loop over pt bin
    }
  } // end of loop over centrality classes

}

void FlowAnalysisWithQCumulantGenericFramework::Zero()
{
  M = 0;
  for(Int_t h=0;h<maxHarmonic;h++)
  {
    for(Int_t p=0;p<maxPower;p++)
    {
      fQvector[h][p](0.,0.);
      fQvectorGapPos[h][p](0.,0.);
      fQvectorGapNeg[h][p](0.,0.);
      for(Int_t ipt(0);ipt<npt;ipt++)
      {
        for(Int_t id(0);id<npid;id++)
        {
          fPvector[h][p][ipt][id](0.,0.);
          fSvector[h][p][ipt][id](0.,0.);
          fPvectorGapPos[h][p][ipt][id](0.,0.);
          fSvectorGapPos[h][p][ipt][id](0.,0.);
          fPvectorGapNeg[h][p][ipt][id](0.,0.);
          fSvectorGapNeg[h][p][ipt][id](0.,0.);        
        }
      }
    }
  }
}

void FlowAnalysisWithQCumulantGenericFramework::ProcessFirstTrackLoopRP(const Double_t &eta, const Double_t &phi)
{
  Double_t dWeight = 1.0;
  for(Int_t h=0;h<maxHarmonic;h++)
  {
    for(Int_t p=0;p<maxPower;p++)
    {
      fQvector[h][p] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
      if (eta <-fEtaGap)
        fQvectorGapNeg[h][p] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
      if (eta > fEtaGap)
        fQvectorGapPos[h][p] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
    }
  }
  M++;
}

void FlowAnalysisWithQCumulantGenericFramework::ProcessFirstTrackLoopPOI(const Int_t &ipt, const double &eta, const double &phi, const Int_t &pid, const double &charge)
{
  Double_t dWeight = 1.0;
  for(Int_t h=0;h<maxHarmonic;h++){
    for(Int_t p=0;p<maxPower;p++){
      if (charge > 0)
      {
        fSvector[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        fPvector[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        if (eta < -fEtaGap)
        {
          fSvectorGapNeg[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapNeg[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
        if (eta > fEtaGap)
        {
          fSvectorGapPos[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapPos[h][p][ipt][0] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
      }
      if (charge < 0)
      {
        fSvector[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        fPvector[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        if (eta < -fEtaGap)
        {
          fSvectorGapNeg[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapNeg[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
        if (eta > fEtaGap)
        {
          fSvectorGapPos[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapPos[h][p][ipt][4] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
      }
      if (pid > 0)
      {
        fSvector[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        fPvector[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
        if (eta < -fEtaGap)
        {
          fSvectorGapNeg[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapNeg[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
        if (eta > fEtaGap)
        {
          fSvectorGapPos[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));
          fPvectorGapPos[h][p][ipt][pid] += TMath::Power(dWeight,p)*TComplex(TMath::Cos(h*phi),TMath::Sin(h*phi));  
        }
      }
    }
  }
} 

void FlowAnalysisWithQCumulantGenericFramework::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  Double_t w2 = Two(0,0).Re();
  Double_t w4 = Four(0,0,0,0).Re();
  if (w2!=0. && w4!=0.)
  {
    Double_t cor22 = Two(h1,h2).Re() / w2;
    Double_t cor24 = Four(h1,h2,h3,h4).Re() / w4;
    hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
    hv24[icent]->Fill(0.5, cor24, w4); // <<4>>
    hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t id = 0; id < npid; id++)
      {
        Double_t wred2 = TwoDiff(0,0,ipt,id).Re();
        Double_t wred4 = FourDiff(0,0,0,0,ipt,id).Re();
        if (wred2!=0 && wred4!=0)
        {
          Double_t redCor22 = TwoDiff(h1,h2,ipt,id).Re() / wred2;
          Double_t redCor24 = FourDiff(h1,h2,h3,h4,ipt,id).Re() / wred4;
          hv22pt[icent][ipt][id]->Fill(0.5, redCor22, wred2);
          hv24pt[icent][ipt][id]->Fill(0.5, redCor24, wred4);
          hcov22prime[icent][ipt][id]->Fill(0.5, cor22 * redCor22, w2 * wred2); // <2>*<2'>
          hcov24prime[icent][ipt][id]->Fill(0.5, cor22 * redCor24, w2 * wred4);
          hcov42prime[icent][ipt][id]->Fill(0.5, cor24 * redCor22, w4 * wred2);
          hcov44prime[icent][ipt][id]->Fill(0.5, cor24 * redCor24, w4 * wred4);
          hcov2prime4prime[icent][ipt][id]->Fill(0.5, redCor22 * redCor24, wred2 * wred4);
        }
      }
    }
  }

  Double_t w2Gap = TwoGap(0,0).Re();
  Double_t w4Gap = FourGap(0,0,0,0).Re();
  if (w2Gap!=0. && w4Gap!=0.)
  {
    Double_t cor22Gap = TwoGap(h1,h2).Re() / w2Gap;
    Double_t cor24Gap = FourGap(h1,h3,h2,h4).Re() / w4Gap;
    hv22Gap[icent]->Fill(0.5, cor22Gap, w2Gap);
    hv24Gap[icent]->Fill(0.5, cor24Gap, w4Gap);
    hcov24Gap[icent]->Fill(0.5, cor22Gap * cor24Gap, w2Gap * w4Gap); // <2>*<4>
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t id = 0; id < npid; id++)
      {
        Double_t wred2GapPos = TwoDiffGapPos(0,0,ipt,id).Re();
        Double_t wred4GapPos = FourDiffGapPos(0,0,0,0,ipt,id).Re();
        if (wred2GapPos>0. && wred4GapPos>0.)
        {
          Double_t redCor22GapPos = TwoDiffGapPos(h1,h2,ipt,id).Re() / wred2GapPos;
          Double_t redCor24GapPos = FourDiffGapPos(h1,h3,h2,h4,ipt,id).Re() / wred4GapPos;
          hv22ptGap[icent][ipt][id]->Fill(0.5, redCor22GapPos, wred2GapPos);
          hv24ptGap[icent][ipt][id]->Fill(0.5, redCor24GapPos, wred4GapPos); 
          // hcounter[icent][ipt][id]->Fill(1.5, 1, mpGap[ieta][ipt][id]);
          // Covariances
          hcov22primeGap[icent][ipt][id]->Fill(0.5, cor22Gap * redCor22GapPos, w2Gap * wred2GapPos);                                          // <2>*<2'>
          hcov24primeGap[icent][ipt][id]->Fill(0.5, cor22Gap * redCor24GapPos, w2Gap * wred4GapPos);                                          // <2>*<4'>
          hcov42primeGap[icent][ipt][id]->Fill(0.5, cor24Gap * redCor22GapPos, w4Gap * wred2GapPos);                                          // <4>*<2'>  
          hcov44primeGap[icent][ipt][id]->Fill(0.5, cor24Gap * redCor24GapPos, w4Gap * wred4GapPos);                                          // <4>*<4'>
          hcov2prime4primeGap[icent][ipt][id]->Fill(0.5, redCor22GapPos*redCor24GapPos, wred2GapPos*wred4GapPos);     // <2'>*<4'>
        }
        Double_t wred2GapNeg = TwoDiffGapNeg(0,0,ipt,id).Re();
        Double_t wred4GapNeg = FourDiffGapNeg(0,0,0,0,ipt,id).Re();
        if (wred2GapNeg>0. && wred4GapNeg>0.)
        {
          Double_t redCor22GapNeg = TwoDiffGapNeg(h1,h2,ipt,id).Re() / wred2GapNeg;
          Double_t redCor24GapNeg = FourDiffGapNeg(h1,h3,h2,h4,ipt,id).Re() / wred4GapNeg;
          hv22ptGap[icent][ipt][id]->Fill(0.5, redCor22GapNeg, wred2GapNeg);
          hv24ptGap[icent][ipt][id]->Fill(0.5, redCor24GapNeg, wred4GapNeg); 
          // hcounter[icent][ipt][id]->Fill(1.5, 1, mpGap[ieta][ipt][id]);
          // Covariances
          hcov22primeGap[icent][ipt][id]->Fill(0.5, cor22Gap * redCor22GapNeg, w2Gap * wred2GapNeg);                                          // <2>*<2'>
          hcov24primeGap[icent][ipt][id]->Fill(0.5, cor22Gap * redCor24GapNeg, w2Gap * wred4GapNeg);                                          // <2>*<4'>
          hcov42primeGap[icent][ipt][id]->Fill(0.5, cor24Gap * redCor22GapNeg, w4Gap * wred2GapNeg);                                          // <4>*<2'>  
          hcov44primeGap[icent][ipt][id]->Fill(0.5, cor24Gap * redCor24GapNeg, w4Gap * wred4GapNeg);                                          // <4>*<4'>
          hcov2prime4primeGap[icent][ipt][id]->Fill(0.5, redCor22GapNeg*redCor24GapNeg, wred2GapNeg*wred4GapNeg);     // <2'>*<4'>
        }
      }
    }
  }
}

void FlowAnalysisWithQCumulantGenericFramework::SaveHist()
{


  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent]->Write();
    hv24[icent]->Write();
    hcov24[icent]->Write();
    hv22Gap[icent]->Write();
    hcov24Gap[icent]->Write();
    hv24Gap[icent]->Write();    
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv22pt[icent][ipt][id]->Write();
        hv24pt[icent][ipt][id]->Write();
        hcov22prime[icent][ipt][id]->Write();
        hcov24prime[icent][ipt][id]->Write();
        hcov42prime[icent][ipt][id]->Write();
        hcov44prime[icent][ipt][id]->Write();
        hcov2prime4prime[icent][ipt][id]->Write();
        hcounter[icent][ipt][id]->Write();
        hv22ptGap[icent][ipt][id]->Write();
        hv24ptGap[icent][ipt][id]->Write();
        hcov22primeGap[icent][ipt][id]->Write();
        hcov24primeGap[icent][ipt][id]->Write();
        hcov42primeGap[icent][ipt][id]->Write();
        hcov44primeGap[icent][ipt][id]->Write();
        hcov2prime4primeGap[icent][ipt][id]->Write();
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes

}

TComplex FlowAnalysisWithQCumulantGenericFramework::Q(const Int_t n, const Int_t p) const
{
  if (n < 0) return TComplex::Conjugate(fQvector[-n][p]);
  else return fQvector[n][p];
}

TComplex FlowAnalysisWithQCumulantGenericFramework::QGapPos(const Int_t n, const Int_t p) const
{
  if (n < 0) return TComplex::Conjugate(fQvectorGapPos[-n][p]);
  else return fQvectorGapPos[n][p];
}

TComplex FlowAnalysisWithQCumulantGenericFramework::QGapNeg(const Int_t n, const Int_t p) const
{
  if(n < 0) return TComplex::Conjugate(fQvectorGapNeg[-n][p]);
  else return fQvectorGapNeg[n][p];
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Two(const Int_t n1, const Int_t n2) const
{
  TComplex two = Q(n1,1)*Q(n2,1) - Q(n1+n2,2);
  return two;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::TwoGap(const Int_t n1, const Int_t n2) const
{
  TComplex twoGap = QGapPos(n1,1)*QGapNeg(n2,1);
  return twoGap;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Three(const Int_t n1, const Int_t n2, const Int_t n3) const
{
  TComplex three = Q(n1,1)*Q(n2,1)*Q(n3,1)-Q(n1+n2,2)*Q(n3,1)-Q(n2,1)*Q(n1+n3,2)-Q(n1,1)*Q(n2+n3,2)+2.0*Q(n1+n2+n3,3);
  return three; 
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Four(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4) const
{
  TComplex four = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)-Q(n2,1)*Q(n1+n3,2)*Q(n4,1)
                - Q(n1,1)*Q(n2+n3,2)*Q(n4,1)+2.0*Q(n1+n2+n3,3)*Q(n4,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)
                + Q(n2+n3,2)*Q(n1+n4,2)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)+Q(n1+n3,2)*Q(n2+n4,2)
                + 2.0*Q(n3,1)*Q(n1+n2+n4,3)-Q(n1,1)*Q(n2,1)*Q(n3+n4,2)+Q(n1+n2,2)*Q(n3+n4,2)
                + 2.0*Q(n2,1)*Q(n1+n3+n4,3)+2.0*Q(n1,1)*Q(n2+n3+n4,3)-6.0*Q(n1+n2+n3+n4,4);
  return four;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::FourGap(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4) const
{
  TComplex formula = QGapPos(n1,1)*QGapPos(n2,1)*QGapNeg(n3,1)*QGapNeg(n4,1)-QGapPos(n1+n2,2)*QGapNeg(n3,1)*QGapNeg(n4,1)
                    -QGapPos(n1,1)*QGapPos(n2,1)*QGapNeg(n3+n4,2)+QGapPos(n1+n2,2)*QGapNeg(n3+n4,2);
  //same as
  //TComplex formula = TwoPos(n1,n2)*TwoNeg(n3,n4);
	return formula;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Five(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5) const
{
  TComplex five = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)
  - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)
  + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)
  + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)
  + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)
  - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)
  + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)
  - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)
  + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)
  + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)
  - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)
  + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)
  - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)
  - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)
  + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)
  + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)
  + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)
  + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)
  - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)
  + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)
  + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)
  + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)
  + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)
  - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)
  - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)
  - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)+24.*Q(n1+n2+n3+n4+n5,5);
  return five;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Six(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5, const Int_t n6) const
{
  TComplex six = Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n6,1)
  - Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n6,1)
  + 2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)
  + Q(n2+n3,2)*Q(n1+n4,2)*Q(n5,1)*Q(n6,1)-Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)
  + Q(n1+n3,2)*Q(n2+n4,2)*Q(n5,1)*Q(n6,1)+2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5,1)*Q(n6,1)
  - Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)+Q(n1+n2,2)*Q(n3+n4,2)*Q(n5,1)*Q(n6,1)
  + 2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5,1)*Q(n6,1)+2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5,1)*Q(n6,1)
  - 6.*Q(n1+n2+n3+n4,4)*Q(n5,1)*Q(n6,1)-Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)
  + Q(n2+n3,2)*Q(n4,1)*Q(n1+n5,2)*Q(n6,1)+Q(n3,1)*Q(n2+n4,2)*Q(n1+n5,2)*Q(n6,1)
  + Q(n2,1)*Q(n3+n4,2)*Q(n1+n5,2)*Q(n6,1)-2.*Q(n2+n3+n4,3)*Q(n1+n5,2)*Q(n6,1)
  - Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)+Q(n1+n3,2)*Q(n4,1)*Q(n2+n5,2)*Q(n6,1)
  + Q(n3,1)*Q(n1+n4,2)*Q(n2+n5,2)*Q(n6,1)+Q(n1,1)*Q(n3+n4,2)*Q(n2+n5,2)*Q(n6,1)
  - 2.*Q(n1+n3+n4,3)*Q(n2+n5,2)*Q(n6,1)+2.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5,3)*Q(n6,1)
  - 2.*Q(n3+n4,2)*Q(n1+n2+n5,3)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)
  + Q(n1+n2,2)*Q(n4,1)*Q(n3+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n4,2)*Q(n3+n5,2)*Q(n6,1)
  + Q(n1,1)*Q(n2+n4,2)*Q(n3+n5,2)*Q(n6,1)-2.*Q(n1+n2+n4,3)*Q(n3+n5,2)*Q(n6,1)
  + 2.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5,3)*Q(n6,1)-2.*Q(n2+n4,2)*Q(n1+n3+n5,3)*Q(n6,1)
  + 2.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5,3)*Q(n6,1)-2.*Q(n1+n4,2)*Q(n2+n3+n5,3)*Q(n6,1)
  - 6.*Q(n4,1)*Q(n1+n2+n3+n5,4)*Q(n6,1)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)
  + Q(n1+n2,2)*Q(n3,1)*Q(n4+n5,2)*Q(n6,1)+Q(n2,1)*Q(n1+n3,2)*Q(n4+n5,2)*Q(n6,1)
  + Q(n1,1)*Q(n2+n3,2)*Q(n4+n5,2)*Q(n6,1)-2.*Q(n1+n2+n3,3)*Q(n4+n5,2)*Q(n6,1)
  + 2.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5,3)*Q(n6,1)-2.*Q(n2+n3,2)*Q(n1+n4+n5,3)*Q(n6,1)
  + 2.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5,3)*Q(n6,1)-2.*Q(n1+n3,2)*Q(n2+n4+n5,3)*Q(n6,1)
  - 6.*Q(n3,1)*Q(n1+n2+n4+n5,4)*Q(n6,1)+2.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5,3)*Q(n6,1)
  - 2.*Q(n1+n2,2)*Q(n3+n4+n5,3)*Q(n6,1)-6.*Q(n2,1)*Q(n1+n3+n4+n5,4)*Q(n6,1)
  - 6.*Q(n1,1)*Q(n2+n3+n4+n5,4)*Q(n6,1)+24.*Q(n1+n2+n3+n4+n5,5)*Q(n6,1)
  - Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)+Q(n2+n3,2)*Q(n4,1)*Q(n5,1)*Q(n1+n6,2)
  + Q(n3,1)*Q(n2+n4,2)*Q(n5,1)*Q(n1+n6,2)+Q(n2,1)*Q(n3+n4,2)*Q(n5,1)*Q(n1+n6,2)
  - 2.*Q(n2+n3+n4,3)*Q(n5,1)*Q(n1+n6,2)+Q(n3,1)*Q(n4,1)*Q(n2+n5,2)*Q(n1+n6,2)
  - Q(n3+n4,2)*Q(n2+n5,2)*Q(n1+n6,2)+Q(n2,1)*Q(n4,1)*Q(n3+n5,2)*Q(n1+n6,2)
  - Q(n2+n4,2)*Q(n3+n5,2)*Q(n1+n6,2)-2.*Q(n4,1)*Q(n2+n3+n5,3)*Q(n1+n6,2)
  + Q(n2,1)*Q(n3,1)*Q(n4+n5,2)*Q(n1+n6,2)-Q(n2+n3,2)*Q(n4+n5,2)*Q(n1+n6,2)
  - 2.*Q(n3,1)*Q(n2+n4+n5,3)*Q(n1+n6,2)-2.*Q(n2,1)*Q(n3+n4+n5,3)*Q(n1+n6,2)
  + 6.*Q(n2+n3+n4+n5,4)*Q(n1+n6,2)-Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)
  + Q(n1+n3,2)*Q(n4,1)*Q(n5,1)*Q(n2+n6,2)+Q(n3,1)*Q(n1+n4,2)*Q(n5,1)*Q(n2+n6,2)
  + Q(n1,1)*Q(n3+n4,2)*Q(n5,1)*Q(n2+n6,2)-2.*Q(n1+n3+n4,3)*Q(n5,1)*Q(n2+n6,2)
  + Q(n3,1)*Q(n4,1)*Q(n1+n5,2)*Q(n2+n6,2)-Q(n3+n4,2)*Q(n1+n5,2)*Q(n2+n6,2)
  + Q(n1,1)*Q(n4,1)*Q(n3+n5,2)*Q(n2+n6,2)-Q(n1+n4,2)*Q(n3+n5,2)*Q(n2+n6,2)
  - 2.*Q(n4,1)*Q(n1+n3+n5,3)*Q(n2+n6,2)+Q(n1,1)*Q(n3,1)*Q(n4+n5,2)*Q(n2+n6,2)
  - Q(n1+n3,2)*Q(n4+n5,2)*Q(n2+n6,2)-2.*Q(n3,1)*Q(n1+n4+n5,3)*Q(n2+n6,2)
  - 2.*Q(n1,1)*Q(n3+n4+n5,3)*Q(n2+n6,2)+6.*Q(n1+n3+n4+n5,4)*Q(n2+n6,2)
  + 2.*Q(n3,1)*Q(n4,1)*Q(n5,1)*Q(n1+n2+n6,3)-2.*Q(n3+n4,2)*Q(n5,1)*Q(n1+n2+n6,3)
  - 2.*Q(n4,1)*Q(n3+n5,2)*Q(n1+n2+n6,3)-2.*Q(n3,1)*Q(n4+n5,2)*Q(n1+n2+n6,3)
  + 4.*Q(n3+n4+n5,3)*Q(n1+n2+n6,3)-Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)
  + Q(n1+n2,2)*Q(n4,1)*Q(n5,1)*Q(n3+n6,2)+Q(n2,1)*Q(n1+n4,2)*Q(n5,1)*Q(n3+n6,2)
  + Q(n1,1)*Q(n2+n4,2)*Q(n5,1)*Q(n3+n6,2)-2.*Q(n1+n2+n4,3)*Q(n5,1)*Q(n3+n6,2)
  + Q(n2,1)*Q(n4,1)*Q(n1+n5,2)*Q(n3+n6,2)-Q(n2+n4,2)*Q(n1+n5,2)*Q(n3+n6,2)
  + Q(n1,1)*Q(n4,1)*Q(n2+n5,2)*Q(n3+n6,2)-Q(n1+n4,2)*Q(n2+n5,2)*Q(n3+n6,2)
  - 2.*Q(n4,1)*Q(n1+n2+n5,3)*Q(n3+n6,2)+Q(n1,1)*Q(n2,1)*Q(n4+n5,2)*Q(n3+n6,2)
  - Q(n1+n2,2)*Q(n4+n5,2)*Q(n3+n6,2)-2.*Q(n2,1)*Q(n1+n4+n5,3)*Q(n3+n6,2)
  - 2.*Q(n1,1)*Q(n2+n4+n5,3)*Q(n3+n6,2)+6.*Q(n1+n2+n4+n5,4)*Q(n3+n6,2)
  + 2.*Q(n2,1)*Q(n4,1)*Q(n5,1)*Q(n1+n3+n6,3)-2.*Q(n2+n4,2)*Q(n5,1)*Q(n1+n3+n6,3)
  - 2.*Q(n4,1)*Q(n2+n5,2)*Q(n1+n3+n6,3)-2.*Q(n2,1)*Q(n4+n5,2)*Q(n1+n3+n6,3)
  + 4.*Q(n2+n4+n5,3)*Q(n1+n3+n6,3)+2.*Q(n1,1)*Q(n4,1)*Q(n5,1)*Q(n2+n3+n6,3)
  - 2.*Q(n1+n4,2)*Q(n5,1)*Q(n2+n3+n6,3)-2.*Q(n4,1)*Q(n1+n5,2)*Q(n2+n3+n6,3)
  - 2.*Q(n1,1)*Q(n4+n5,2)*Q(n2+n3+n6,3)+4.*Q(n1+n4+n5,3)*Q(n2+n3+n6,3)
  - 6.*Q(n4,1)*Q(n5,1)*Q(n1+n2+n3+n6,4)+6.*Q(n4+n5,2)*Q(n1+n2+n3+n6,4)
  - Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)+Q(n1+n2,2)*Q(n3,1)*Q(n5,1)*Q(n4+n6,2)
  + Q(n2,1)*Q(n1+n3,2)*Q(n5,1)*Q(n4+n6,2)+Q(n1,1)*Q(n2+n3,2)*Q(n5,1)*Q(n4+n6,2)
  - 2.*Q(n1+n2+n3,3)*Q(n5,1)*Q(n4+n6,2)+Q(n2,1)*Q(n3,1)*Q(n1+n5,2)*Q(n4+n6,2)
  - Q(n2+n3,2)*Q(n1+n5,2)*Q(n4+n6,2)+Q(n1,1)*Q(n3,1)*Q(n2+n5,2)*Q(n4+n6,2)
  - Q(n1+n3,2)*Q(n2+n5,2)*Q(n4+n6,2)-2.*Q(n3,1)*Q(n1+n2+n5,3)*Q(n4+n6,2)
  + Q(n1,1)*Q(n2,1)*Q(n3+n5,2)*Q(n4+n6,2)-Q(n1+n2,2)*Q(n3+n5,2)*Q(n4+n6,2)
  - 2.*Q(n2,1)*Q(n1+n3+n5,3)*Q(n4+n6,2)-2.*Q(n1,1)*Q(n2+n3+n5,3)*Q(n4+n6,2)
  + 6.*Q(n1+n2+n3+n5,4)*Q(n4+n6,2)+2.*Q(n2,1)*Q(n3,1)*Q(n5,1)*Q(n1+n4+n6,3)
  - 2.*Q(n2+n3,2)*Q(n5,1)*Q(n1+n4+n6,3)-2.*Q(n3,1)*Q(n2+n5,2)*Q(n1+n4+n6,3)
  - 2.*Q(n2,1)*Q(n3+n5,2)*Q(n1+n4+n6,3)+4.*Q(n2+n3+n5,3)*Q(n1+n4+n6,3)
  + 2.*Q(n1,1)*Q(n3,1)*Q(n5,1)*Q(n2+n4+n6,3)-2.*Q(n1+n3,2)*Q(n5,1)*Q(n2+n4+n6,3)
  - 2.*Q(n3,1)*Q(n1+n5,2)*Q(n2+n4+n6,3)-2.*Q(n1,1)*Q(n3+n5,2)*Q(n2+n4+n6,3)
  + 4.*Q(n1+n3+n5,3)*Q(n2+n4+n6,3)-6.*Q(n3,1)*Q(n5,1)*Q(n1+n2+n4+n6,4)
  + 6.*Q(n3+n5,2)*Q(n1+n2+n4+n6,4)+2.*Q(n1,1)*Q(n2,1)*Q(n5,1)*Q(n3+n4+n6,3)
  - 2.*Q(n1+n2,2)*Q(n5,1)*Q(n3+n4+n6,3)-2.*Q(n2,1)*Q(n1+n5,2)*Q(n3+n4+n6,3)
  - 2.*Q(n1,1)*Q(n2+n5,2)*Q(n3+n4+n6,3)+4.*Q(n1+n2+n5,3)*Q(n3+n4+n6,3)
  - 6.*Q(n2,1)*Q(n5,1)*Q(n1+n3+n4+n6,4)+6.*Q(n2+n5,2)*Q(n1+n3+n4+n6,4)
  - 6.*Q(n1,1)*Q(n5,1)*Q(n2+n3+n4+n6,4)+6.*Q(n1+n5,2)*Q(n2+n3+n4+n6,4)
  + 24.*Q(n5,1)*Q(n1+n2+n3+n4+n6,5)-Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)
  + Q(n1+n2,2)*Q(n3,1)*Q(n4,1)*Q(n5+n6,2)+Q(n2,1)*Q(n1+n3,2)*Q(n4,1)*Q(n5+n6,2)
  + Q(n1,1)*Q(n2+n3,2)*Q(n4,1)*Q(n5+n6,2)-2.*Q(n1+n2+n3,3)*Q(n4,1)*Q(n5+n6,2)
  + Q(n2,1)*Q(n3,1)*Q(n1+n4,2)*Q(n5+n6,2)-Q(n2+n3,2)*Q(n1+n4,2)*Q(n5+n6,2)
  + Q(n1,1)*Q(n3,1)*Q(n2+n4,2)*Q(n5+n6,2)-Q(n1+n3,2)*Q(n2+n4,2)*Q(n5+n6,2)
  - 2.*Q(n3,1)*Q(n1+n2+n4,3)*Q(n5+n6,2)+Q(n1,1)*Q(n2,1)*Q(n3+n4,2)*Q(n5+n6,2)
  - Q(n1+n2,2)*Q(n3+n4,2)*Q(n5+n6,2)-2.*Q(n2,1)*Q(n1+n3+n4,3)*Q(n5+n6,2)
  - 2.*Q(n1,1)*Q(n2+n3+n4,3)*Q(n5+n6,2)+6.*Q(n1+n2+n3+n4,4)*Q(n5+n6,2)
  + 2.*Q(n2,1)*Q(n3,1)*Q(n4,1)*Q(n1+n5+n6,3)-2.*Q(n2+n3,2)*Q(n4,1)*Q(n1+n5+n6,3)
  - 2.*Q(n3,1)*Q(n2+n4,2)*Q(n1+n5+n6,3)-2.*Q(n2,1)*Q(n3+n4,2)*Q(n1+n5+n6,3)
  + 4.*Q(n2+n3+n4,3)*Q(n1+n5+n6,3)+2.*Q(n1,1)*Q(n3,1)*Q(n4,1)*Q(n2+n5+n6,3)
  - 2.*Q(n1+n3,2)*Q(n4,1)*Q(n2+n5+n6,3)-2.*Q(n3,1)*Q(n1+n4,2)*Q(n2+n5+n6,3)
  - 2.*Q(n1,1)*Q(n3+n4,2)*Q(n2+n5+n6,3)+4.*Q(n1+n3+n4,3)*Q(n2+n5+n6,3)
  - 6.*Q(n3,1)*Q(n4,1)*Q(n1+n2+n5+n6,4)+6.*Q(n3+n4,2)*Q(n1+n2+n5+n6,4)
  + 2.*Q(n1,1)*Q(n2,1)*Q(n4,1)*Q(n3+n5+n6,3)-2.*Q(n1+n2,2)*Q(n4,1)*Q(n3+n5+n6,3)
  - 2.*Q(n2,1)*Q(n1+n4,2)*Q(n3+n5+n6,3)-2.*Q(n1,1)*Q(n2+n4,2)*Q(n3+n5+n6,3)
  + 4.*Q(n1+n2+n4,3)*Q(n3+n5+n6,3)-6.*Q(n2,1)*Q(n4,1)*Q(n1+n3+n5+n6,4)
  + 6.*Q(n2+n4,2)*Q(n1+n3+n5+n6,4)-6.*Q(n1,1)*Q(n4,1)*Q(n2+n3+n5+n6,4)
  + 6.*Q(n1+n4,2)*Q(n2+n3+n5+n6,4)+24.*Q(n4,1)*Q(n1+n2+n3+n5+n6,5)
  + 2.*Q(n1,1)*Q(n2,1)*Q(n3,1)*Q(n4+n5+n6,3)-2.*Q(n1+n2,2)*Q(n3,1)*Q(n4+n5+n6,3)
  - 2.*Q(n2,1)*Q(n1+n3,2)*Q(n4+n5+n6,3)-2.*Q(n1,1)*Q(n2+n3,2)*Q(n4+n5+n6,3)
  + 4.*Q(n1+n2+n3,3)*Q(n4+n5+n6,3)-6.*Q(n2,1)*Q(n3,1)*Q(n1+n4+n5+n6,4)
  + 6.*Q(n2+n3,2)*Q(n1+n4+n5+n6,4)-6.*Q(n1,1)*Q(n3,1)*Q(n2+n4+n5+n6,4)
  + 6.*Q(n1+n3,2)*Q(n2+n4+n5+n6,4)+24.*Q(n3,1)*Q(n1+n2+n4+n5+n6,5)
  - 6.*Q(n1,1)*Q(n2,1)*Q(n3+n4+n5+n6,4)+6.*Q(n1+n2,2)*Q(n3+n4+n5+n6,4)
  + 24.*Q(n2,1)*Q(n1+n3+n4+n5+n6,5)+24.*Q(n1,1)*Q(n2+n3+n4+n5+n6,5)
  - 120.*Q(n1+n2+n3+n4+n5+n6,6);
  return six;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::Recursion(Int_t n, Int_t* harmonic, Int_t mult /*= 1*/, Int_t skip /*= 0*/) 
{
 // Calculate multi-particle correlators by using recursion (an improved faster version) originally developed by 
 // Kristjan Gulbrandsen (gulbrand@nbi.dk). 

  Int_t nm1 = n-1;
  TComplex c(Q(harmonic[nm1], mult));
  if (nm1 == 0) return c;
  c *= Recursion(nm1, harmonic);
  if (nm1 == skip) return c;

  Int_t multp1 = mult+1;
  Int_t nm2 = n-2;
  Int_t counter1 = 0;
  Int_t hhold = harmonic[counter1];
  harmonic[counter1] = harmonic[nm2];
  harmonic[nm2] = hhold + harmonic[nm1];
  TComplex c2(Recursion(nm1, harmonic, multp1, nm2));
  Int_t counter2 = n-3;
  while (counter2 >= skip) {
    harmonic[nm2] = harmonic[counter1];
    harmonic[counter1] = hhold;
    ++counter1;
    hhold = harmonic[counter1];
    harmonic[counter1] = harmonic[nm2];
    harmonic[nm2] = hhold + harmonic[nm1];
    c2 += Recursion(nm1, harmonic, multp1, counter2);
    --counter2;
  }
  harmonic[nm2] = harmonic[counter1];
  harmonic[counter1] = hhold;

  if (mult == 1) return c-c2;
  return c-Double_t(mult)*c2;

} // TComplex AliFlowAnalysisWithMultiparticleCorrelations::Recursion(Int_t n, Int_t* harmonic, Int_t mult = 1, Int_t skip = 0)

TComplex FlowAnalysisWithQCumulantGenericFramework::P(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n>=0) { return fPvector[n][p][ipt][pid]; }
  return TComplex::Conjugate(fPvector[-n][p][ipt][pid]);
}

TComplex FlowAnalysisWithQCumulantGenericFramework::PGapPos(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n < 0) return TComplex::Conjugate(fPvectorGapPos[-n][p][ipt][pid]);
  else return fPvectorGapPos[n][p][ipt][pid];
}
// ============================================================================
TComplex FlowAnalysisWithQCumulantGenericFramework::PGapNeg(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n < 0) return TComplex::Conjugate(fPvectorGapNeg[-n][p][ipt][pid]);
  else return fPvectorGapNeg[n][p][ipt][pid];
}

TComplex FlowAnalysisWithQCumulantGenericFramework::S(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n>=0) { return fSvector[n][p][ipt][pid]; }
  return TComplex::Conjugate(fSvector[-n][p][ipt][pid]);
}

TComplex FlowAnalysisWithQCumulantGenericFramework::SGapPos(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n < 0) return TComplex::Conjugate(fSvectorGapPos[-n][p][ipt][pid]);
  else return fSvectorGapPos[n][p][ipt][pid];
}
// ============================================================================
TComplex FlowAnalysisWithQCumulantGenericFramework::SGapNeg(const Int_t n, const Int_t p, const Int_t ipt, const Int_t pid) const
{
  if(n < 0) return TComplex::Conjugate(fSvectorGapNeg[-n][p][ipt][pid]);
  else return fSvectorGapNeg[n][p][ipt][pid];
}

TComplex FlowAnalysisWithQCumulantGenericFramework::TwoDiff(const Int_t n1, const Int_t n2, const Int_t ipt, const Int_t pid) const
{
  TComplex twoDiff = P(n1,1,ipt,pid)*Q(n2,1) - S(n1+n2,2,ipt,pid);
  return twoDiff;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::TwoDiffGapPos(const Int_t n1, const Int_t n2, const Int_t ipt, const Int_t pid) const
{
  TComplex twoDiffGapPos = PGapPos(n1,1,ipt,pid)*QGapNeg(n2,1);
  return twoDiffGapPos;
}
// ============================================================================
TComplex FlowAnalysisWithQCumulantGenericFramework::TwoDiffGapNeg(const Int_t n1, const Int_t n2, const Int_t ipt, const Int_t pid) const
{
  TComplex twoDiffGapNeg = PGapNeg(n1,1,ipt,pid)*QGapPos(n2,1);
  return twoDiffGapNeg;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::ThreeDiff(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t ipt, const Int_t pid) const
{
  TComplex threeDiff = P(n1,1,ipt,pid)*Q(n2,1)*Q(n3,1)-S(n1+n2,2,ipt,pid)*Q(n3,1)-S(n1+n3,2,ipt,pid)*Q(n2,1)
 		                 - P(n1,1,ipt,pid)*Q(n2+n3,2)+2.0*S(n1+n2+n3,3,ipt,pid);
  return threeDiff;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::FourDiff(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t ipt, const Int_t pid) const
{
  TComplex fourDiff = P(n1,1,ipt,pid)*Q(n2,1)*Q(n3,1)*Q(n4,1)-S(n1+n2,2,ipt,pid)*Q(n3,1)*Q(n4,1)-Q(n2,1)*S(n1+n3,2,ipt,pid)*Q(n4,1)
                    - P(n1,1,ipt,pid)*Q(n2+n3,2)*Q(n4,1)+2.0*S(n1+n2+n3,3,ipt,pid)*Q(n4,1)-Q(n2,1)*Q(n3,1)*S(n1+n4,2,ipt,pid)
                    + Q(n2+n3,2)*S(n1+n4,2,ipt,pid)-P(n1,1,ipt,pid)*Q(n3,1)*Q(n2+n4,2)+S(n1+n3,2,ipt,pid)*Q(n2+n4,2)
                    + 2.0*Q(n3,1)*S(n1+n2+n4,3,ipt,pid)-P(n1,1,ipt,pid)*Q(n2,1)*Q(n3+n4,2)+S(n1+n2,2,ipt,pid)*Q(n3+n4,2)
                    + 2.0*Q(n2,1)*S(n1+n3+n4,3,ipt,pid)+2.0*P(n1,1,ipt,pid)*Q(n2+n3+n4,3)-6.0*S(n1+n2+n3+n4,4,ipt,pid);
  return fourDiff;
}

TComplex FlowAnalysisWithQCumulantGenericFramework::FourDiffGapPos(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t ipt, const Int_t pid) const
{
  TComplex formula = PGapPos(n1,1,ipt,pid)*QGapPos(n2,1)*QGapNeg(n3,1)*QGapNeg(n4,1)
                      - SGapPos(n1+n2,2,ipt,pid)*QGapNeg(n3,1)*QGapNeg(n4,1)
                      - PGapPos(n1,1,ipt,pid)*QGapPos(n2,1)*QGapNeg(n3+n4,2)
                      + SGapPos(n1+n2,2,ipt,pid)*QGapNeg(n3+n4,2);
  // same as
  // TComplex formula = TwoDiffPos(n1,n2)*TwoNeg(n3,n4);
  return formula;
}
// ============================================================================
TComplex FlowAnalysisWithQCumulantGenericFramework::FourDiffGapNeg(const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t ipt, const Int_t pid) const
{
  TComplex formula = PGapNeg(n1,1,ipt,pid)*QGapNeg(n2,1)*QGapPos(n3,1)*QGapPos(n4,1)
                      - SGapNeg(n1+n2,2,ipt,pid)*QGapPos(n3,1)*QGapPos(n4,1)
                      - PGapNeg(n1,1,ipt,pid)*QGapNeg(n2,1)*QGapPos(n3+n4,2)
                      + SGapNeg(n1+n2,2,ipt,pid)*QGapPos(n3+n4,2);
  // same as
  // TComplex formula = TwoDiffNeg(n1,n2)*TwoPos(n3,n4);
  return formula;
}