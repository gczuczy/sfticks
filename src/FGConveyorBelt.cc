
#include "FGConveyorBelt.hh"
#include "GenericArrayProperty.hh"
//#include "ObjectProperty.hh"

FGConveyorBelt::FGConveyorBelt(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGBuilding(_et, _reader, _fgoh), c_throughput(_throughput) {
  defineProperty(std::make_shared<GenericArrayProperty>("mSplineData"));
}

FGConveyorBelt::~FGConveyorBelt() {
}


