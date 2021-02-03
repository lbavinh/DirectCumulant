 // TProfile of multi-particle correlations
struct CCorrelator
{
    TProfile *pCorrelator2EtaGap;
    TProfile *pCorrelator2;
    TProfile *pCorrelator4;

    TProfile2D *pReducedCorrelator2EtaGap[npid];
    TProfile2D *pReducedCorrelator2[npid];
    TProfile2D *pReducedCorrelator4[npid];

    CCorrelator();
    void SaveHist();
};

CCorrelator::CCorrelator()
{
    pCorrelator2EtaGap = new TProfile("pCorrelator2EtaGap", "2nd order correlator with eta-gap, TPC", ncent, 0, ncent); // <<2>> (with eta-gap)
    pCorrelator2EtaGap -> Sumw2();
    pCorrelator2 = new TProfile("pCorrelator2", "2nd order correlator", ncent, 0, ncent);                               // <<2>>
    pCorrelator2 -> Sumw2();
    pCorrelator4 = new TProfile("pCorrelator4", "4th order correlator", ncent, 0, ncent);                               // <<4>>
    pCorrelator4 -> Sumw2();

    for (Int_t i = 0; i < npid; i++)
    {
        pReducedCorrelator2EtaGap[i] = new TProfile2D(Form("pReducedCorrelator2EtaGap_pid%i", i), Form("Reduced 2nd order correlator with eta-gap of %s (TPC", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
        pReducedCorrelator2EtaGap[i] -> Sumw2();
        pReducedCorrelator2[i] = new TProfile2D(Form("pReducedCorrelator2_pid%i", i), Form("Reduced 2nd order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
        pReducedCorrelator2[i] -> Sumw2();
        pReducedCorrelator4[i] = new TProfile2D(Form("pReducedCorrelator4_pid%i", i), Form("Reduced 4th order correlator of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
        pReducedCorrelator4[i] -> Sumw2();
    }  
}

void CCorrelator::SaveHist()
{
    pCorrelator2EtaGap->Write();
    pCorrelator2->Write();
    pCorrelator4->Write();
    for (Int_t id = 0; id < npid; id++)
    {
      pReducedCorrelator2EtaGap[id]->Write();
      pReducedCorrelator2[id]->Write();
      pReducedCorrelator4[id]->Write();
    }
}

// TProfile for covariance calculation of statistical errors of QCumulant
struct CCovCorrelator
{
    TProfile *pCov24;                                                                  // <2>*<4>
    TProfile2D *pCov22Red[npid];                                                       // <2>*<2'>
    TProfile2D *pCov24Red[npid];                                                       // <2>*<4'>
    TProfile2D *pCov42Red[npid];                                                       // <4>*<2'>
    TProfile2D *pCov44Red[npid];                                                       // <4>*<4'>
    TProfile2D *pCov2Red4Red[npid];                                                    // <2'>*<4'>
    TProfile2D *pCov22RedEtaGap[npid];                                                 // <2>*<2'> (with eta-gap)

    CCovCorrelator();
    void SaveHist();

};

CCovCorrelator::CCovCorrelator()
{
    pCov24 = new TProfile("pCov24", "Covariance(<2>,<4>)", ncent, 0, ncent); // <2>*<4>
    pCov24 -> Sumw2();

    for (Int_t i = 0; i < npid; i++)
    {
      pCov22RedEtaGap[i] = new TProfile2D(Form("pCov22RedEtaGap_pid%i", i), Form("Covariance(<2>,<2'>) with eta-gap of %s (TPC)", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov22RedEtaGap[i] -> Sumw2();
      pCov22Red[i] = new TProfile2D(Form("pCov22Red_pid%i", i), Form("Covariance(<2>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov22Red[i] -> Sumw2();
      pCov24Red[i] = new TProfile2D(Form("pCov24Red_pid%i", i), Form("Covariance(<2>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov24Red[i] -> Sumw2();
      pCov42Red[i] = new TProfile2D(Form("pCov42Red_pid%i", i), Form("Covariance(<4>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov42Red[i] -> Sumw2();
      pCov44Red[i] = new TProfile2D(Form("pCov44Red_pid%i", i), Form("Covariance(<4>,<4'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov44Red[i] -> Sumw2();
      pCov2Red4Red[i] = new TProfile2D(Form("pCov2Red4Red_pid%i", i), Form("Covariance(<4'>,<2'>) of %s", pidNames.at(i).Data()), npt, 0, npt, ncent, 0, ncent);
      pCov2Red4Red[i] -> Sumw2();
    }    

}

void CCovCorrelator::SaveHist()
{
  pCov24->Write();
  for (Int_t id = 0; id < npid; id++)
  {
    pCov22RedEtaGap[id]->Write();
    pCov22Red[id]->Write();
    pCov24Red[id]->Write();
    pCov42Red[id]->Write();
    pCov44Red[id]->Write();
    pCov2Red4Red[id]->Write();
  }
}

struct CPhiAngles
{
      Double_t cos4phi, sin4phi, cos2phi, sin2phi;

      void recalc(Double_t phi);
};

void CPhiAngles::recalc(Double_t phi)
{
      cos4phi = TMath::Cos(4. * phi);
      sin4phi = TMath::Sin(4. * phi);
      cos2phi = TMath::Cos(2. * phi);
      sin2phi = TMath::Sin(2. * phi);
}

// 2,4-QC
struct CQC24
{
    Double_t Qx2, Qy2, Qx4, Qy4;
    TComplex Q2, Q4;
    Double_t px2[npt][npid], py2[npt][npid];
    TComplex p2[npt][npid], p4[npt][npid], q2[npt][npid], q4[npt][npid];
    Double_t qx2[npt][npid], qy2[npt][npid], qx4[npt][npid], qy4[npt][npid];
    Double_t M = 0.;
    Double_t mq[npt][npid], mp[npt][npid];
    Double_t redCor22[npt][npid], redCor24[npt][npid];
    Double_t w2, w4;
    Double_t wred2[npt][npid], wred4[npt][npid];
    Double_t cor22, cor24;

    Int_t fCentBin;

    CQC24() { zero(); }
    void zero();
    void setQxQy(const CPhiAngles& phiAngles);
    void setQP(const CPhiAngles& phiAngles, const Int_t ipt, const Double_t charge, const Int_t fId);
    void calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr);

  private:        
    void setQP(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx1);
};

void CQC24::zero()
{
    Qx2 = 0.; Qy2 = 0.; Qx4 = 0.; Qy4 = 0.;
    Q2 = TComplex(0.,0.); Q4 = TComplex(0.,0.);
    // px2[npt][npid] = {{0.}}; py2[npt][npid] = {{0.}};
    // p2[npt][npid] = {{0.}}; p4[npt][npid] = {{0.}}; q2[npt][npid] = {{0.}}; q4[npt][npid] = {{0.}};
    // qx2[npt][npid] = {{0.}}; qy2[npt][npid] = {{0.}}; qx4[npt][npid] = {{0.}}; qy4[npt][npid] = {{0.}};
    M = 0.;
    // mq[npt][npid] = {{0.}}; mp[npt][npid] = {{0.}};
    // redCor22[npt][npid] = {{0.}}; redCor24[npt][npid] = {{0.}};
    w2 = 0.; w4 = 0.;
    // wred2[npt][npid] = {{0.}}; wred4[npt][npid] = {{0.}};
    cor22 = 0.; cor24 = 0.;
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
            p4[ipt][ipid] = TComplex(0., 0.);
            q2[ipt][ipid] = TComplex(0., 0.);
            q4[ipt][ipid] = TComplex(0., 0.);
        }
    }
}

void CQC24::setQxQy(const CPhiAngles& phiAngles)
{
        Qx2 += phiAngles.cos2phi;
        Qy2 += phiAngles.sin2phi;
        Qx4 += phiAngles.cos4phi;
        Qy4 += phiAngles.sin4phi;
        M++;
}

void CQC24::setQP(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx1)
{
        px2[ipt][idx1] += phiAngles.cos2phi;
        py2[ipt][idx1] += phiAngles.sin2phi;
        mp[ipt][idx1]++;

        qx2[ipt][idx1] += phiAngles.cos2phi;
        qy2[ipt][idx1] += phiAngles.sin2phi;
        qx4[ipt][idx1] += phiAngles.cos4phi;
        qy4[ipt][idx1] += phiAngles.sin4phi;
        mq[ipt][idx1]++;
}

void CQC24::setQP(const CPhiAngles& phiAngles, const Int_t ipt, const Double_t charge, const Int_t fId)
{
      if (charge > 0)
      {
          setQP(phiAngles, ipt, 0);
      }
      else if (charge < 0)
      {
          setQP(phiAngles, ipt, 4);
      }
      if (fId > 0)
      {
          setQP(phiAngles, ipt, fId);
      }
}

void CQC24::calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr)
{
    Q2 = TComplex(Qx2, Qy2);
    w2 = M * (M - 1); // w(<2>)
    Q4 = TComplex(Qx4, Qy4);
    w4 = M * (M - 1) * (M - 2) * (M - 3); // w(<4>)
    if (w2 != 0 && w4 != 0)
    {
      cor22 = CalCor22(Q2, M, w2);                   // <2>
      cor24 = CalCor24(Q2, Q4, M, w4);               // <4>
      pCorr->pCorrelator2->Fill(0.5 + fCentBin, cor22, w2); // <<2>>
      pCorr->pCorrelator4->Fill(0.5 + fCentBin, cor24, w4); // <<4>>
      // TProfile for covariance calculation in statistic error
      pCovCorr->pCov24->Fill(0.5 + fCentBin, cor22 * cor24, w2 * w4); // <2>*<4>
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
          pCorr->pReducedCorrelator2[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id], wred2[ipt][id]);
          redCor24[ipt][id] = CalRedCor24(Q2, Q4, p2[ipt][id], q2[ipt][id], q4[ipt][id], M, mp[ipt][id], mq[ipt][id], wred4[ipt][id]); // <4'>
          pCorr->pReducedCorrelator4[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor24[ipt][id], wred4[ipt][id]);                                 // <<4'>>

          // TProfile for covariance calculation in statistic error
          pCovCorr->pCov22Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor22[ipt][id], w2 * wred2[ipt][id]); // <2>*<2'>
          pCovCorr->pCov24Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22 * redCor24[ipt][id], w2 * wred4[ipt][id]);
          pCovCorr->pCov42Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor22[ipt][id], w4 * wred2[ipt][id]);
          pCovCorr->pCov44Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor24 * redCor24[ipt][id], w4 * wred4[ipt][id]);
          pCovCorr->pCov2Red4Red[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22[ipt][id] * redCor24[ipt][id], wred2[ipt][id] * wred4[ipt][id]);
        }
      }
    }                                                                                                                                                                         
}

// 2-QC, eta-gapped
struct CQC2eg
{
    Double_t Qx2Gap[neta], Qy2Gap[neta];
    Double_t px2Gap[neta][npt][npid], py2Gap[neta][npt][npid];
    TComplex Q2Gap[neta], p2Gap[neta][npt][npid];
    Double_t MGap[neta];
    Double_t mpGap[neta][npt][npid];
    Double_t w2Gap;
    Double_t wred2Gap[neta][npt][npid];
    Double_t cor22Gap;
    Double_t redCor22Gap[neta][npt][npid];

    Int_t fCentBin;

    CQC2eg() { zero(); }
    void zero();
    void setQxQy(const CPhiAngles& phiAngles, const Double_t eta);
    void setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Double_t eta, const Double_t charge, const Int_t fId);
    void calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr);

private:
    void setQxQy(const CPhiAngles& phiAngles, const Int_t idx);
    void setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx, const Int_t idx1);
    void setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx, const Double_t charge, const Int_t fId);

};

void CQC2eg::zero()
{
    // Qx2Gap[neta] = {0.}; Qy2Gap[neta] = {0.};
    // px2Gap[neta][npt][npid] = {{{0.}}}; py2Gap[neta][npt][npid] = {{{0.}}};
    // Q2Gap[neta] = {0.}; p2Gap[neta][npt][npid] = {{{0.}}};
    // MGap[neta] = {0};
    // mpGap[neta][npt][npid] = {{{0.}}};
    w2Gap = 0.;
    // wred2Gap[neta][npt][npid] = {{{0.}}};
    cor22Gap = 0.;
    // redCor22Gap[neta][npt][npid] = {{{0.}}};
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

void CQC2eg::setQxQy(const CPhiAngles& phiAngles, const Int_t idx)
{
    Qx2Gap[idx] += phiAngles.cos2phi;
    Qy2Gap[idx] += phiAngles.sin2phi;
    MGap[idx]++;
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx, const Int_t idx1)
{
    px2Gap[idx][ipt][idx1] += phiAngles.cos2phi;
    py2Gap[idx][ipt][idx1] += phiAngles.sin2phi;
    mpGap[idx][ipt][idx1]++;  
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Int_t idx, const Double_t charge, const Int_t fId)
{
      if (charge > 0)
      {
          setPxPy(phiAngles, ipt, idx, 0);
      }
      else if (charge < 0)
      {
          setPxPy(phiAngles, ipt, idx, 4);
      }
      if (fId > 0)
      {
          setPxPy(phiAngles, ipt, idx, fId);
      }
}

void CQC2eg::setQxQy(const CPhiAngles& phiAngles, const Double_t eta)
{
    if (eta < -eta_gap)
    {
        setQxQy(phiAngles, 0);
    }
    else if (eta > eta_gap)
    {
        setQxQy(phiAngles, 1);
    }
}

void CQC2eg::setPxPy(const CPhiAngles& phiAngles, const Int_t ipt, const Double_t eta, const Double_t charge, const Int_t fId)
{
    // Here, we reverse eta index (left TPC: 1, right TPC: 0)
    // in order to correlate p-vector with Q-vector from the oposite TPC sub-event
    if (eta < -eta_gap)
    {   // Left TPC sub-event
        setPxPy(phiAngles, ipt, 1, charge, fId);
        // Here, we reverse eta index in order to correlate p-vector with 
    }
    else if (eta > eta_gap)
    {   // Right TPC sub-event
        setPxPy(phiAngles, ipt, 0, charge, fId);

    }
}

void CQC2eg::calcMPCorr(CCorrelator *pCorr, CCovCorrelator *pCovCorr)
{
     // 2-QC, eta-gapped: multi-particle correlation calculation
    if (MGap[0] != 0 && MGap[1] != 0)
    {
        for (Int_t ieta = 0; ieta < neta; ieta++)
        {
            Q2Gap[ieta] = TComplex(Qx2Gap[ieta], Qy2Gap[ieta]);
        }

        w2Gap = MGap[0] * MGap[1];
        cor22Gap = CalRedCor22(Q2Gap[0], Q2Gap[1], MGap[0], MGap[1], 0., w2Gap); // <2>
        pCorr->pCorrelator2EtaGap->Fill(0.5 + fCentBin, cor22Gap, w2Gap);
      
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
                    pCorr->pReducedCorrelator2EtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, redCor22Gap[ieta][ipt][id], wred2Gap[ieta][ipt][id]);
                    // TProfile for covariance calculation in statistic error
                    pCovCorr->pCov22RedEtaGap[id]->Fill(0.5 + ipt, 0.5 + fCentBin, cor22Gap * redCor22Gap[ieta][ipt][id], w2Gap * wred2Gap[ieta][ipt][id]);
                }
            }
        }
    }
}

