
#include "FGConveyorBelt.hh"
#include "GenericArrayProperty.hh"

FGConveyorBelt::ConveyorAny::ConveyorAny(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(FGComponentType::ConveyorAny, _reader, _fgoh) {
  //defineProperty(std::make_shared<ArrayProperty<StructProperty<InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
}

FGComponentSP FGConveyorBelt::ConveyorAny::instantiate(Reader& _reader, FGObjectHeader& _fgoh) {
  return std::make_shared<FGConveyorBelt::ConveyorAny>(_reader, _fgoh);
}
FGConveyorBelt::FGConveyorBelt(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput)
  : FGBuilding(_et, _reader, _fgoh), c_throughput(_throughput) {
  defineProperty(std::make_shared<GenericArrayProperty>("mSplineData"));
}

FGConveyorBelt::~FGConveyorBelt() {
}


