#include "PicoDstFHCal.h"

ClassImp(PicoDstFHCal);

PicoDstFHCal::PicoDstFHCal()
{
}

PicoDstFHCal::~PicoDstFHCal()
{
  Clear();
}

void PicoDstFHCal::Clear(Option_t *option)
{
  TObject::Clear(option);
  fEnergy = 0;
}
