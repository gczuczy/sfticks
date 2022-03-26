
#include "FGOilRefinery.hh"

FGOilRefinery::FGOilRefinery(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::OilRefinery, _reader, _fgoh), c_mPendingPotential(0),
    c_mCurrentPotential(0) {
  defineProperty("mPendingPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mPendingPotential);});
  defineProperty("mCurrentPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentPotential);});
}

FGOilRefinery::~FGOilRefinery() {
}
