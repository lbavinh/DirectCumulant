#ifndef QVECTOR_H
#define QVECTOR_H
#include "../constants.C"
#include <TMath.h>
class QVector
{
public:
  QVector();
  QVector(Double_t n);
  virtual ~QVector();
  void Zero();
  void CalQVector(const Double_t &phi, const Double_t &weight);
  void WeightQVector();
  Double_t X() const { return this->fQx; }
  Double_t Y() const { return this->fQy; }
  Int_t GetMult() const { return this->fMult; }

private:
  Double_t fNHarmonic;
  Double_t fQx;
  Double_t fQy;
  Double_t fWeight;
  Int_t fMult;
  ClassDef(QVector,0);
};

#endif