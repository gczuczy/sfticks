
#include "FGConveyorLift.hh"
#include "GenericStruct.hh"

FGConveyorLift::FGConveyorLift(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGConveyorBelt(_et, _reader, _fgoh, _throughput) {
  defineProperty(std::make_shared<GenericStruct>("Transform", "mTopTransform"));
}

FGConveyorLift::~FGConveyorLift() {
}


