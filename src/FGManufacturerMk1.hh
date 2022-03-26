
#ifndef SFT_FGMANUFACTURERMK1_H
#define SFT_FGMANUFACTURERMK1_H

#include "FGIOUnit.hh"

class FGManufacturerMk1: public FGIOUnit {
public:
  FGManufacturerMk1()=delete;
  FGManufacturerMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGManufacturerMk1();

  inline float& mPendingPotential() {return c_mPendingPotential;};
  inline float& mCurrentPotential() {return c_mCurrentPotential;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mPendingPotential, c_mCurrentPotential;
};

#endif
