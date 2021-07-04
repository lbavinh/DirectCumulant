#define MULTIPARTICLECORRELATION_H
#include <TProfile.h>
#include <TMath.h>
struct term{ // structure for "Mean squared error of MEAN" calculation, using unbiased estimator for the root of variance
  term(){
    mVal = 0;
    mMSE = 0;
  }
  term(TProfile *const &pr, Int_t bin=0){
    // Eq. (15) http://arxiv.org/abs/2104.00588
    Double_t Neff = pr -> GetBinEffectiveEntries(bin+1);
    mVal = pr -> GetBinContent(bin+1);
    pr -> SetErrorOption("s");
    Double_t stdevW = pr -> GetBinError(bin+1);
    Double_t S2 = stdevW*stdevW/(1-1./Neff);
    mMSE = S2/Neff;

    // Eq. (17) http://arxiv.org/abs/2104.00588
  };
  term(TProfile *const &pr1, TProfile *const &pr2, Int_t bin=0)
  {
    Double_t Neff = pr1 -> GetBinEffectiveEntries(bin+1);
    Double_t N = pr1 -> GetEntries();
    mVal = pr1 -> GetBinContent(bin+1);
    pr2 -> SetErrorOption("s");
    Double_t stdevW = pr2 -> GetBinError(bin+1);
    mMSE = N/(N-1.)*stdevW*stdevW/Neff;
    // mMSE = stdevW*stdevW/Neff;
  };
 public: 
  Double_t mVal; // weithted mean value
  Double_t mMSE; // Mean squared error of mean, https://en.wikipedia.org/wiki/Mean_squared_error

};

class MultiparticleCorrelation
{
 public:
  MultiparticleCorrelation();
  // 2-particle correlations only
  MultiparticleCorrelation(TProfile *const &pCor2, Int_t &cent);
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2Var, Int_t &cent);
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2red, 
                           TProfile *const &pCov22prime,
                           Int_t &cent, Int_t &pt);
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor2red, 
                           TProfile *const &pCor2Var, TProfile *const &pCor2redVar, TProfile *const &pCov22prime,
                           Int_t &cent, Int_t &pt);
  // 2- and 4-particle correlations of RFP (statistical uncertainties calculated according to Ante's thesis)
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCov24, Int_t &cent);
  // 2- and 4-particle correlations of RFP (statistical uncertainties calculated according to Cochran)
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, 
                           TProfile *const &pCor2Var, TProfile *const &pCor4Var, 
                           TProfile *const &pCov24, Int_t &cent);
  // 2- and 4-particle correlations of POI (statistical uncertainties calculated according to Ante's thesis)
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red,
                           TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const & pCov24prime,
                           TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                           Int_t &cent, Int_t &pt);
  // 2- and 4-particle correlations of POI (statistical uncertainties calculated according to Cochran)
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red,
                           TProfile *const &pCor2Var, TProfile *const &pCor4Var, TProfile *const &pCor2redVar, TProfile *const &pCor4redVar,
                           TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const & pCov24prime,
                           TProfile *const &pCov42prime, TProfile *const &pCov2prime4prime, TProfile *const &pCov44prime,
                           Int_t &cent, Int_t &pt);
  // for ratio v2{4}/v2{2,2-sub}
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, 
                           TProfile *const &pCor2Var, TProfile *const &pCor4Var,
                           TProfile *const &pCor2Gap, TProfile *const &pCor2GapVar,
                           TProfile *const &pCov24, TProfile *const &pCov2Gap4, TProfile *const &pCov2Gap2, Int_t &cent);
  MultiparticleCorrelation(TProfile *const &pCor2, TProfile *const &pCor4, TProfile *const &pCor2red, TProfile *const &pCor4red, TProfile *const &pCor2Gap, TProfile *const &pCor2redGap,
                           TProfile *const &pCor2Var, TProfile *const &pCor4Var, TProfile *const &pCor2redVar, TProfile *const &pCor4redVar, TProfile *const &pCor2GapVar, TProfile *const &pCor2redGapVar,
                           TProfile *const &pCov22prime, TProfile *const &pCov24, TProfile *const &pCov24prime,
                           TProfile *const &hcov42prime, TProfile *const &hcov2prime4prime, TProfile *const &hcov44prime,
                           TProfile *const &pCov22primeGap, TProfile *const &pCov2Gap2, TProfile *const &pCov2Gap4,
                           TProfile *const &hcov2primeGap2, TProfile *const &hcov2primeGap4,
                           TProfile *const &hcov2Gap2prime, TProfile *const &hcov2Gap4prime,
                           TProfile *const &hcov2primeGap2prime, TProfile *const &hcov2primeGap4prime,
                           Int_t &cent, Int_t &pt);

  virtual ~MultiparticleCorrelation();
  Double_t GetV22Ref() const { return this->v22Ref; }
  Double_t GetV22RefErr() const { return this->v22Refe; }
  Double_t GetV24Ref() const { return this->v24Ref; }
  Double_t GetV24RefErr() const { return this->v24Refe; }

  Double_t GetV22Dif() const { return this->v22Dif; }
  Double_t GetV22DifErr() const { return this->v22Dife; }
  Double_t GetV24Dif() const { return this->v24Dif; }
  Double_t GetV24DifErr() const { return this->v24Dife; }

  Double_t GetRatioV24V22Ref() const { return this->ratioV24OverV22Ref; }
  Double_t GetRatioV24V22RefErr() const { return this->ratioV24OverV22Refe; }
  Double_t GetRatioV24V22Dif() const { return this->ratioV24OverV22Dif; }
  Double_t GetRatioV24V22DifErr() const { return this->ratioV24OverV22Dife; }  

  Double_t GetCor2Ref() const { return this->cor2.mVal; }
  Double_t GetCor2MSERef() const { return this->cor2.mMSE; }
  Double_t GetCor4Ref() const { return this->cor4.mVal; }
  Double_t GetCor4MSERef() const { return this->cor4.mMSE; }

  Double_t GetCor2Dif() const { return this->cor2red.mVal; }
  Double_t GetCor2MSEDif() const { return this->cor2red.mMSE; }
  Double_t GetCor4Dif() const { return this->cor4red.mVal; }
  Double_t GetCor4MSEDif() const { return this->cor4red.mMSE; }

 private: 
  Int_t fCentBin;
  Int_t fPtBin;

  term cor2, cor2red, cor4, cor4red;
  Double_t cov22prime, cov24, cov24prime,cov42prime, cov2prime4prime, cov44prime;

  Double_t v22Ref, v24Ref, v22Refe, v24Refe;
  Double_t v22Dif, v24Dif, v22Dife, v24Dife;

  Double_t ratioV24OverV22Ref, ratioV24OverV22Refe;
  Double_t ratioV24OverV22Dif, ratioV24OverV22Dife;

  Double_t Covariance(TProfile *const &hcovXY, TProfile *const &hX, TProfile *const &hY, Int_t binXY, Int_t binX, Int_t binY);
  ClassDef(MultiparticleCorrelation,0);
};