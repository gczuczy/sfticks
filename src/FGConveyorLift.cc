
#include "FGConveyorLift.hh"
#include "GenericStruct.hh"
#include "ArrayProperty.hh"
#include "ObjectProperty.hh"

FGConveyorLift::FGConveyorLift(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGConveyorBelt(_et, _reader, _fgoh, _throughput) {
  defineProperty(std::make_shared<GenericStruct>("Transform", "mTopTransform"));
  defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mSnappedPassthroughs", c_mSnappedPassthroughs));
}

FGConveyorLift::~FGConveyorLift() {
}


