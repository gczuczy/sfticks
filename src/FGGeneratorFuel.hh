
#ifndef SFT_FGGENERATORFUEL_H
#define SFT_FGGENERATORFUEL_H

#include "FGGeneratorUnit.hh"

class FGGeneratorFuel: public FGGeneratorUnit {
public:
  FGGeneratorFuel()=delete;
  FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorFuel();

  inline float& mPendingPotential() {return c_mPendingPotential;};
  inline float& mCurrentPotential() {return c_mCurrentPotential;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mPendingPotential, c_mCurrentPotential;
};

#endif
