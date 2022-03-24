
#include "FGFoundryMk1.hh"

FGFoundryMk1::FGFoundryMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::FoundryMk1, _reader, _fgoh){
}

FGFoundryMk1::~FGFoundryMk1() {
}

