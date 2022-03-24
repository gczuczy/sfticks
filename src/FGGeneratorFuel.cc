
#include "FGGeneratorFuel.hh"

FGGeneratorFuel::FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::GeneratorFuel, _reader, _fgoh){
}

FGGeneratorFuel::~FGGeneratorFuel() {
}

