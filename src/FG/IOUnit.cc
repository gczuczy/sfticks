
#include "FG/IOUnit.hh"

#include "FG/FloatProperty.hh"
#include "FG/ObjectProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  IOUnit::IOUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Building(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<FloatProperty>("mCurrentManufacturingProgress", c_mCurrentManufacturingProgress));
    defineProperty(std::make_shared<ObjectProperty>("mInputInventory", c_mInputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mOutputInventory", c_mOutputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mCurrentRecipe", c_mCurrentRecipe));
    defineProperty(std::make_shared<ObjectProperty>("mInventoryPotential", c_mInventoryPotential));
    defineProperty(std::make_shared<FloatProperty>("mPendingPotential", c_mPendingPotential));
    defineProperty(std::make_shared<FloatProperty>("mCurrentPotential", c_mCurrentPotential));
    defineProperty(std::make_shared<BoolProperty>("mIsProductionPaused", c_mIsProductionPaused));

  }

  IOUnit::~IOUnit() {
  }

}
