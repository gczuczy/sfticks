
#include "FGConveyorLiftMk4.hh"

std::string FGConveyorLiftMk4::objtypename("Build_ConveyorLiftMk4_C");

FGConveyorLiftMk4::FGConveyorLiftMk4(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorLift(FGEntityType::ConveyorLiftMk4, _reader, _fgoh, 480){
}

FGConveyorLiftMk4::~FGConveyorLiftMk4() {
}

