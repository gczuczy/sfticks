
#include "FGGeneratorNuclear.hh"

namespace FG {

  std::string GeneratorNuclear::objtypename("Build_GeneratorNuclear_C");

  GeneratorNuclear::GeneratorNuclear(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorNuclear, _reader, _fgoh){
  }

  GeneratorNuclear::~GeneratorNuclear() {
  }

}
