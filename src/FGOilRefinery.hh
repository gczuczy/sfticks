
#ifndef SFT_FGOilRefinery_H
#define SFT_FGOilRefinery_H

#include "FGIOUnit.hh"

class FGOilRefinery: public FGIOUnit {
public:
  FGOilRefinery()=delete;
  FGOilRefinery(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGOilRefinery();

  inline float& mPendingPotential() {return c_mPendingPotential;};
  inline float& mCurrentPotential() {return c_mCurrentPotential;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mPendingPotential, c_mCurrentPotential;
};

#endif
