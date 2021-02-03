#include <QVector.h>

ClassImp(QVector);

QVector::QVector() : fQx(0), fQy(0), fMult(0), fWeight(0) 
{
}

QVector::~QVector()
{
}

void QVector::Zero()
{
  fQx = 0.;
  fQy = 0.;
  fMult = 0.;
  fWeight = 0.;
}

void QVector::CalQVector(const double &phi, const double &weight)
{
  fQx += weight * TMath::Cos(2.0 * phi);
  fQy += weight * TMath::Sin(2.0 * phi);
  fWeight += weight;
  fMult++;
}

void QVector::WeightQVector()
{
  if (fMult != 0)
  {
    fQx /= fWeight;
    fQy /= fWeight;
  }
}