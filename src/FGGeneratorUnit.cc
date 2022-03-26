
#include "FGGeneratorUnit.hh"

FGGeneratorUnit::FGGeneratorUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(_et, _reader, _fgoh), c_mCurrentFuelAmount(0), c_mHasFuelCached(false) {
  defPropLoaders();
}

FGGeneratorUnit::~FGGeneratorUnit() {
}

void FGGeneratorUnit::defPropLoaders() {
  setObjDefDecls({"mFuelInventory", "mCurrentFuelClass"});
  defineProperty("mCurrentFuelAmount", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentFuelAmount);});
  defineProperty("mHasFuelCached", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mHasFuelCached = b == 1;
		 });
}
