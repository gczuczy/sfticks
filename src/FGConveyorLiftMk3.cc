
#include "FGConveyorLiftMk3.hh"

std::string FGConveyorLiftMk3::objtypename("Build_ConveyorLiftMk3_C");

FGConveyorLiftMk3::FGConveyorLiftMk3(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorLift(FGEntityType::ConveyorLiftMk3, _reader, _fgoh, 270){
}

FGConveyorLiftMk3::~FGConveyorLiftMk3() {
}

