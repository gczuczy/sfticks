
#include "FGConveyorLift.hh"
#include "ArrayProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"
#include "StructProperty.hh"

namespace FG {

  ConveyorLift::ConveyorLift(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : ConveyorBelt(_et, _reader, _fgoh, _throughput) {
    defineProperty(std::make_shared<StructProperty<Transform> >("mTopTransform", c_mTopTransform));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mSnappedPassthroughs", c_mSnappedPassthroughs));
    defineProperty(std::make_shared<BoolProperty>("mIsReversed", c_mIsReversed));
  }

  ConveyorLift::~ConveyorLift() {
  }

  float ConveyorLift::length() {
    return c_mTopTransform.Translation.z;
  }
}

