
#include "FGManufacturerMk1.hh"

FGManufacturerMk1::FGManufacturerMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ManufacturerMk1, _reader, _fgoh), c_mPendingPotential(0),
    c_mCurrentPotential(0) {
#if 0
  defineProperty("mPendingPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mPendingPotential);});
  defineProperty("mCurrentPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentPotential);});
#endif
}

FGManufacturerMk1::~FGManufacturerMk1() {
}

