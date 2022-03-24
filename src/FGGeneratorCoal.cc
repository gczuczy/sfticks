
#include "FGGeneratorCoal.hh"

FGGeneratorCoal::FGGeneratorCoal(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::GeneratorCoal, _reader, _fgoh){
}

FGGeneratorCoal::~FGGeneratorCoal() {
}

