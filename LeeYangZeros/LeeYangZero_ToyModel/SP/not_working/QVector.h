#ifndef QVECTOR_H
#define QVECTOR_H
#include "constants.C"
#include <TMath.h>
class QVector
{
public:
  QVector();
  virtual ~QVector();
  void Zero();
  void CalQVector(const double &phi, const double &weight);
  void WeightQVector();
  double X() const { return this->fQx; }
  double Y() const { return this->fQy; }
  int GetMult() const { return this->fMult; }

private:
  double fQx;
  double fQy;
  double fWeight;
  int fMult;
  ClassDef(QVector,0);
};

#endif