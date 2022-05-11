
#include "FG/GeneratorCoal.hh"

#include "FG/FloatProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  std::string GeneratorCoal::objtypename("Build_GeneratorCoal_C");

  GeneratorCoal::GeneratorCoal(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorCoal, _reader, _fgoh), c_mCurrentSupplementalAmount(0),
      c_mHasSupplementalCached(false) {
    defineProperty(std::make_shared<FloatProperty>("mCurrentSupplementalAmount", c_mCurrentSupplementalAmount));
    defineProperty(std::make_shared<BoolProperty>("mHasSupplementalCached", c_mHasSupplementalCached));

    defineInputs({"Input0"});
  }

  GeneratorCoal::~GeneratorCoal() {
  }

}
