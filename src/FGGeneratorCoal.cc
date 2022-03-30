
#include "FGGeneratorCoal.hh"

#include "FloatProperty.hh"
#include "BoolProperty.hh"

FGGeneratorCoal::FGGeneratorCoal(Reader& _reader, FGObjectHeader& _fgoh)
  : FGGeneratorUnit(FGEntityType::GeneratorCoal, _reader, _fgoh), c_mCurrentSupplementalAmount(0),
    c_mHasSupplementalCached(false) {
  defineProperty(std::make_shared<FloatProperty>("mCurrentSupplementalAmount", c_mCurrentSupplementalAmount));
  defineProperty(std::make_shared<BoolProperty>("mHasSupplementalCached", c_mHasSupplementalCached));
}

FGGeneratorCoal::~FGGeneratorCoal() {
}

