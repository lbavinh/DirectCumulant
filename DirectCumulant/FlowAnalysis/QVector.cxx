#include <QVector.h>

ClassImp(QVector);

QVector::QVector() : fNHarmonic(2), fQx(0), fQy(0), fMult(0), fWeight(0) 
{
}

QVector::QVector(double n) : fNHarmonic(n), fQx(0), fQy(0), fMult(0), fWeight(0) 
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
  fQx += weight * TMath::Cos( fNHarmonic * phi );
  fQy += weight * TMath::Sin( fNHarmonic * phi );
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