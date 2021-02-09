#include <FlowAnalysisWithQCumulant.h>
ClassImp(FlowAnalysisWithQCumulant);
FlowAnalysisWithQCumulant::FlowAnalysisWithQCumulant() : fEtaGap(0)
{
  Zero();
}

FlowAnalysisWithQCumulant::~FlowAnalysisWithQCumulant()
{
}

void FlowAnalysisWithQCumulant::Init()
{
  for (Int_t icent = 0; icent < ncent; icent++)
  { // loop over centrality classes
    hv22[icent] = new TProfile(Form("hv22_%i", icent), Form("hv22_%i", icent), 1, 0., 1.);
    hv24[icent] = new TProfile(Form("hv24_%i", icent), Form("hv24_%i", icent), 1, 0., 1.);
    hcov24[icent] = new TProfile(Form("hcov24_%i", icent), Form("hcov24_%i", icent), 1, 0., 1.);
    hv22Gap[icent] = new TProfile(Form("hv22Gap_%i", icent), Form("hv22Gap_%i", icent), 1, 0., 1.);
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
        hcov22primeGap[icent][ipt][id] = new TProfile(Form("hcov22primeGap_%i_%i_%i", icent, ipt, id), Form("hcov22primeGap_%i_%i_%i", icent, ipt, id), 1, 0., 1.);
      } // end of loop over pt bin
    }
  } // end of loop over centrality classes
}

void FlowAnalysisWithQCumulant::Zero()
{
  Qx2 = 0.;
  Qy2 = 0.;
  Qx4 = 0.;
  Qy4 = 0.;
  Q2 = TComplex(0., 0.);
  Q4 = TComplex(0., 0.);
  M = 0.;
  w2 = 0.;
  w4 = 0.;
  cor22 = 0.;
  cor24 = 0.;
  for (Int_t ipt = 0; ipt < npt; ipt++)
  {
    for (Int_t ipid = 0; ipid < npid; ipid++)
    {
      px2[ipt][ipid] = 0.;
      py2[ipt][ipid] = 0.;
      qx2[ipt][ipid] = 0.;
      qy2[ipt][ipid] = 0.;
      qx4[ipt][ipid] = 0.;
      qy4[ipt][ipid] = 0.;

      mq[ipt][ipid] = 0.;
      mp[ipt][ipid] = 0.;
      redCor22[ipt][ipid] = 0.;
      redCor24[ipt][ipid] = 0.;
      wred2[ipt][ipid] = 0.;
      wred4[ipt][ipid] = 0.;
      p2[ipt][ipid] = TComplex(0., 0.);
      // p4[ipt][ipid] = TComplex(0., 0.);
      q2[ipt][ipid] = TComplex(0., 0.);
      q4[ipt][ipid] = TComplex(0., 0.);
    }
  }

  // 2,QC with eta-gap

  w2Gap = 0.;
  cor22Gap = 0.;
  for (Int_t ieta = 0; ieta < neta; ieta++)
  {
    Qx2Gap[ieta] = 0.;
    Qy2Gap[ieta] = 0.;
    MGap[ieta] = 0.;
    Q2Gap[ieta] = TComplex(0., 0.);
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t ipid = 0; ipid < npid; ipid++)
      {
        px2Gap[ieta][ipt][ipid] = 0;
        py2Gap[ieta][ipt][ipid] = 0;
        mpGap[ieta][ipt][ipid] = 0;
        wred2Gap[ieta][ipt][ipid] = 0;
        redCor22Gap[ieta][ipt][ipid] = 0;
        p2Gap[ieta][ipt][ipid] = TComplex(0., 0.);
      }
    }
  }
}

