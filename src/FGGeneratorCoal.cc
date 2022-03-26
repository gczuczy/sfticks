
#include "FGGeneratorCoal.hh"

FGGeneratorCoal::FGGeneratorCoal(Reader& _reader, FGObjectHeader& _fgoh)
  : FGGeneratorUnit(FGEntityType::GeneratorCoal, _reader, _fgoh), c_mCurrentSupplementalAmount(0),
    c_mHasSupplementalCached(false) {
  defineProperty("mCurrentSupplementalAmount", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentSupplementalAmount);});
  defineProperty("mHasSupplementalCached", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mHasSupplementalCached = b == 1;
		 });
}

FGGeneratorCoal::~FGGeneratorCoal() {
}

