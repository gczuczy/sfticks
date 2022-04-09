
#include "FGGeneratorFuel.hh"

namespace FG {

  std::string GeneratorFuel::objtypename("Build_GeneratorFuel_C");

  GeneratorFuel::GeneratorFuel(Reader& _reader, ObjectHeader& _fgoh)
    : GeneratorUnit(EntityType::GeneratorFuel, _reader, _fgoh) {
  }

  GeneratorFuel::~GeneratorFuel() {
  }

}
