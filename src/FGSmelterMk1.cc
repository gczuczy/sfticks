
#include "FGSmelterMk1.hh"

std::string FGSmelterMk1::objtypename("Build_SmelterMk1_C");

FGSmelterMk1::FGSmelterMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::SmelterMk1, _reader, _fgoh){
}

FGSmelterMk1::~FGSmelterMk1() {
}

