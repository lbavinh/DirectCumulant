#define MULTIPARTICLECORRELATION_CXX
#include "MultiparticleCorrelation.h"

ClassImp(MultiparticleCorrelation);
MultiparticleCorrelation::MultiparticleCorrelation()
{
}

MultiparticleCorrelation::~MultiparticleCorrelation()
{
}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, Int_t &cent)
{ // 2-particle correlations only
  fCentBin = cent;
  cor2 = term(pCor2, fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2Var, Int_t &cent)
{ // 2-particle correlations only
  fCentBin = cent;
  cor2 = term(pCor2, pCor2Var, fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2red, 
                                                   TProfile *const &pCov22prime,
                                                   Int_t &cent, Int_t &pt)
{
  fCentBin = cent;
  fPtBin = pt;
  cor2 = term(pCor2, fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  cor2red = term(pCor2red,fPtBin);
  v22Dif = cor2red.mVal/v22Ref;
  cov22prime = Covariance(pCov22prime,pCor2,pCor2red,fPtBin,fCentBin,fPtBin);
  v22Dife = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2red, 
                                                   TProfile *const &pCor2Var, TProfile *const &pCor2redVar, TProfile *const &pCov22prime,
                                                   Int_t &cent, Int_t &pt)
{
  fCentBin = cent;
  fPtBin = pt;
  cor2 = term(pCor2, pCor2Var, fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  cor2red = term(pCor2red,pCor2redVar,fPtBin);
  v22Dif = cor2red.mVal/v22Ref;
  cov22prime = Covariance(pCov22prime,pCor2,pCor2red,fPtBin,fCentBin,fPtBin);
  v22Dife = sqrt(0.25*pow(cor2.mVal,-3)*(pow(cor2red.mVal,2)*cor2.mMSE
                            + 4*pow(cor2.mVal,2)*cor2red.mMSE - 4*cor2.mVal*cor2red.mVal*cov22prime));
}

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red,
                                                   TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const & pCov24prime,
                                                   TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                                                   Int_t &cent, Int_t &pt)
{ // 2- and 4-particle correlations of POI (statistical uncertainties calculated according to Ante's thesis)
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
    pow((4.*pow(cor2.mVal,2.)*cor4red.mVal-6.*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(2.*sqrt(cor2.mVal)*cor2red.mVal*pow(2*pow(cor2.mVal,2)-cor4.mVal,7./4.)), 2.) * cor2.mMSE
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

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red,
                                                   TProfile *const &pCor2Var, TProfile *const &pCor4Var, TProfile *const &pCor2redVar, TProfile *const &pCor4redVar,
                                                   TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const & pCov24prime,
                                                   TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                                                   Int_t &cent, Int_t &pt)
{ // 2- and 4-particle correlations of POI (statistical uncertainties calculated according to Cochran)
  fCentBin = cent;
  fPtBin = pt;
  cor2 = term(pCor2,pCor2Var,fCentBin);
  cor4 = term(pCor4,pCor4Var,fCentBin);
  v22Ref = sqrt(cor2.mVal);
  v22Refe = sqrt(1./(4.*cor2.mVal)*cor2.mMSE);
  cov24 = Covariance(pCov24,pCor2,pCor4,fCentBin,fCentBin,fCentBin);
  v24Ref = pow(2*pow(cor2.mVal,2)-cor4.mVal,0.25);
  v24Refe = sqrt( 1./pow(v24Ref,6)*(cor2.mVal*cor2.mVal*cor2.mMSE+1./16*cor4.mMSE-0.5*cor2.mVal*cov24) );

  cor2red = term(pCor2red,pCor2redVar,fPtBin);
  cor4red = term(pCor4red,pCor4redVar,fPtBin);

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
    pow((4.*pow(cor2.mVal,2.)*cor4red.mVal-6.*cor2.mVal*cor2red.mVal*cor4.mVal+cor4.mVal*cor4red.mVal)/(2.*sqrt(cor2.mVal)*cor2red.mVal*pow(2*pow(cor2.mVal,2)-cor4.mVal,7./4.)), 2.) * cor2.mMSE
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
{ // 2- and 4-particle correlations of RFP (statistical uncertainties calculated according to Ante's thesis)
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

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, 
                                                   TProfile *const &pCor2Var, TProfile *const &pCor4Var, 
                                                   TProfile *const &pCov24, Int_t &cent)
{ // 2- and 4-particle correlations of RFP (statistical uncertainties calculated according to Cochran)
  fCentBin = cent;
  cor2 = term(pCor2, pCor2Var, fCentBin);
  cor4 = term(pCor4, pCor4Var, fCentBin);
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

MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, 
                                                   TProfile *const &pCor2Var, TProfile *const &pCor4Var,
                                                   TProfile *const &pCor2Gap, TProfile *const &pCor2GapVar,
                                                   TProfile *const &pCov24, TProfile *const &pCov2Gap4, TProfile *const &pCov2Gap2, Int_t &cent)
{ // for ratio v2{4}/v2{2,2-sub}
  fCentBin = cent;
  // MultiparticleCorrelation *cor2gap = new MultiparticleCorrelation(pCor2Gap, fCentBin);
  // MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(pCor2, pCor4, pCov24, fCentBin);

  MultiparticleCorrelation *cor2gap = new MultiparticleCorrelation(pCor2Gap, pCor2GapVar, fCentBin);
  MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(pCor2, pCor4, pCor2Var, pCor4Var, pCov24, fCentBin);
  v22Ref = cor2gap->GetV22Ref();
  v22Refe = cor2gap->GetV22RefErr();
  v24Ref = standardQC->GetV24Ref();
  v24Refe = standardQC->GetV24RefErr();
  Double_t cor2MSEGap = cor2gap->GetCor2MSERef();
  Double_t cor2MSE = standardQC->GetCor2MSERef();
  Double_t cor4MSE = standardQC->GetCor4MSERef();
  Double_t cor2MeanGap = cor2gap->GetCor2Ref();
  Double_t cor2Mean = standardQC->GetCor2Ref();
  Double_t cor4Mean = standardQC->GetCor4Ref();

  cov24 = Covariance(pCov24,pCor2,pCor4,fCentBin,fCentBin,fCentBin);
  Double_t cov2Gap2 = Covariance(pCov2Gap2,pCor2Gap,pCor2,fCentBin,fCentBin,fCentBin);
  Double_t cov2Gap4 = Covariance(pCov2Gap4,pCor2Gap,pCor4,fCentBin,fCentBin,fCentBin);
  ratioV24OverV22Ref = v24Ref / v22Ref;
  // ratioV24OverV22Refe = sqrt(
  //   pow(4. * pow(v24Ref, 3.) * v22Ref, -2.) * (2.*cor2MSE + cor4MSE - 4.*cov24) +
  //   pow(0.5 * v24Ref / pow(v22Ref, 3.), 2.) * cor2MSEGap +
  //   1./(4. * pow(v24Ref, 2.) * pow(v22Ref, 4.)) * (cov2Gap4 - 2.*cov2Gap2)
  //   );
  ratioV24OverV22Refe = sqrt(
     pow( cor2Mean/(v22Ref*pow(v24Ref,3.)), 2.)*cor2MSE
    +pow( 1./(4.*v22Ref*pow(v24Ref,3.)), 2.)*cor4MSE
    +pow( v24Ref/(2.*pow(v22Ref,3.)), 2.)*cor2MSEGap
    -2.*( cor2Mean/(4.*cor2MeanGap*pow(v24Ref,6.)) )*cov24
    -2.*( cor2Mean/(2.*cor2MeanGap*cor2MeanGap*pow(v24Ref,2.)) )*cov2Gap2
    +2.*( 1./(8.*cor2MeanGap*cor2MeanGap*pow(v24Ref,2.)) )*cov2Gap4
  );  
}

  MultiparticleCorrelation::MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red, TProfile *const &pCor2Gap, TProfile *const &pCor2redGap,
                                                     TProfile *const &pCor2Var, TProfile *const &pCor4Var, TProfile *const &pCor2redVar, TProfile *const &pCor4redVar, TProfile *const &pCor2GapVar, TProfile *const &pCor2redGapVar,
                                                     TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const &pCov24prime,
                                                     TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                                                     TProfile *const &pCov2Gap2primeGap, TProfile *const &pCov2Gap2, TProfile *const &pCov2Gap4,
                                                     TProfile *const &pCov2primeGap2, TProfile *const &pCov2primeGap4,
                                                     TProfile *const &pCov2Gap2prime, TProfile *const &pCov2Gap4prime,
                                                     TProfile *const &pCov2primeGap2prime, TProfile *const &pCov2primeGap4prime,
                                                     Int_t &cent, Int_t &pt)
{ // for ratio v2{4}/v2{2,2-sub}
  fCentBin = cent;
  fPtBin = pt;
  MultiparticleCorrelation *standardQC = new MultiparticleCorrelation(pCor2, pCor4, pCor2red, pCor4red, 
                                                                      pCor2Var, pCor4Var, pCor2redVar, pCor4redVar,
                                                                      pCov22prime, pCov24, pCov24prime,
                                                                      pCov42prime, pCov2prime4prime, pCov44prime,
                                                                      fCentBin, fPtBin);
  MultiparticleCorrelation *cor2gap = new MultiparticleCorrelation(pCor2Gap, pCor2redGap, 
                                                                   pCor2GapVar, pCor2redGapVar,
                                                                   pCov2Gap2primeGap, fCentBin, fPtBin); 
  
  v22Ref  = cor2gap->GetV22Ref();
  v22Refe = cor2gap->GetV22RefErr();
  v24Ref  = standardQC->GetV24Ref();
  v24Refe = standardQC->GetV24RefErr();
  v22Dif  = cor2gap->GetV22Dif();
  v22Dife = cor2gap->GetV22DifErr();
  v24Dif  = standardQC->GetV24Dif();
  v24Dife = standardQC->GetV24DifErr();


  Double_t cor2MSEGap = cor2gap->GetCor2MSERef();
  Double_t cor2MSE = standardQC->GetCor2MSERef();
  Double_t cor4MSE = standardQC->GetCor4MSERef();
  Double_t cor2MeanGap = cor2gap->GetCor2Ref();
  Double_t cor2Mean = standardQC->GetCor2Ref();
  Double_t cor4Mean = standardQC->GetCor4Ref();

  Double_t cor2redMSEGap = cor2gap->GetCor2MSEDif();
  Double_t cor2redMSE = standardQC->GetCor2MSEDif();
  Double_t cor4redMSE = standardQC->GetCor4MSEDif();
  Double_t cor2redMeanGap = cor2gap->GetCor2Dif();
  Double_t cor2redMean = standardQC->GetCor2Dif();
  Double_t cor4redMean = standardQC->GetCor4Dif();


  cov24 = Covariance(pCov24,pCor2,pCor4,fCentBin,fCentBin,fCentBin);
  Double_t cov2Gap4 = Covariance(pCov2Gap4,pCor2Gap,pCor4,fCentBin,fCentBin,fCentBin);
  Double_t cov2Gap2 = Covariance(pCov2Gap2,pCor2Gap,pCor2,fCentBin,fCentBin,fCentBin);
  cov22prime = Covariance(pCov22prime,pCor2,pCor2red,fPtBin,fCentBin,fPtBin);
  cov24prime = Covariance(pCov24prime,pCor2,pCor4red,fPtBin,fCentBin,fPtBin);
  cov42prime = Covariance(pCov42prime,pCor4,pCor2red,fPtBin,fCentBin,fPtBin);
  cov44prime = Covariance(pCov44prime,pCor4,pCor4red,fPtBin,fCentBin,fPtBin);
  cov2prime4prime = Covariance(pCov2prime4prime,pCor2red,pCor4red,fPtBin,fPtBin,fPtBin);
  Double_t cov2Gap2primeGap = Covariance(pCov2Gap2primeGap,pCor2Gap,pCor2redGap,fPtBin,fCentBin,fPtBin);
  Double_t cov2primeGap2 = Covariance(pCov2primeGap2,pCor2redGap,pCor2,fPtBin,fCentBin,fPtBin);
  Double_t cov2primeGap4 = Covariance(pCov2primeGap4,pCor2redGap,pCor4,fPtBin,fCentBin,fPtBin);
  Double_t cov2Gap2prime = Covariance(pCov2Gap2prime,pCor2Gap,pCor2red,fPtBin,fCentBin,fPtBin);
  Double_t cov2Gap4prime = Covariance(pCov2Gap4prime,pCor2Gap,pCor4red,fPtBin,fCentBin,fPtBin);
  Double_t cov2primeGap2prime = Covariance(pCov2primeGap2prime,pCor2redGap,pCor2red,fPtBin,fCentBin,fPtBin);
  Double_t cov2primeGap4prime = Covariance(pCov2primeGap4prime,pCor2redGap,pCor4red,fPtBin,fCentBin,fPtBin);
  
  ratioV24OverV22Ref = v24Ref / v22Ref;
  ratioV24OverV22Dif = v24Dif / v22Dif;
  ratioV24OverV22Refe = sqrt(
    pow(4. * pow(v24Ref, 3.) * v22Ref, -2.) * (2.*cor2MSE + cor4MSE - 4.*cov24) +
    pow(0.5 * v24Ref / pow(v22Ref, 3.), 2.) * cor2MSEGap +
    1./(4. * pow(v24Ref, 2.) * pow(v22Ref, 4.)) * (cov2Gap4 - 2.*cov2Gap2));  
  ratioV24OverV22Dife = sqrt(
    pow( ( v22Ref * (2.*cor2Mean*cor2Mean*cor2redMean-3.*cor2Mean*cor4redMean+2.*cor2redMean*cor4Mean) )/(cor2redMeanGap * pow(v24Ref,7.)) , 2. ) * cor2MSE
  + pow( ( 2.*v22Ref*cor2Mean )/(cor2redMeanGap * pow(v24Ref,3.)) , 2. ) * cor2redMSE
  + pow( ( 3.*v22Ref*(2.*cor2Mean*cor2redMean-cor4redMean) )/(4. * cor2redMeanGap * pow(v24Ref,7.)) , 2. ) * cor4MSE
  + pow( v22Ref/(cor2redMeanGap * pow(v24Ref,3.)) , 2. ) * cor4redMSE
  + pow( (  cor4redMean-2.*cor2Mean*cor2redMean )/(2. * v22Ref * cor2redMeanGap * pow(v24Ref,3.)) , 2. ) * cor2MSEGap
  + pow( ( v22Ref*(cor4redMean-2.*cor2Mean*cor2redMean) )/(pow(cor2redMeanGap,2.) * pow(v24Ref,3.)) , 2. ) * cor2redMSEGap
  - 2.*( (4.*pow(cor2Mean,3.)*cor2redMean*cor2MeanGap-6.*pow(cor2Mean,2.)*cor4redMean*cor2MeanGap+4.*cor2Mean*cor2redMean*cor4Mean*cor2MeanGap)/(pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov22prime
  + 2.*( (3.*cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean)*(2.*cor2Mean*cor2Mean*cor2redMean-3.*cor2Mean*cor4redMean+2.*cor2redMean*cor4Mean))/(4.*pow(cor2redMeanGap,2.)*pow(v24Ref,14.)) )*cov24
  + 2.*( (cor2MeanGap*(2.*cor2Mean*cor2Mean*cor2redMean-3.*cor2Mean*cor4redMean+2.*cor2redMean*cor4Mean))/(pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov24prime
  + 2.*( ((cor4redMean-2.*cor2Mean*cor2redMean)*(2.*cor2Mean*cor2Mean*cor2redMean-3.*cor2Mean*cor4redMean+2.*cor2redMean*cor4Mean))/(2.*pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov2Gap2
  - 2.*( (cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean)*(2.*cor2Mean*cor2Mean*cor2redMean-3.*cor2Mean*cor4redMean+2.*cor2redMean*cor4Mean))/(pow(cor2redMeanGap,3.)*pow(v24Ref,10.)) )*cov2primeGap2
  - 2.*( (3.*cor2Mean*cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean))/(2.*pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov42prime
  - 2.*( (2.*cor2Mean*cor2MeanGap)/(pow(cor2redMeanGap,2.)*pow(v24Ref,6.)) )*cov2prime4prime
  - 2.*( (cor2Mean*(cor4redMean-2.*cor2Mean*cor2redMean))/(pow(cor2redMeanGap,2.)*pow(v24Ref,6.)) )*cov2Gap2prime
  + 2.*( (2.*cor2Mean*cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean))/(pow(cor2redMeanGap,3.)*pow(v24Ref,6.)) )*cov2primeGap2prime
  + 2.*( (3.*cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean))/(4.*pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov44prime
  + 2.*( (3.*pow(cor4redMean-2.*cor2Mean*cor2redMean,2.))/(8.*pow(cor2redMeanGap,2.)*pow(v24Ref,10.)) )*cov2Gap4
  - 2.*( (3.*cor2MeanGap*pow(cor4redMean-2.*cor2Mean*cor2redMean,2.))/(4.*pow(cor2redMeanGap,3.)*pow(v24Ref,10.)) )*cov2primeGap4
  + 2.*( (cor4redMean-2.*cor2Mean*cor2redMean)/(2.*pow(cor2redMeanGap,2.)*pow(v24Ref,6.)) )*cov2Gap4prime
  - 2.*( (cor2MeanGap*(cor4redMean-2.*cor2Mean*cor2redMean))/(pow(cor2redMeanGap,3.)*pow(v24Ref,6.)) )*cov2primeGap4prime
  - 2.*( pow(cor4redMean-2.*cor2Mean*cor2redMean,2.)/(2.*pow(cor2redMeanGap,3.)*pow(v24Ref,6.)) )*cov2Gap2primeGap
  );

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