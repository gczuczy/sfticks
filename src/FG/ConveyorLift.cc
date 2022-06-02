
#include "FG/ConveyorLift.hh"
#include "FG/ArrayProperty.hh"
#include "FG/ObjectProperty.hh"
#include "FG/BoolProperty.hh"
#include "FG/StructProperty.hh"

namespace FG {

  ConveyorLift::ConveyorLift(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : ConveyorBelt(_et, _reader, _fgoh, _throughput) {
    defineProperty(std::make_shared<StructProperty<Transform> >("mTopTransform", c_mTopTransform));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mSnappedPassthroughs", c_mSnappedPassthroughs));
    defineProperty(std::make_shared<BoolProperty>("mIsReversed", c_mIsReversed));
  }

  ConveyorLift::~ConveyorLift() {
  }

  float ConveyorLift::calcLength() {
    return c_mTopTransform.Translation.z;
  }
}