void FlowAnalysisWithQCumulant::ProcessFirstTrackLoopRP(const double &eta, const double &phi)
{
  Double_t cos4phi = TMath::Cos(4. * phi);
  Double_t sin4phi = TMath::Sin(4. * phi);
  Double_t cos2phi = TMath::Cos(2. * phi);
  Double_t sin2phi = TMath::Sin(2. * phi);

  // 2,4-QC
  Qx2 += cos2phi;
  Qy2 += sin2phi;
  Qx4 += cos4phi;
  Qy4 += sin4phi;
  M++;

  // 2-QC, eta-gapped
  if (eta < -fEtaGap)
  { // Left TPC subevent selection
    Qx2Gap[0] += cos2phi;
    Qy2Gap[0] += sin2phi;
    MGap[0]++;
  }
  if (eta > fEtaGap)
  { // Right TPC subevent selection
    Qx2Gap[1] += cos2phi;
    Qy2Gap[1] += sin2phi;
    MGap[1]++;
  }
}

void FlowAnalysisWithQCumulant::ProcessFirstTrackLoopPOI(const Int_t &ipt, const double &eta, const double &phi, const Int_t &pid, const double &charge)
{
  Double_t cos4phi = TMath::Cos(4. * phi);
  Double_t sin4phi = TMath::Sin(4. * phi);
  Double_t cos2phi = TMath::Cos(2. * phi);
  Double_t sin2phi = TMath::Sin(2. * phi);

  // Differential Flow of 2,4-QC
  if (charge > 0)
  {
    px2[ipt][0] += cos2phi;
    py2[ipt][0] += sin2phi;
    mp[ipt][0]++;

    qx2[ipt][0] += cos2phi;
    qy2[ipt][0] += sin2phi;
    qx4[ipt][0] += cos4phi;
    qy4[ipt][0] += sin4phi;
    mq[ipt][0]++;
  }
  if (charge < 0)
  {
    px2[ipt][4] += cos2phi;
    py2[ipt][4] += sin2phi;
    mp[ipt][4]++;

    qx2[ipt][4] += cos2phi;
    qy2[ipt][4] += sin2phi;
    qx4[ipt][4] += cos4phi;
    qy4[ipt][4] += sin4phi;
    mq[ipt][4]++;
  }
  if (pid > 0)
  {
    px2[ipt][pid] += cos2phi;
    py2[ipt][pid] += sin2phi;
    mp[ipt][pid]++;

    qx2[ipt][pid] += cos2phi;
    qy2[ipt][pid] += sin2phi;
    qx4[ipt][pid] += cos4phi;
    qy4[ipt][pid] += sin4phi;
    mq[ipt][pid]++;
  }

  // Differential Flow of 2-QC, eta-gapped
  if (eta < -fEtaGap)
  { // Left TPC subevent selection
    if (charge > 0)
    { // Inclusive positively charged hadrons
      px2Gap[1][ipt][0] += cos2phi;
      py2Gap[1][ipt][0] += sin2phi;
      mpGap[1][ipt][0]++;
    }
    if (charge < 0)
    { // Inclusive negatively charged hadrons
      px2Gap[1][ipt][4] += cos2phi;
      py2Gap[1][ipt][4] += sin2phi;
      mpGap[1][ipt][4]++;
    }
    if (pid > 0)
    { // Identified charged hadrons
      px2Gap[1][ipt][pid] += cos2phi;
      py2Gap[1][ipt][pid] += sin2phi;
      mpGap[1][ipt][pid]++;
    }
  } // end of Left TPC subevent selection
  if (eta > fEtaGap)
  { // Right TPC subevent selection
    if (charge > 0)
    { // Inclusive positively charged hadrons
      px2Gap[0][ipt][0] += cos2phi;
      py2Gap[0][ipt][0] += sin2phi;
      mpGap[0][ipt][0]++;
    }
    if (charge < 0)
    { // Inclusive negatively charged hadrons
      px2Gap[0][ipt][4] += cos2phi;
      py2Gap[0][ipt][4] += sin2phi;
      mpGap[0][ipt][4]++;
    }
    if (pid > 0)
    { // Identified charged hadrons
      px2Gap[0][ipt][pid] += cos2phi;
      py2Gap[0][ipt][pid] += sin2phi;
      mpGap[0][ipt][pid]++;
    }
  } // end of Right TPC subevent selection
}

