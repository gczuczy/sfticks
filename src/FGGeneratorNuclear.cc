
#include "FGGeneratorNuclear.hh"
#include "IntProperty.hh"
#include "FloatProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  std::string GeneratorNuclear::objtypename("Build_GeneratorNuclear_C");

  GeneratorNuclear::GeneratorNuclear(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorNuclear, _reader, _fgoh), c_mWasteLeftFromCurrentFuel(0),
      c_mCurrentSupplementalAmount(0), c_mHasSupplementalCached(false) {
    defineProperty(std::make_shared<IntProperty>("mWasteLeftFromCurrentFuel", c_mWasteLeftFromCurrentFuel));
    defineProperty(std::make_shared<FloatProperty>("mCurrentSupplementalAmount", c_mCurrentSupplementalAmount));
    defineProperty(std::make_shared<BoolProperty>("mHasSupplementalCached", c_mHasSupplementalCached));

    // components
    c_inputs.resize(1);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Output0", c_outputs[0]);
  }

  GeneratorNuclear::~GeneratorNuclear() {
  }

}
