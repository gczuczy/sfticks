
#include "FGConveyorBeltLogic.hh"

FGConveyorBeltLogic::FGConveyorBeltLogic(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGBuilding(_et, _reader, _fgoh) {
  setObjDefDecls({"mBufferInventory"});
}

FGConveyorBeltLogic::~FGConveyorBeltLogic() {
}

