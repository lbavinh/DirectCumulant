/**
 * Elliptic flow v2 measurements using Q-Cumulant
 * proposed by Ante Bilandzic in https://arxiv.org/abs/1010.0233
 * coded by Vinh Ba Luong (lbavinh@gmail.com)
 * 25/11/2020
 */
#include <FlowAnalysisWithQCumulant.h>
ClassImp(FlowAnalysisWithQCumulant);
FlowAnalysisWithQCumulant::FlowAnalysisWithQCumulant() :
  fHarmonic(2),
  fEtaGap(0),
  pCorrelator2(nullptr),
  pCorrelator4(nullptr),
  pCov24(nullptr),
  pCorrelator2EtaGap(nullptr),
  pCorrelator4EtaGap(nullptr),
  pCov24EtaGap(nullptr)  
{
  for (Int_t id = 0; id < npidQC; id++){
    pReducedCorrelator2[id] = nullptr;
    pReducedCorrelator4[id] = nullptr;
    pCov22Red[id] = nullptr;
    pCov24Red[id] = nullptr;
    pCov42Red[id] = nullptr;
    pCov44Red[id] = nullptr;
    pCov2Red4Red[id] = nullptr;

    pReducedCorrelator2EtaGap[id] = nullptr;
    pReducedCorrelator4EtaGap[id] = nullptr;
    pCov22RedEtaGap[id] = nullptr;
    pCov24RedEtaGap[id] = nullptr;
    pCov42RedEtaGap[id] = nullptr;
    pCov44RedEtaGap[id] = nullptr;
    pCov2Red4RedEtaGap[id] = nullptr;

  }
  Zero();
}

FlowAnalysisWithQCumulant::~FlowAnalysisWithQCumulant()
{
}

