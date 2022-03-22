
#include "FGConveyorBelt.hh"

FGConveyorBelt::FGConveyorBelt(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGBuilding(_et, _reader, _fgoh), c_throughput(_throughput) {
}

FGConveyorBelt::~FGConveyorBelt() {
}

