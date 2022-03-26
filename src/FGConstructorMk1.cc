
#include "FGConstructorMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

FGConstructorMk1::FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ConstructorMk1, _reader, _fgoh, {"mInputInventory", "mOutputInventory", "mCurrentRecipe",
							    "mPowerInfo", "mInventoryPotential"}),
    c_mCurrentManufacturingProgress(0) {
  defineProperty("mCurrentManufacturingProgress", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentManufacturingProgress);});
  defineProperty("mTimeSinceStartStopProducing", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mTimeSinceStartStopProducing);});
  defineProperty("mIsProducing", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mIsProducing = b == 1;
		 });
}

FGConstructorMk1::~FGConstructorMk1() {
}
