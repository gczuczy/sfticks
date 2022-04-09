
#include "FGConveyorBelt.hh"
#include "GenericArrayProperty.hh"
//#include "ObjectProperty.hh"

namespace FG {

  ConveyorBelt::ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : Building(_et, _reader, _fgoh), c_throughput(_throughput) {
    defineProperty(std::make_shared<GenericArrayProperty>("mSplineData"));
  }

  ConveyorBelt::~ConveyorBelt() {
  }

}
