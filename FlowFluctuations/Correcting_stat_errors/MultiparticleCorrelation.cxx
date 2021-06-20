#define MULTIPARTICLECORRELATION_CXX
#include "MultiparticleCorrelation.h"

ClassImp(MultiparticleCorrelation);
MultiparticleCorrelation::MultiparticleCorrelation()
{
}

Double_t MultiparticleCorrelation::Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY, Int_t binXY=0, Int_t binX=0, Int_t binY=0)
{
  Double_t mSumWXY = hcovXY->GetBinEntries(binXY+1);
  Double_t sumWX = hX->GetBinEntries(binX+1);
  Double_t sumWY = hY->GetBinEntries(binY+1);

  Double_t meanXY = hcovXY -> GetBinContent(binXY+1);
  Double_t meanX = hX -> GetBinContent(binX+1);
  Double_t meanY = hY -> GetBinContent(binY+1);
  Double_t mVal = (meanXY-meanX*meanY)/(sumWX*sumWY/mSumWXY-1.); // Cov(x,y)/(sumWX*sumWY/sumWXY)
  return mVal;  
}


MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red,
                                                   TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const & pCov24prime,
                                                   TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                                                   Int_t &cent, Int_t &pt)
{
  fCentBin = cent;
  fPtBin = pt;
  cor2 = term(pCor2,fCentBin);
  cor4 = term(pCor4,fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  cov24 = Covariance(pCov24,pCor2,pCor4,fCentBin,fCentBin,fCentBin);
  v24Ref = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
  v24Refe = sqrt( 1./pow(v24Ref,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );

  cor2red = term(pCor2red,fPtBin);
  cor4red = term(pCor4red,fPtBin);

  v22Dif = cor2red.mVal/v22Ref;
  cov22prime = Covariance(pCov22prime,pCor2,pCor2red,fPtBin,fCentBin,fPtBin);
  v22Dife = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));

        
  cov24prime = Covariance(pCov24prime,pCor2,pCor4red,fPtBin,fCentBin,fPtBin);
  cov42prime = Covariance(pCov42prime,pCor4,pCor2red,fPtBin,fCentBin,fPtBin);
  cov44prime = Covariance(pCov44prime,pCor4,pCor4red,fPtBin,fCentBin,fPtBin);
  cov2prime4prime = Covariance(pCov2prime4prime,pCor2red,pCor4red,fPtBin,fPtBin,fPtBin);
  v24Dif = (2.*cor2.mVal*cor2red.mVal-cor4red.mVal)*pow(v24Ref,-3);
  v24Dife = sqrt( pow(v24Ref,-14)
            * (pow(2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal,2.)
            * cor2.mMSE
            + 9./16*pow(2.*cor2.mVal*cor2red.mVal-cor4red.mVal,2.)*cor4.mMSE
            + 4*pow(cor2.mVal,2)*pow(v24Ref,8)*cor2red.mMSE
            + pow(v24Ref,8)*cor4red.mMSE
            - 1.5*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24
            - 4*cor2.mVal*pow(v24Ref,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov22prime
            + 2*pow(v24Ref,4)
            * (2*cor2.mVal*cor2.mVal*cor2red.mVal-3*cor2.mVal*cor4red.mVal+2*cor4.mVal*cor2red.mVal)
            * cov24prime
            + 3*cor2.mVal*pow(v24Ref,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov42prime
            - 1.5*pow(v24Ref,4)*(2*cor2.mVal*cor2red.mVal-cor4red.mVal)
            * cov44prime
            - 4*cor2.mVal*pow(v24Ref,8)*cov2prime4prime));
  
  ratioV24OverV22Dif = v24Dif / v22Dif;
  ratioV24OverV22Dife = sqrt(
    pow((4.*pow(cor2.mVal, 2.)-6*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(2.*sqrt(cor2.mVal)*cor2red.mVal*pow(2*pow(cor2.mVal,2)-cor4.mVal,7./4.)), 2.) * cor2.mMSE
  + pow((sqrt(cor2.mVal)*cor4red.mVal)/(pow(cor2red.mVal,2.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,3./4.)), 2.) * cor2red.mMSE
  + pow((3.*sqrt(cor2.mVal)*(cor4red.mVal-2.*cor2.mVal*cor2red.mVal))/(4.*cor2red.mVal*pow(2*pow(cor2.mVal,2)-cor4.mVal,7./4.)), 2.) * cor4.mMSE
  + pow(sqrt(cor2.mVal)/(cor2red.mVal*pow(2*pow(cor2.mVal,2)-cor4.mVal,3./4.)), 2.) * cor4red.mMSE
  + cor4red.mVal*(4.*pow(cor2.mVal,2.)*cor4red.mVal-6.*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(pow(cor2red.mVal, 3.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,5./2.)) * cov22prime
  - 3.*(cor4red.mVal-2.*cor2.mVal*cor2red.mVal)*(4.*pow(cor2.mVal,2.)*cor4red.mVal-6.*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(4.*pow(cor2red.mVal,2.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,7./2.)) * cov24
  - (4.*pow(cor2.mVal,2.)*cor4red.mVal-6.*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(pow(cor2red.mVal,2.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,5./2.)) * cov24prime
  - 3.*cor2.mVal*cor4red.mVal*(cor4red.mVal-2.*cor2.mVal*cor2red.mVal)/(2.*pow(cor2red.mVal,3.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,5./2.)) * cov42prime
  - 2*cor2.mVal*cor4red.mVal/(pow(cor2red.mVal,3.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,3./2.)) * cov2prime4prime
  + 3.*cor2.mVal*(cor4red.mVal-2.*cor2.mVal*cor2red.mVal)/(2.*pow(cor2red.mVal,2.)*pow(2*pow(cor2.mVal,2)-cor4.mVal,5./2.)) * cov44prime
  );

}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCov24, Int_t &cent)
{
  fCentBin = cent;
  cor2 = term(pCor2,fCentBin);
  cor4 = term(pCor4,fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  cov24 = Covariance(pCov24,pCor2,pCor4,fCentBin,fCentBin,fCentBin);
  v24Ref = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
  v24Refe = sqrt( 1./pow(v24Ref,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );

  ratioV24OverV22Ref = v24Ref / v22Ref;
  ratioV24OverV22Refe = sqrt( pow( cor4.mVal/(2.*pow(cor2.mVal, 3.)*pow( 2 - cor4.mVal/pow(cor2.mVal, 2.), 0.75)), 2.) * cor2.mMSE
                            + pow( 1.       /(4.*pow(cor2.mVal, 2.)*pow( 2 - cor4.mVal/pow(cor2.mVal, 2.), 0.75)), 2.) * cor4.mMSE
                            - 2.*cor4.mVal/(8.*pow(cor2.mVal, 5.) * pow( 2 - cor4.mVal/pow(cor2.mVal, 2.), 9./16.)) * cov24);

}

MultiparticleCorrelation::~MultiparticleCorrelation()
{
}

