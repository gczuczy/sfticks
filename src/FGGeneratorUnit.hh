
#ifndef SFT_FGGENERATORUNIT_H
#define SFT_FGGENERATORUNIT_H

#include "FGIOUnit.hh"
#include "ObjectReference.hh"

/*
  This is a base class for Input/Output units.
  An input-output unit is everything that has at least input or output, and
  does something with it, apart from storing it.
 */
class FGGeneratorUnit: public FGIOUnit {
public:
  FGGeneratorUnit()=delete;
  FGGeneratorUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorUnit();

  inline float& mCurrentFuelAmount() {return c_mCurrentFuelAmount;};
  inline bool& mHasFuelCached() {return c_mHasFuelCached;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mCurrentFuelAmount;
  bool c_mHasFuelCached;
  ObjectReference c_mFuelInventory, c_mCurrentFuelClass;
};

typedef std::shared_ptr<FGGeneratorUnit> FGGeneratorUnitSP;

#endif
