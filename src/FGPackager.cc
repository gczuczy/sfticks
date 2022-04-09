
#include "FGPackager.hh"

std::string FGPackager::objtypename("Build_Packager_C");

FGPackager::FGPackager(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::Packager, _reader, _fgoh){
}

FGPackager::~FGPackager() {
}

