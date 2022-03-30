
#include "FGConveyorBeltLogic.hh"
#include "ObjectProperty.hh"

FGConveyorBeltLogic::FGConveyorBeltLogic(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGBuilding(_et, _reader, _fgoh) {
  defineProperty(std::make_shared<ObjectProperty>("mBufferInventory", c_mBufferInventory));
}

FGConveyorBeltLogic::~FGConveyorBeltLogic() {
}

