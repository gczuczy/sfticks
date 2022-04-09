
#include "FGGeneratorFuel.hh"

std::string FGGeneratorFuel::objtypename("Build_GeneratorFuel_C");

FGGeneratorFuel::FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh)
  : FGGeneratorUnit(FGEntityType::GeneratorFuel, _reader, _fgoh) {
}

FGGeneratorFuel::~FGGeneratorFuel() {
}

