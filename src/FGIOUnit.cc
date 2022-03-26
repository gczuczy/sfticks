
#include "FGIOUnit.hh"

FGIOUnit::FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGBuilding(_et, _reader, _fgoh), c_mCurrentManufacturingProgress(0) {
  defPropLoaders();
}

FGIOUnit::~FGIOUnit() {
}

void FGIOUnit::defPropLoaders() {
  setObjDefDecls({"mCurrentRecipe", "mInputInventory", "mOutputInventory",
      "mInventoryPotential"});

  defineProperty("mCurrentManufacturingProgress", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentManufacturingProgress);});
}
