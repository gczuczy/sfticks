
#include "FGConveyorLiftMk2.hh"

std::string FGConveyorLiftMk2::objtypename("Build_ConveyorLiftMk2_C");

FGConveyorLiftMk2::FGConveyorLiftMk2(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorLift(FGEntityType::ConveyorLiftMk2, _reader, _fgoh, 120){
}

FGConveyorLiftMk2::~FGConveyorLiftMk2() {
}

