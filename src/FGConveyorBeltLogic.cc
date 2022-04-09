
#include "FGConveyorBeltLogic.hh"
#include "ObjectProperty.hh"

namespace FG {

  ConveyorBeltLogic::ConveyorBeltLogic(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Building(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<ObjectProperty>("mBufferInventory", c_mBufferInventory));

    // components
    registerComponent("StorageInventory", c_StorageInventory);
  }

  ConveyorBeltLogic::~ConveyorBeltLogic() {
  }

}
