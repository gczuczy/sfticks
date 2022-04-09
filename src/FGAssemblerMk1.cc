
#include "FGAssemblerMk1.hh"

std::string FGAssemblerMk1::objtypename("Build_AssemblerMk1_C");

FGAssemblerMk1::FGAssemblerMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::AssemblerMk1, _reader, _fgoh){
}

FGAssemblerMk1::~FGAssemblerMk1() {
}

