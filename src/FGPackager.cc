
#include "FGPackager.hh"

FGPackager::FGPackager(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::Packager, _reader, _fgoh){
}

FGPackager::~FGPackager() {
}

