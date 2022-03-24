
#include "FGGeneratorNuclear.hh"

FGGeneratorNuclear::FGGeneratorNuclear(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::GeneratorNuclear, _reader, _fgoh){
}

FGGeneratorNuclear::~FGGeneratorNuclear() {
}

