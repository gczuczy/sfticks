
#include "FGConveyorLiftMk5.hh"

std::string FGConveyorLiftMk5::objtypename("Build_ConveyorLiftMk5_C");

FGConveyorLiftMk5::FGConveyorLiftMk5(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorLift(FGEntityType::ConveyorLiftMk5, _reader, _fgoh, 780){
}

FGConveyorLiftMk5::~FGConveyorLiftMk5() {
}