void FlowAnalysisWithQCumulant::ProcessEventAfterFirstTrackLoop(const Int_t &icent)
{
  // 2,QC & 4,QC without eta-gap
  Q2 = TComplex(Qx2, Qy2);
  w2 = M * (M - 1); // w(<2>)
  Q4 = TComplex(Qx4, Qy4);
  w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
  if (w2 != 0 && w4 != 0)
  {
    cor22 = CalCor22(Q2, M, w2);       // <2>
    cor24 = CalCor24(Q2, Q4, M, w4);   // <4>
    hv22[icent]->Fill(0.5, cor22, w2); // <<2>>
    hv24[icent]->Fill(0.5, cor24, w4); // <<4>>
    // TProfile for covariance calculation in statistic error
    hcov24[icent]->Fill(0.5, cor22 * cor24, w2 * w4); // <2>*<4>
    for (Int_t ipt = 0; ipt < npt; ipt++)
    {
      for (Int_t id = 0; id < npid; id++)
      {
        wred2[ipt][id] = mp[ipt][id] * M - mq[ipt][id];                           // w(<2'>)
        wred4[ipt][id] = (mp[ipt][id] * M - 3 * mq[ipt][id]) * (M - 1) * (M - 2); // w(<4'>)
        if (mp[ipt][id] == 0 || wred2[ipt][id] == 0 || wred4[ipt][id] == 0)
          continue;
        p2[ipt][id] = TComplex(px2[ipt][id], py2[ipt][id]);
        q2[ipt][id] = TComplex(qx2[ipt][id], qy2[ipt][id]);
        q4[ipt][id] = TComplex(qx4[ipt][id], qy4[ipt][id]);
        redCor22[ipt][id] = CalRedCor22(Q2, p2[ipt][id], M, mp[ipt][id], mq[ipt][id], wred2[ipt][id]); // <2'>
        hv22pt[icent][ipt][id]->Fill(0.5, redCor22[ipt][id], wred2[ipt][id]);
        redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]); // <4'>
        hv24pt[icent][ipt][id]->Fill(0.5, redCor24[ipt][id], wred4[ipt][id]);
        // TProfile for covariance calculation in statistic error
        hcov22prime[icent][ipt][id]->Fill(0.5, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]); // <2>*<2'>
        hcov24prime[icent][ipt][id]->Fill(0.5, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
        hcov42prime[icent][ipt][id]->Fill(0.5, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
        hcov44prime[icent][ipt][id]->Fill(0.5, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
        hcov2prime4prime[icent][ipt][id]->Fill(0.5, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
        hcounter[icent][ipt][id]->Fill(0.5, 1, mp[ipt][id]);
      }
    }
  }

  // 2-QC, eta-gapped: multi-particle correlation calculation
  if (MGap[0] != 0 && MGap[1] != 0)
  {
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
    }
    w2Gap = MGap[0] * MGap[1];
    cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap); // <2>
    // pCorrelator2EtaGap->Fill(0.5 + icent, cor22Gap, w2Gap);
    hv22Gap[icent]->Fill(0.5, cor22Gap, w2Gap);
    for (Int_t ieta = 0; ieta < neta; ieta++)
    {
      for (Int_t ipt = 0; ipt < npt; ipt++)
      { // <2'>
        for (Int_t id = 0; id < npid; id++)
        {
          if (mpGap[ieta][ipt][id] == 0)
            continue;
          p2Gap[ieta][ipt][id] = TComplex(px2Gap[ieta][ipt][id], py2Gap[ieta][ipt][id]);
          wred2Gap[ieta][ipt][id] = mpGap[ieta][ipt][id] * MGap[ieta];
          redCor22Gap[ieta][ipt][id] = CalRedCor22(Q2Gap[ieta], p2Gap[ieta][ipt][id], MGap[ieta], mpGap[ieta][ipt][id], 0., wred2Gap[ieta][ipt][id]); // <2'>
          hv22ptGap[icent][ipt][id]->Fill(0.5, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);                                                  // <<2'>>
          hcounter[icent][ipt][id]->Fill(1.5, 1, mpGap[ieta][ipt][id]);
          // TProfile for covariance calculation in statistic error
          hcov22primeGap[icent][ipt][id]->Fill(0.5, cor22Gap * redCor22Gap[ieta][ipt][id], w2Gap * wred2Gap[ieta][ipt][id]); // <2>*<2'>
        }
      }
    }
  }
}

