
#include "FGSpaceElevator.hh"

std::string FGSpaceElevator::objtypename("Build_SpaceElevator_C");

FGSpaceElevator::FGSpaceElevator(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::SpaceElevator, _reader, _fgoh){
}

FGSpaceElevator::~FGSpaceElevator() {
}

