
#include "FGSpaceElevator.hh"

FGSpaceElevator::FGSpaceElevator(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::SpaceElevator, _reader, _fgoh){
}

FGSpaceElevator::~FGSpaceElevator() {
}

