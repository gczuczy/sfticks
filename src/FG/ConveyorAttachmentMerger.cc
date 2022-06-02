
#include "FG/ConveyorAttachmentMerger.hh"
#include "FG/IntProperty.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string ConveyorAttachmentMerger::objtypename("Build_ConveyorAttachmentMerger_C");

  ConveyorAttachmentMerger::ConveyorAttachmentMerger(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBeltLogic(EntityType::ConveyorAttachmentMerger, _reader, _fgoh) {
    defineProperty(std::make_shared<IntProperty>("mCurrentInputIndex", c_mCurrentInputIndex));
    defineProperty(std::make_shared<IntProperty>("mCurrentInventoryIndex", c_mCurrentInventoryIndex));
  }

  ConveyorAttachmentMerger::~ConveyorAttachmentMerger() {
  }

  void ConveyorAttachmentMerger::associateComponents() {
    ConveyorBeltLogic::associateComponents();

    uint32_t idx=0;
    for (auto&& it: inputs()) {
      if ( !it->isConnected() ) continue;
      it->setIndex(idx++);
      c_connected_inputs.push_back(it);
    }
    c_mCurrentInventoryIndex=0;
  }

  void ConveyorAttachmentMerger::doTick(SFT::tickinfo_t& _tick) {
    // TODO: this needs to be more sophisticated.
    // input connections without inputable items should be skipped
    // this way the throughput is equally divided even in cases when
    // there's no actual input (input queue empty on connection)
    c_mCurrentInputIndex = (c_mCurrentInputIndex+1)%c_connected_inputs.size();
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }

  bool ConveyorAttachmentMerger::recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src) {
    printf("%s\n - %s\n - From idx: %u\nBufferInventory:%s\n\n",
	   __PRETTY_FUNCTION__,
	   instance().c_str(),
	   _src.index(),
	   bufferInventory()->compdetails().c_str());

    // Changing this after every item is a bit more problematic
    // because belts are not ticked after each transfer
    if ( c_mCurrentInputIndex != _src.index() ) return false;
    
    return bufferInventory()->store(_item);
  }
}
