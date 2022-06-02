
#include "FG/ConveyorBeltLogic.hh"
#include "FG/ObjectProperty.hh"

namespace FG {

  ConveyorBeltLogic::ConveyorBeltLogic(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Building(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<ObjectProperty>("mBufferInventory", c_mBufferInventory));
  }

  ConveyorBeltLogic::~ConveyorBeltLogic() {
  }

  void ConveyorBeltLogic::associateComponents() {
    Building::associateComponents();
    c_mBufferInventory.resolveInto(c_bufferinventory);
    c_bufferinventory->setStackSize(1);
  }

  bool ConveyorBeltLogic::recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src) {
#if 0
    printf("%s\n - %s\nBufferInventory:%s\n\n", __PRETTY_FUNCTION__, instance().c_str(),
	   c_bufferinventory->compdetails().c_str());
#endif
    return c_bufferinventory->store(_item);
  }

}