void FlowAnalysisWithQCumulant::Init()
{
  pCorrelator2 = new TProfile("pCorrelator2", "2nd order correlator", ncent, 0, ncent); // <<2>>
  pCorrelator2->Sumw2();
  pCorrelator4 = new TProfile("pCorrelator4", "4th order correlator", ncent, 0, ncent); // <<4>>
  pCorrelator4->Sumw2();
  pCorrelator2EtaGap = new TProfile("pCorrelator2EtaGap", "2nd order correlator 2-sub, TPC", ncent, 0, ncent); // <<2>> (2-sub)
  pCorrelator2EtaGap->Sumw2();
  pCorrelator4EtaGap = new TProfile("pCorrelator4EtaGap", "4th order correlator 2-sub, TPC", ncent, 0, ncent); // <<4>> (2-sub)
  pCorrelator4EtaGap->Sumw2();  
  pCov24 = new TProfile("pCov24", "Covariance(<2>,<4>)", ncent, 0, ncent); // <2>*<4>
  pCov24->Sumw2();
  pCov24EtaGap = new TProfile("pCov24EtaGap", "Covariance(<2>,<4>) 2-sub method", ncent, 0, ncent); // <2>*<4>
  pCov24EtaGap->Sumw2();
  for (Int_t i = 0; i < npidQC; i++)
  {
    pReducedCorrelator2[i] = new TProfile2D(Form("pReducedCorrelator2_pid%i", i), Form("Reduced 2nd order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator2[i]->Sumw2();
    pReducedCorrelator4[i] = new TProfile2D(Form("pReducedCorrelator4_pid%i", i), Form("Reduced 4th order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator4[i]->Sumw2();
    pCov22Red[i] = new TProfile2D(Form("pCov22Red_pid%i", i), Form("Covariance(<2>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov22Red[i]->Sumw2();
    pCov24Red[i] = new TProfile2D(Form("pCov24Red_pid%i", i), Form("Covariance(<2>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov24Red[i]->Sumw2();
    pCov42Red[i] = new TProfile2D(Form("pCov42Red_pid%i", i), Form("Covariance(<4>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov42Red[i]->Sumw2();
    pCov44Red[i] = new TProfile2D(Form("pCov44Red_pid%i", i), Form("Covariance(<4>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov44Red[i]->Sumw2();
    pCov2Red4Red[i] = new TProfile2D(Form("pCov2Red4Red_pid%i", i), Form("Covariance(<4'>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov2Red4Red[i]->Sumw2();

    pReducedCorrelator2EtaGap[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_pid%i", i), Form("Reduced 2nd order correlator 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator2EtaGap[i]->Sumw2();
    pReducedCorrelator4EtaGap[i] = new TProfile2D(Form("pReducedCorrelator4EtaGap_pid%i", i), Form("Reduced 4th order correlator 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pReducedCorrelator4EtaGap[i]->Sumw2();
    pCov22RedEtaGap[i] = new TProfile2D(Form("pCov22RedEtaGap_pid%i", i), Form("Covariance(<2>,<2'>) 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov22RedEtaGap[i]->Sumw2();
    pCov24RedEtaGap[i] = new TProfile2D(Form("pCov24RedEtaGap_pid%i", i), Form("Covariance(<2>,<4'>) 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov24RedEtaGap[i]->Sumw2();
    pCov42RedEtaGap[i] = new TProfile2D(Form("pCov42RedEtaGap_pid%i", i), Form("Covariance(<4>,<2'>) 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov42RedEtaGap[i]->Sumw2();
    pCov44RedEtaGap[i] = new TProfile2D(Form("pCov44RedEtaGap_pid%i", i), Form("Covariance(<4>,<4'>) 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov44RedEtaGap[i]->Sumw2();
    pCov2Red4RedEtaGap[i] = new TProfile2D(Form("pCov2Red4RedEtaGap_pid%i", i), Form("Covariance(<4'>,<2'>) 2-sub of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
    pCov2Red4RedEtaGap[i]->Sumw2();
  }
}

void FlowAnalysisWithQCumulant::Zero()
{
  Q2x = 0.;
  Q2y = 0.;
  Q4x = 0.;
  Q4y = 0.;
  Q2 = TComplex(0., 0.);
  Q4 = TComplex(0., 0.);
  M = 0.;
  w2 = 0.;
  w4 = 0.;
  cor22 = 0.;
  cor24 = 0.;
  for (Int_t ipt = 0; ipt < npt; ipt++)
  {
    for (Int_t ipid = 0; ipid < npidQC; ipid++)
    {
      p2x[ipt][ipid] = 0.;
      p2y[ipt][ipid] = 0.;
      q2x[ipt][ipid] = 0.;
      q2y[ipt][ipid] = 0.;
      q4x[ipt][ipid] = 0.;
      q4y[ipt][ipid] = 0.;

      mq[ipt][ipid] = 0.;
      mp[ipt][ipid] = 0.;
      redCor22[ipt][ipid] = 0.;
      redCor24[ipt][ipid] = 0.;
      wred2[ipt][ipid] = 0.;
      wred4[ipt][ipid] = 0.;
      p2[ipt][ipid] = TComplex(0., 0.);
      q2[ipt][ipid] = TComplex(0., 0.);
      q4[ipt][ipid] = TComplex(0., 0.);
    }
  }

  // 2,4-QC with 2-sub

  w2Gap = 0.;
  w4Gap = 0.;
  cor22Gap = 0.;
  cor24Gap = 0.;
  for (Int_t ieta = 0; ieta < neta; ieta++)
  {
    Q2xGap[ieta] = 0.;
    Q2yGap[ieta] = 0.;
    Q4xGap[ieta] = 0.;
    Q4yGap[ieta] = 0.;
    MGap[ieta] = 0.;
    Q2Gap[ieta] = TComplex(0., 0.);
    Q4Gap[ieta] = TComplex(0., 0.);
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t ipid = 0; ipid < npidQC; ipid++)
      {
        p2xGap[ieta][ipt][ipid] = 0;
        p2yGap[ieta][ipt][ipid] = 0;
        p2Gap[ieta][ipt][ipid] = TComplex(0., 0.);
        mpGap[ieta][ipt][ipid] = 0;
        q2xGap[ieta][ipt][ipid] = 0;
        q2yGap[ieta][ipt][ipid] = 0;
        q2Gap[ieta][ipt][ipid] = TComplex(0., 0.);
        q4xGap[ieta][ipt][ipid] = 0;
        q4yGap[ieta][ipt][ipid] = 0;
        q4Gap[ieta][ipt][ipid] = TComplex(0., 0.);        
        mqGap[ieta][ipt][ipid] = 0;        
        wred2Gap[ieta][ipt][ipid] = 0;
        wred4Gap[ieta][ipt][ipid] = 0;
        redCor22Gap[ieta][ipt][ipid] = 0;
        redCor24Gap[ieta][ipt][ipid] = 0;
      }
    }
  }
}

void FlowAnalysisWithQCumulant::ProcessFirstTrackLoopRP(const Double_t &eta, const Double_t &phi)
{
  Double_t cos2nphi = TMath::Cos(2.*fHarmonic*phi);
  Double_t sin2nphi = TMath::Sin(2.*fHarmonic*phi);
  Double_t cosnphi = TMath::Cos(fHarmonic*phi);
  Double_t sinnphi = TMath::Sin(fHarmonic*phi);

  // 2,4-QC
  Q2x += cosnphi;
  Q2y += sinnphi;
  Q4x += cos2nphi;
  Q4y += sin2nphi;
  M++;

  // 2,4-QC, 2-sub
  if (eta < -fEtaGap)
  { // Left TPC subevent selection
    Q2xGap[0] += cosnphi;
    Q2yGap[0] += sinnphi;
    Q4xGap[0] += cos2nphi;
    Q4yGap[0] += sin2nphi;
    MGap[0]++;
  }
  if (eta > fEtaGap)
  { // Right TPC subevent selection
    Q2xGap[1] += cosnphi;
    Q2yGap[1] += sinnphi;
    Q4xGap[1] += cos2nphi;
    Q4yGap[1] += sin2nphi;
    MGap[1]++;
  }

}

void FlowAnalysisWithQCumulant::ProcessFirstTrackLoopPOI(const Int_t &ipt, const Double_t &eta, const Double_t &phi, const Int_t &pid, const Double_t &charge)
{
  Double_t cos2nphi = TMath::Cos(2.*fHarmonic*phi);
  Double_t sin2nphi = TMath::Sin(2.*fHarmonic*phi);
  Double_t cosnphi = TMath::Cos(fHarmonic*phi);
  Double_t sinnphi = TMath::Sin(fHarmonic*phi);

  // Differential Flow of 2,4-QC
  if (charge > 0)
  {
    p2x[ipt][0] += cosnphi;
    p2y[ipt][0] += sinnphi;
    mp[ipt][0]++;

    q2x[ipt][0] += cosnphi;
    q2y[ipt][0] += sinnphi;
    q4x[ipt][0] += cos2nphi;
    q4y[ipt][0] += sin2nphi;
    mq[ipt][0]++;
  }
  if (charge < 0)
  {
    p2x[ipt][4] += cosnphi;
    p2y[ipt][4] += sinnphi;
    mp[ipt][4]++;

    q2x[ipt][4] += cosnphi;
    q2y[ipt][4] += sinnphi;
    q4x[ipt][4] += cos2nphi;
    q4y[ipt][4] += sin2nphi;
    mq[ipt][4]++;
  }
  if (pid > 0)
  {
    p2x[ipt][pid] += cosnphi;
    p2y[ipt][pid] += sinnphi;
    mp[ipt][pid]++;

    q2x[ipt][pid] += cosnphi;
    q2y[ipt][pid] += sinnphi;
    q4x[ipt][pid] += cos2nphi;
    q4y[ipt][pid] += sin2nphi;
    mq[ipt][pid]++;
  }

  // Differential Flow of 2-QC, 2-sub
  // Note: Here, I reverse index of sub-event in order to correlate Particle of Interest in one half hemisphere
  // with Reference Particles in the other one.
  if (eta < -fEtaGap)
  { // Left TPC subevent selection
    if (charge > 0)
    { // Inclusive positively charged hadrons
      p2xGap[1][ipt][0] += cosnphi;
      p2yGap[1][ipt][0] += sinnphi;
      mpGap[1][ipt][0]++;
      q2xGap[1][ipt][0] += cosnphi;
      q2yGap[1][ipt][0] += sinnphi;
      q4xGap[1][ipt][0] += cos2nphi;
      q4yGap[1][ipt][0] += sin2nphi;
      mqGap[1][ipt][0]++;
    }
    if (charge < 0)
    { // Inclusive negatively charged hadrons
      p2xGap[1][ipt][4] += cosnphi;
      p2yGap[1][ipt][4] += sinnphi;
      mpGap[1][ipt][4]++;
      q2xGap[1][ipt][4] += cosnphi;
      q2yGap[1][ipt][4] += sinnphi;
      q4xGap[1][ipt][4] += cos2nphi;
      q4yGap[1][ipt][4] += sin2nphi;
      mqGap[1][ipt][4]++;
    }
    if (pid > 0)
    { // Identified charged hadrons
      p2xGap[1][ipt][pid] += cosnphi;
      p2yGap[1][ipt][pid] += sinnphi;
      mpGap[1][ipt][pid]++;
      q2xGap[1][ipt][pid] += cosnphi;
      q2yGap[1][ipt][pid] += sinnphi;
      q4xGap[1][ipt][pid] += cos2nphi;
      q4yGap[1][ipt][pid] += sin2nphi;
      mqGap[1][ipt][pid]++;      
    }
  } // end of Left TPC subevent selection
  if (eta > fEtaGap)
  { // Right TPC subevent selection
    if (charge > 0)
    { // Inclusive positively charged hadrons
      p2xGap[0][ipt][0] += cosnphi;
      p2yGap[0][ipt][0] += sinnphi;
      mpGap[0][ipt][0]++;
      q2xGap[0][ipt][0] += cosnphi;
      q2yGap[0][ipt][0] += sinnphi;
      q4xGap[0][ipt][0] += cos2nphi;
      q4yGap[0][ipt][0] += sin2nphi;
      mqGap[0][ipt][0]++;
    }
    if (charge < 0)
    { // Inclusive negatively charged hadrons
      p2xGap[0][ipt][4] += cosnphi;
      p2yGap[0][ipt][4] += sinnphi;
      mpGap[0][ipt][4]++;
      q2xGap[0][ipt][4] += cosnphi;
      q2yGap[0][ipt][4] += sinnphi;
      q4xGap[0][ipt][4] += cos2nphi;
      q4yGap[0][ipt][4] += sin2nphi;
      mqGap[0][ipt][4]++;
    }
    if (pid > 0)
    { // Identified charged hadrons
      p2xGap[0][ipt][pid] += cosnphi;
      p2yGap[0][ipt][pid] += sinnphi;
      mpGap[0][ipt][pid]++;
      q2xGap[0][ipt][pid] += cosnphi;
      q2yGap[0][ipt][pid] += sinnphi;
      q4xGap[0][ipt][pid] += cos2nphi;
      q4yGap[0][ipt][pid] += sin2nphi;
      mqGap[0][ipt][pid]++;
    }
  } // end of Right TPC subevent selection
}

void FlowAnalysisWithQCumulant::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  // 2,QC & 4,QC without eta-gap
  Q2 = TComplex(Q2x, Q2y);
  w2 = M * (M - 1); // w(<2>)
  Q4 = TComplex(Q4x, Q4y);
  w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
  if (w2 != 0 && w4 != 0)
  {
    cor22 = CalCor22(Q2, M, w2);                // <2>
    cor24 = CalCor24(Q2, Q4, M, w4);            // <4>
    pCorrelator2->Fill(0.5 + icent, cor22, w2); // <<2>>
    pCorrelator4->Fill(0.5 + icent, cor24, w4); // <<4>>
    // TProfile for covariance calculation in statistic error
    pCov24->Fill(0.5 + icent, cor22 * cor24, w2 * w4); // <2>*<4>
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t id = 0; id < npidQC; id++)
      {
        wred2[ipt][id] = mp[ipt][id] * M - mq[ipt][id];                           // w(<2'>)
        wred4[ipt][id] = (mp[ipt][id] * M - 3 * mq[ipt][id]) * (M - 1) * (M - 2); // w(<4'>)
        if (mp[ipt][id] == 0 || wred2[ipt][id] == 0 || wred4[ipt][id] == 0)
          continue;
        p2[ipt][id] = TComplex(p2x[ipt][id], p2y[ipt][id]);
        q2[ipt][id] = TComplex(q2x[ipt][id], q2y[ipt][id]);
        q4[ipt][id] = TComplex(q4x[ipt][id], q4y[ipt][id]);
        redCor22[ipt][id] = CalRedCor22(Q2, p2[ipt][id], M, mp[ipt][id], mq[ipt][id], wred2[ipt][id]); // <2'>
        pReducedCorrelator2[id]->Fill(0.5 + ipt, 0.5 + icent, redCor22[ipt][id], wred2[ipt][id]);
        redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]); // <4'>
        pReducedCorrelator4[id]->Fill(0.5 + ipt, 0.5 + icent, redCor24[ipt][id], wred4[ipt][id]);                                 // <<4'>>
        // TProfile for covariance calculation in statistic error
        pCov22Red[id]->Fill(0.5 + ipt, 0.5 + icent, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]); // <2>*<2'>
        pCov24Red[id]->Fill(0.5 + ipt, 0.5 + icent, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
        pCov42Red[id]->Fill(0.5 + ipt, 0.5 + icent, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
        pCov44Red[id]->Fill(0.5 + ipt, 0.5 + icent, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
        pCov2Red4Red[id]->Fill(0.5 + ipt, 0.5 + icent, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
      }
    }
  }

  // 2,4-QC, 2-sub
  if (MGap[0] >= 2 && MGap[1] >= 2)
  {
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      Q2Gap[ieta] = TComplex(Q2xGap[ieta], Q2yGap[ieta]);
      Q4Gap[ieta] = TComplex(Q4xGap[ieta], Q4yGap[ieta]);
    }
    w2Gap = MGap[0]*MGap[1];
    w4Gap = MGap[0]*(MGap[0]-1)*MGap[1]*(MGap[1]-1);
    cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap);              // <2>
    cor24Gap = CalCor24TwoSub(Q2Gap[0], Q4Gap[0], Q2Gap[1], Q4Gap[1], MGap[0], MGap[1]);  // <4>  
    pCorrelator2EtaGap->Fill(0.5 + icent, cor22Gap, w2Gap);
    pCorrelator4EtaGap->Fill(0.5 + icent, cor24Gap, w4Gap);
    pCov24EtaGap->Fill(0.5 + icent, cor22Gap * cor24Gap, w2Gap * w4Gap);           // <2>*<4>
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      for (Int_t ipt = 0; ipt < npt; ipt++)
      { // <2'>
        for (Int_t id = 0; id < npidQC; id++)
        {
          if (mpGap[ieta][ipt][id] == 0)
            continue;
          wred2Gap[ieta][ipt][id] = mpGap[ieta][ipt][id] * MGap[ieta];
          if (ieta==0) wred4Gap[ieta][ipt][id] = (mpGap[ieta][ipt][id]*MGap[ieta+1] - mqGap[ieta][ipt][id]) * MGap[ieta]*(MGap[ieta]-1);
          if (ieta==1) wred4Gap[ieta][ipt][id] = (mpGap[ieta][ipt][id]*MGap[ieta-1] - mqGap[ieta][ipt][id]) * MGap[ieta]*(MGap[ieta]-1);
          if (wred2Gap[ieta][ipt][id]==0 || wred4Gap[ieta][ipt][id]==0) continue;
          p2Gap[ieta][ipt][id] = TComplex(p2xGap[ieta][ipt][id], p2yGap[ieta][ipt][id]);
          q2Gap[ieta][ipt][id] = TComplex(q2xGap[ieta][ipt][id], q2yGap[ieta][ipt][id]);
          q4Gap[ieta][ipt][id] = TComplex(q4xGap[ieta][ipt][id], q4yGap[ieta][ipt][id]);
          redCor22Gap[ieta][ipt][id] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt][id], MGap[ieta], mpGap[ieta][ipt][id], 0., wred2Gap[ieta][ipt][id]); // <2'>
          if (ieta==0) redCor24Gap[ieta][ipt][id] = CalRedCor24TwoSub(Q2Gap[ieta+1], Q2Gap[ieta],
                                                                  Q4Gap[ieta], p2Gap[ieta][ipt][id],
                                                                  q2Gap[ieta][ipt][id], q4Gap[ieta][ipt][id],
                                                                  MGap[ieta+1], MGap[ieta],
                                                                  mpGap[ieta][ipt][id], mqGap[ieta][ipt][id]);                                                        // <4'>
          if (ieta==1) redCor24Gap[ieta][ipt][id] = CalRedCor24TwoSub(Q2Gap[ieta-1], Q2Gap[ieta],
                                                                  Q4Gap[ieta], p2Gap[ieta][ipt][id],
                                                                  q2Gap[ieta][ipt][id], q4Gap[ieta][ipt][id],
                                                                  MGap[ieta-1], MGap[ieta],
                                                                  mpGap[ieta][ipt][id], mqGap[ieta][ipt][id]);            
          pReducedCorrelator2EtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);
          pReducedCorrelator4EtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, redCor24Gap[ieta][ipt][id], wred4Gap[ieta][ipt][id]); 
          // TProfile for covariance calculation in statistic error
          pCov22RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, cor22Gap * redCor22Gap[ieta][ipt][id], w2Gap * wred2Gap[ieta][ipt][id]);                                          // <2>*<2'>
          pCov24RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, cor22Gap * redCor24Gap[ieta][ipt][id], w2Gap * wred4Gap[ieta][ipt][id]);                                          // <2>*<4'>
          pCov42RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, cor24Gap * redCor22Gap[ieta][ipt][id], w4Gap * wred2Gap[ieta][ipt][id]);                                          // <4>*<2'>  
          pCov44RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, cor24Gap * redCor24Gap[ieta][ipt][id], w4Gap * wred4Gap[ieta][ipt][id]);                                          // <4>*<4'>
          pCov2Red4RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + icent, redCor22Gap[ieta][ipt][id]*redCor24Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]*wred4Gap[ieta][ipt][id]);       // <2'>*<4'>
        }
      }
    }
  }
}

void FlowAnalysisWithQCumulant::SaveHist()
{

  pCorrelator2->Write();
  pCorrelator4->Write();
  pCorrelator2EtaGap->Write();
  pCorrelator4EtaGap->Write();
  pCov24->Write();
  pCov24EtaGap->Write();
  for (Int_t id = 0; id < npidQC; id++)
  {
    pReducedCorrelator2[id]->Write();
    pReducedCorrelator4[id]->Write();
    pCov22Red[id]->Write();
    pCov24Red[id]->Write();
    pCov42Red[id]->Write();
    pCov44Red[id]->Write();
    pCov2Red4Red[id]->Write();
    pReducedCorrelator2EtaGap[id]->Write();
    pReducedCorrelator4EtaGap[id]->Write();
    pCov22RedEtaGap[id]->Write();
    pCov24RedEtaGap[id]->Write();
    pCov42RedEtaGap[id]->Write();
    pCov44RedEtaGap[id]->Write();
    pCov2Red4RedEtaGap[id]->Write();
  }
}

void FlowAnalysisWithQCumulant::SaveHist(TDirectoryFile *const &outputDir)
{
  
  outputDir->Add(pCorrelator2);
  outputDir->Add(pCorrelator4);
  outputDir->Add(pCorrelator2EtaGap);
  outputDir->Add(pCorrelator4EtaGap);
  outputDir->Add(pCov24);
  outputDir->Add(pCov24EtaGap);
  for (Int_t id = 0; id < npidQC; id++)
  {
    outputDir->Add(pReducedCorrelator2[id]);
    outputDir->Add(pReducedCorrelator4[id]);
    outputDir->Add(pCov22Red[id]);
    outputDir->Add(pCov24Red[id]);
    outputDir->Add(pCov42Red[id]);
    outputDir->Add(pCov44Red[id]);
    outputDir->Add(pCov2Red4Red[id]);
    outputDir->Add(pReducedCorrelator2EtaGap[id]);
    outputDir->Add(pReducedCorrelator4EtaGap[id]);
    outputDir->Add(pCov22RedEtaGap[id]);
    outputDir->Add(pCov24RedEtaGap[id]);
    outputDir->Add(pCov42RedEtaGap[id]);
    outputDir->Add(pCov44RedEtaGap[id]);
    outputDir->Add(pCov2Red4RedEtaGap[id]);
  }
  outputDir->Write();
}
TComplex FlowAnalysisWithQCumulant::Qstar(const TComplex &Q)
{
  TComplex QStar = TComplex::Conjugate(Q);
  return QStar;
}

Double_t FlowAnalysisWithQCumulant::CalCor22(const TComplex &Q2, const Double_t &M, const Double_t &w2)
{
  // single-event average 2-particle azimuthal correlation <2>
  Double_t Q2Square = Q2.Rho2();
  Double_t coor22 = Q2Square - M;
  return coor22 / w2;
}

Double_t FlowAnalysisWithQCumulant::CalCor24(const TComplex &Q2, const TComplex &Q4, const Double_t &M, const Double_t &w4)
{
  // single-event average 4-particle azimuthal correlation <4>

  TComplex Q2Star = Qstar(Q2);
  TComplex Q4Star = Qstar(Q4);

  Double_t Q2Square = Q2.Rho2();
  Double_t Q4Square = Q4.Rho2();
  Double_t ReQQQ = (Q4 * Q2Star * Q2Star).Re();

  Double_t coor24 = (Q2Square * Q2Square + Q4Square - 2 * ReQQQ - 4 * (M - 2) * Q2Square + 2 * M * (M - 3));

  return coor24 / w4;
}

Double_t FlowAnalysisWithQCumulant::CalRedCor22(const TComplex &Q2, const TComplex &p2, const Double_t &M, const Double_t &mp,
                                              const Double_t &mq, const Double_t &wred2)
{

  // Calculate the average reduced single-event 2-particle correlations
  TComplex Q2Star = TComplex::Conjugate(Q2);
  Double_t coor22 = (p2 * Q2Star - mq).Re();

  return coor22 / wred2;
}

Double_t FlowAnalysisWithQCumulant::CalRedCor24(const TComplex &Q2, const TComplex &Q4, const TComplex &p2, const TComplex &q2,
                                              const TComplex &q4, const Double_t &M, const Double_t &mp, const Double_t &mq, const Double_t &wred4)
{

  // Calculate the average reduced single-event 2-particle correlations
  TComplex Q2Star = TComplex::Conjugate(Q2);
  TComplex Q4Star = TComplex::Conjugate(Q4);
  TComplex q2Star = TComplex::Conjugate(q2);
  Double_t Q2Square = Q2.Rho2();
  TComplex coorc = p2 * Q2 * Q2Star * Q2Star - q4 * Q2Star * Q2Star - p2 * Q2 * Q4Star - 2.0 * M * p2 * Q2Star - 2.0 * mq * Q2Square + 7.0 * q2 * Q2Star - Q2 * q2Star + q4 * Q4Star + 2.0 * p2 * Q2Star + 2.0 * mq * M - 6.0 * mq;
  Double_t coor24 = coorc.Re();
  return coor24 / wred4;
}
Double_t FlowAnalysisWithQCumulant::CalCor24TwoSub(const TComplex &Q2a, const TComplex &Q4a, 
                                                 const TComplex &Q2b, const TComplex &Q4b,
                                                 const Double_t &Ma, const Double_t &Mb)
{
  Double_t dNumerator = ((Q2a*Q2a - Q4a) * TComplex::Conjugate(Q2b*Q2b - Q4b)).Re();
  Double_t dDenominator = Ma * (Ma-1) * Mb * (Mb-1);
  if (dDenominator != 0) { return dNumerator/dDenominator; }
  else 
  { 
    cerr << "In FlowAnalysisWithQCumulant::CalCor24TwoSub, dDenominator=0" << endl;
    return 999;
  }
}

Double_t FlowAnalysisWithQCumulant::CalRedCor24TwoSub(const TComplex &Q2a, // const TComplex &Q4a, 
                         const TComplex &Q2b, const TComplex &Q4b,
                         const TComplex &p2a, const TComplex &q2a, 
                         const TComplex &q4a,
                         const Double_t &Ma, const Double_t &Mb,
                         const Double_t &mpa, const Double_t &mqa)
{
  Double_t dNumerator = ( p2a*Q2a*Qstar(Q2b)*Qstar(Q2b) - q4a*Qstar(Q2b)*Qstar(Q2b) -p2a*Q2a*Qstar(Q4b) + q4a*Qstar(Q4b) ).Re();
  Double_t dDenominator = (mpa*Ma-mqa)*Mb*(Mb-1);
  if (dDenominator != 0) { return dNumerator/dDenominator; }
  else 
  { 
    cerr << "In FlowAnalysisWithQCumulant::CalRedCor24TwoSub, dDenominator=0" << endl;
    return 999;
  }
}