void FlowAnalysisWithQCumulant::SaveHist()
{
  for (int icent=0; icent<ncent; icent++){ // loop over centrality classes
    hv22[icent]->Write();
    hv24[icent]->Write();
    hcov24[icent]->Write();
    hv22Gap[icent]->Write();
    for(int ipt=0; ipt<npt; ipt++){ // loop over pt bin
      for (int id=0;id<npid;id++){
        hv22pt[icent][ipt][id]->Write();
        hv24pt[icent][ipt][id]->Write();
        hcov22prime[icent][ipt][id]->Write();
        hcov24prime[icent][ipt][id]->Write();
        hcov42prime[icent][ipt][id]->Write();
        hcov44prime[icent][ipt][id]->Write();
        hcov2prime4prime[icent][ipt][id]->Write();
        hcov22primeGap[icent][ipt][id]->Write();
        hv22ptGap[icent][ipt][id]->Write();
      }
    } // end of loop over pt bin
  } // end of loop over centrality classes
}

TComplex FlowAnalysisWithQCumulant::Qstar(const TComplex &Q)
{
  TComplex QStar = TComplex::Conjugate(Q);
  return QStar;
}

double FlowAnalysisWithQCumulant::CalCor22(const TComplex &Q2, const double &M, const double &w2)
{
  // single-event average 2-particle azimuthal correlation <2>
  double Q2Square = Q2.Rho2();
  double coor22 = Q2Square - M;
  return coor22 / w2;
}

double FlowAnalysisWithQCumulant::CalCor24(const TComplex &Q2, const TComplex &Q4, const double &M, const double &w4)
{
  // single-event average 4-particle azimuthal correlation <4>

  TComplex Q2Star = Qstar(Q2);
  TComplex Q4Star = Qstar(Q4);

  double Q2Square = Q2.Rho2();
  double Q4Square = Q4.Rho2();
  double ReQQQ = (Q4 * Q2Star * Q2Star).Re();

  double coor24 = (Q2Square * Q2Square + Q4Square - 2 * ReQQQ - 4 * (M - 2) * Q2Square + 2 * M * (M - 3));

  return coor24 / w4;
}

double FlowAnalysisWithQCumulant::CalRedCor22(const TComplex &Q2, const TComplex &p2, const double &M, const double &mp,
                                              const double &mq, const double &wred2)
{

  // Calculate the average reduced single-event 2-particle correlations
  TComplex Q2Star = TComplex::Conjugate(Q2);
  double coor22 = (p2 * Q2Star - mq).Re();

  return coor22 / wred2;
}

double FlowAnalysisWithQCumulant::CalRedCor24(const TComplex &Q2, const TComplex &Q4, const TComplex &p2, const TComplex &q2,
                                              const TComplex &q4, const double &M, const double &mp, const double &mq, const double &wred4)
{

  // Calculate the average reduced single-event 2-particle correlations
  TComplex Q2Star = TComplex::Conjugate(Q2);
  TComplex Q4Star = TComplex::Conjugate(Q4);
  TComplex q2Star = TComplex::Conjugate(q2);
  double Q2Square = Q2.Rho2();
  TComplex coorc = p2 * Q2 * Q2Star * Q2Star - q4 * Q2Star * Q2Star - p2 * Q2 * Q4Star - 2.0 * M * p2 * Q2Star - 2.0 * mq * Q2Square + 7.0 * q2 * Q2Star - Q2 * q2Star + q4 * Q4Star + 2.0 * p2 * Q2Star + 2.0 * mq * M - 6.0 * mq;
  double coor24 = coorc.Re();
  return coor24 / wred4;
}