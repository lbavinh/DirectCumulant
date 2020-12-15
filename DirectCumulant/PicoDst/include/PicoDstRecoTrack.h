#ifndef PICODST_RECO_TRACK_H
#define PICODST_RECO_TRACK_H

#include "PicoDstBaseTrack.h"

class PicoDstRecoTrack : public PicoDstBaseTrack
{
private:
  Int_t fId; // Id of the corresponding MC track
  Int_t fInitialId; // Initial Id of the corresponding MC track
  Int_t fTofFlag;
  Float_t fTpcdEdx;
  Float_t fTofMass2;
  Float_t fPidProbPion;
  Float_t fPidProbKaon;
  Float_t fPidProbProton;
  Float_t fChi2;
  Int_t fNhits;
  Int_t fNhitsPoss;
  Short_t fChargeSign;
public:
  PicoDstRecoTrack();
  virtual ~PicoDstRecoTrack();

  void Clear(Option_t *option = "");

  // Setters
  virtual void SetInitialMcId(Int_t _a) { fInitialId = _a; }
  virtual void SetMcId(Int_t _a) { fId = _a; }
  virtual void SetTofFlag(Int_t _a) { fTofFlag = _a; }
  virtual void SetTpcdEdx(Float_t _a) { fTpcdEdx = _a; }
  virtual void SetTofMass2(Float_t _a) { fTofMass2 = _a; }
  virtual void SetPidProbPion(Float_t _a) { fPidProbPion = _a; }
  virtual void SetPidProbKaon(Float_t _a) { fPidProbKaon = _a; }
  virtual void SetPidProbProton(Float_t _a) { fPidProbProton = _a; }
  virtual void SetChi2(Float_t _a) { fChi2 = _a; }
  virtual void SetNhits(Int_t _a) { fNhits = _a; }
  virtual void SetNhitsPoss(Int_t _a) { fNhitsPoss = _a; }
  virtual void SetCharge(Short_t _a) { fChargeSign = _a; }
  
  // Getters
  virtual Int_t   GetInitialMcId() const { return fInitialId; }
  virtual Int_t   GetMcId() const { return fId; }
  virtual Int_t   GetTofFlag() const { return fTofFlag; }
  virtual Float_t GetTpcdEdx() const { return fTpcdEdx; }
  virtual Float_t GetTofMass2() const { return fTofMass2; }
  virtual Float_t GetPidProbPion() const { return fPidProbPion; }
  virtual Float_t GetPidProbKaon() const { return fPidProbKaon; }
  virtual Float_t GetPidProbProton() const { return fPidProbProton; }
  virtual Float_t GetChi2() const { return fChi2; }
  virtual Int_t   GetNhits() const { return fNhits; }
  virtual Int_t   GetNhitsPoss() const { return fNhitsPoss; }
  virtual Short_t GetCharge() const { return fChargeSign; }

  ClassDef(PicoDstRecoTrack,1);
};

#endif
