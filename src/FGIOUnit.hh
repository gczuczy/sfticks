
#ifndef SFT_FGIOUNIT_H
#define SFT_FGIOUNIT_H

#include "FGBuilding.hh"
#include "ObjectReference.hh"

/*
  This is a base class for Input/Output units.
  An input-output unit is everything that has at least input or output, and
  does something with it, apart from storing it.
 */
class FGIOUnit: public FGBuilding {
public:
  FGIOUnit()=delete;
  FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGIOUnit();

  inline float& mCurrentManufacturingProgress() {return c_mCurrentManufacturingProgress;};
  inline ObjectReference& mInputInventory() {return c_mInputInventory;};
  inline ObjectReference& mOutputInventory() {return c_mOutputInventory;};
  inline ObjectReference& mCurrentRecipe() {return c_mCurrentRecipe;};
  inline ObjectReference& mInventoryPotential() {return c_mInventoryPotential;};
  inline float& mPendingPotential() {return c_mPendingPotential;};
  inline float& mCurrentPotential() {return c_mCurrentPotential;};

private:
  //virtual void deserialize(Reader &_reader);
  float c_mCurrentManufacturingProgress, c_mPendingPotential, c_mCurrentPotential;
  ObjectReference c_mInputInventory, c_mCurrentRecipe, c_mOutputInventory, c_mInventoryPotential;
};

typedef std::shared_ptr<FGIOUnit> FGIOUnitSP;

#endif
