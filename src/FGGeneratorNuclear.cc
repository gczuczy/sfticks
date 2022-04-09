
#include "FGGeneratorNuclear.hh"

std::string FGGeneratorNuclear::objtypename("Build_GeneratorNuclear_C");

FGGeneratorNuclear::FGGeneratorNuclear(Reader& _reader, FGObjectHeader& _fgoh)
  : FGGeneratorUnit(FGEntityType::GeneratorNuclear, _reader, _fgoh){
}

FGGeneratorNuclear::~FGGeneratorNuclear() {
}

