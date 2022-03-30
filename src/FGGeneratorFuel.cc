
#include "FGGeneratorFuel.hh"

FGGeneratorFuel::FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh)
  : FGGeneratorUnit(FGEntityType::GeneratorFuel, _reader, _fgoh), c_mPendingPotential(0),
    c_mCurrentPotential(0) {
#if 0
  defineProperty("mPendingPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mPendingPotential);});
  defineProperty("mCurrentPotential", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mPendingPotential);});
#endif
}

FGGeneratorFuel::~FGGeneratorFuel() {
}

