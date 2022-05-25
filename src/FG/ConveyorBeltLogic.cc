
#include "FG/ConveyorBeltLogic.hh"
#include "FG/ObjectProperty.hh"

namespace FG {

  ConveyorBeltLogic::ConveyorBeltLogic(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Building(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<ObjectProperty>("mBufferInventory", c_mBufferInventory));
  }

  ConveyorBeltLogic::~ConveyorBeltLogic() {
  }

}
