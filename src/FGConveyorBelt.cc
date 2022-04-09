
#include "FGConveyorBelt.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"

namespace FG {

  ConveyorBelt::ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : Building(_et, _reader, _fgoh), c_throughput(_throughput) {
    //defineProperty(std::make_shared<GenericArrayProperty>("mSplineData"));
    defineProperty(std::make_shared<ArrayProperty<StructProperty<SplinePointData> > >("mSplineData", c_mSplineData));
  }

  ConveyorBelt::~ConveyorBelt() {
  }

}
