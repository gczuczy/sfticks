
#include "FGConstructorMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

FGConstructorMk1::FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ConstructorMk1, _reader, _fgoh) {
}

FGConstructorMk1::~FGConstructorMk1() {
}
