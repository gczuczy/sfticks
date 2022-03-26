
#ifndef SFT_FGCONSTRUCTORMK1_H
#define SFT_FGCONSTRUCTORMK1_H

#include "FGIOUnit.hh"

class FGConstructorMk1: public FGIOUnit {
public:
  FGConstructorMk1()=delete;
  FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConstructorMk1();

  //virtual void deserializeProperties(Reader& _reader);
  inline float &mCurrentManufacturingProgress() {return c_mCurrentManufacturingProgress;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mCurrentManufacturingProgress;
};

#endif
