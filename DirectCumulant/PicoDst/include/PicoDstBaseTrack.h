#ifndef PICODST_BASE_TRACK_H
#define PICODST_BASE_TRACK_H

#include <TROOT.h>
#include <TObject.h>
#include <TVector3.h>

class PicoDstBaseTrack : public TObject
{
private:
  TVector3 fMom;
  TVector3 fDCA;
public:
  PicoDstBaseTrack();
  virtual ~PicoDstBaseTrack();

  void Clear(Option_t *option = "") { TObject::Clear(option); fMom.SetXYZ(0,0,0); fDCA.SetXYZ(0,0,0); }

  // Setters
  virtual void SetPxPyPz(Float_t _px, Float_t _py, Float_t _pz) { fMom.SetXYZ(_px,_py,_pz); }
  virtual void SetPx(Float_t _a) { fMom.SetX(_a); }
  virtual void SetPy(Float_t _a) { fMom.SetY(_a); }
  virtual void SetPz(Float_t _a) { fMom.SetZ(_a); }
  virtual void SetDCA(Float_t _dcax, Float_t _dcay, Float_t _dcaz) { fDCA.SetXYZ(_dcax,_dcay,_dcaz); }
  virtual void SetDCAx(Float_t _a) { fDCA.SetX(_a); }
  virtual void SetDCAy(Float_t _a) { fDCA.SetY(_a); }
  virtual void SetDCAz(Float_t _a) { fDCA.SetZ(_a); }

  // Getters
  virtual TVector3 GetMom() { return fMom; }
  virtual Float_t  GetPx() { return fMom.X(); }
  virtual Float_t  GetPy() { return fMom.Y(); }
  virtual Float_t  GetPz() { return fMom.Z(); }
  virtual Float_t  GetPt() { return fMom.Perp(); }
  virtual Float_t  GetP() { return fMom.Mag(); }
  virtual Float_t  GetEta() { return fMom.Eta(); }
  virtual Float_t  GetPhi() { return fMom.Phi(); }
  virtual TVector3 GetDCA() { return fDCA; }
  virtual Float_t  GetDCAx() { return fDCA.X(); }
  virtual Float_t  GetDCAy() { return fDCA.Y(); }
  virtual Float_t  GetDCAz() { return fDCA.Z(); }

  ClassDef(PicoDstBaseTrack,1);
};

#endif
