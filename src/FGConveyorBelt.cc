
#include "FGConveyorBelt.hh"

FGConveyorBelt::FGConveyorBelt(FGEntityTypes _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGBuilding(_et, _reader, _fgoh), c_throughput(_throughput) {
}

