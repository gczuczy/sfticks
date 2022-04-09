
#include "FGGeneratorCoal.hh"

#include "FloatProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  std::string GeneratorCoal::objtypename("Build_GeneratorCoal_C");

  GeneratorCoal::GeneratorCoal(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorCoal, _reader, _fgoh), c_mCurrentSupplementalAmount(0),
      c_mHasSupplementalCached(false) {
    defineProperty(std::make_shared<FloatProperty>("mCurrentSupplementalAmount", c_mCurrentSupplementalAmount));
    defineProperty(std::make_shared<BoolProperty>("mHasSupplementalCached", c_mHasSupplementalCached));

    c_inputs.resize(1);
    c_outputs.resize(0);
    registerComponent("Input0", c_inputs[0]);
  }

  GeneratorCoal::~GeneratorCoal() {
  }

}
