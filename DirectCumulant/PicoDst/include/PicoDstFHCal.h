#ifndef PICIODST_FHCAL_H
#define PICIODST_FHCAL_H

#include <TROOT.h>
#include <TObject.h>

class PicoDstFHCal : public TObject
{
private:
  Float_t fEnergy;
public:
  PicoDstFHCal();
  virtual ~PicoDstFHCal();

  virtual void Clear(Option_t *option = "");

  // Setters
  virtual void SetEnergy(Float_t _a) { fEnergy = _a; }

  // Getters
  virtual Float_t GetEnergy() const { return fEnergy; }

  ClassDef(PicoDstFHCal,1);
};

#endif
