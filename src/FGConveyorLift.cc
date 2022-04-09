
#include "FGConveyorLift.hh"
#include "GenericStruct.hh"
#include "ArrayProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  ConveyorLift::ConveyorLift(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : ConveyorBelt(_et, _reader, _fgoh, _throughput) {
    defineProperty(std::make_shared<GenericStruct>("Transform", "mTopTransform"));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mSnappedPassthroughs", c_mSnappedPassthroughs));
    defineProperty(std::make_shared<BoolProperty>("mIsReversed", c_mIsReversed));
  }

  ConveyorLift::~ConveyorLift() {
  }

}

