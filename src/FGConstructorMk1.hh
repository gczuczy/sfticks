
#ifndef SFT_FGCONSTRUCTORMK1_H
#define SFT_FGCONSTRUCTORMK1_H

#include "FGIOUnit.hh"

class FGConstructorMk1: public FGIOUnit {
private:
public:
  FGConstructorMk1()=delete;
  FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConstructorMk1();

  //virtual void deserializeProperties(Reader& _reader);
  inline float& mCurrentManufacturingProgress() {return c_mCurrentManufacturingProgress;};
  inline float& mTimeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
  inline bool& mIsProducing() {return c_mIsProducing;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mCurrentManufacturingProgress, c_mTimeSinceStartStopProducing;
  bool c_mIsProducing;
};

#endif
