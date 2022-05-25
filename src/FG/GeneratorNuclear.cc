
#include "FG/GeneratorNuclear.hh"
#include "FG/IntProperty.hh"
#include "FG/FloatProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  std::string GeneratorNuclear::objtypename("Build_GeneratorNuclear_C");

  GeneratorNuclear::GeneratorNuclear(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorNuclear, _reader, _fgoh), c_mWasteLeftFromCurrentFuel(0),
      c_mCurrentSupplementalAmount(0), c_mHasSupplementalCached(false) {
    defineProperty(std::make_shared<IntProperty>("mWasteLeftFromCurrentFuel", c_mWasteLeftFromCurrentFuel));
    defineProperty(std::make_shared<FloatProperty>("mCurrentSupplementalAmount", c_mCurrentSupplementalAmount));
    defineProperty(std::make_shared<BoolProperty>("mHasSupplementalCached", c_mHasSupplementalCached));
  }

  GeneratorNuclear::~GeneratorNuclear() {
  }

}
