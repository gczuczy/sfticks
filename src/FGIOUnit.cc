
#include "FGIOUnit.hh"

#include "FloatProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

FGIOUnit::FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGBuilding(_et, _reader, _fgoh), c_mCurrentManufacturingProgress(0),
    c_mPendingPotential(0), c_mCurrentPotential(0) {
  defineProperty(std::make_shared<FloatProperty>("mCurrentManufacturingProgress", c_mCurrentManufacturingProgress));
  defineProperty(std::make_shared<ObjectProperty>("mInputInventory", c_mInputInventory));
  defineProperty(std::make_shared<ObjectProperty>("mOutputInventory", c_mOutputInventory));
  defineProperty(std::make_shared<ObjectProperty>("mCurrentRecipe", c_mCurrentRecipe));
  defineProperty(std::make_shared<ObjectProperty>("mInventoryPotential", c_mInventoryPotential));
  defineProperty(std::make_shared<FloatProperty>("mPendingPotential", c_mPendingPotential));
  defineProperty(std::make_shared<FloatProperty>("mCurrentPotential", c_mCurrentPotential));
}

FGIOUnit::~FGIOUnit() {
}
