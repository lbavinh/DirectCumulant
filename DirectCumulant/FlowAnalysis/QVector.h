#ifndef QVECTOR_H
#define QVECTOR_H
#include <iostream>
#include "../constants.C"
#include <TMath.h>
using std::cerr;
using std::cout;
using std::endl;
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
  int GetMult() const { return this->fMult; }
  Double_t GetWeight() const { return this->fWeight; }

private:
  Double_t fNHarmonic;
  Double_t fQx;
  Double_t fQy;
  Double_t fWeight;
  int fMult;
  ClassDef(QVector,0);
};

#endif