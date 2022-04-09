
#include "FGConveyorAttachmentMerger.hh"

#include "IntProperty.hh"

std::string FGConveyorAttachmentMerger::objtypename("Build_ConveyorAttachmentMerger_C");

FGConveyorAttachmentMerger::FGConveyorAttachmentMerger(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentMerger, _reader, _fgoh), c_mCurrentInputIndex(0), c_mCurrentInventoryIndex(0) {
  defineProperty(std::make_shared<IntProperty>("mCurrentInputIndex", c_mCurrentInputIndex));
  defineProperty(std::make_shared<IntProperty>("mCurrentInventoryIndex", c_mCurrentInventoryIndex));
}

FGConveyorAttachmentMerger::~FGConveyorAttachmentMerger() {
}

