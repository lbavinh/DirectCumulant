#ifndef PICODST_BASE_EVENT_H
#define PICODST_BASE_EVENT_H

#include <TROOT.h>
#include <TVector3.h>

class PicoDstBaseEvent
{
private:
  TVector3 fVertex;
public:
  PicoDstBaseEvent();
  virtual ~PicoDstBaseEvent();

  // Setters
  virtual void SetVertex(Float_t _x, Float_t _y, Float_t _z){ fVertex.SetXYZ(_x,_y,_z); }

  // Getters
  virtual TVector3 GetVertex() const { return fVertex; }
  virtual Float_t  GetVertexX() const { return fVertex.X(); }
  virtual Float_t  GetVertexY() const { return fVertex.Y(); }
  virtual Float_t  GetVertexZ() const { return fVertex.Z(); }
  
  ClassDef(PicoDstBaseEvent,1);
};

#endif
