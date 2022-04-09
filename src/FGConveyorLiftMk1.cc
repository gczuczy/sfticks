
#include "FGConveyorLiftMk1.hh"

std::string FGConveyorLiftMk1::objtypename("Build_ConveyorLiftMk1_C");

FGConveyorLiftMk1::FGConveyorLiftMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorLift(FGEntityType::ConveyorLiftMk1, _reader, _fgoh, 60){
}

FGConveyorLiftMk1::~FGConveyorLiftMk1() {
}

